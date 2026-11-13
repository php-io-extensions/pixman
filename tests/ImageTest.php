<?php

declare(strict_types=1);

it('composites solid colours with SRC, OVER and ADD', function (): void {
    $dst = px_argb(3, 1);
    pixman_image_composite32(PIXMAN_OP_SRC, px_solid(0xff102030), null, $dst, 0, 0, 0, 0, 0, 0, 3, 1);
    pixman_image_composite32(PIXMAN_OP_OVER, px_solid(0x80800000), null, $dst, 0, 0, 0, 0, 1, 0, 1, 1);
    pixman_image_composite(PIXMAN_OP_ADD, px_solid(0x00010101), null, $dst, 0, 0, 0, 0, 2, 0, 1, 1);

    // OVER with premultiplied 0x80800000: r = 0x80 + 0x10 * 0x7f / 0xff
    expect(px_pixels($dst))->toBe([0xff102030, 0xff881018, 0xff112131]);
});

it('composites through a mask and with composite64f', function (): void {
    $mask = pixman_image_create_bits(PIXMAN_a8, 2, 1, "\xff\x00\x00\x00", 4);
    $dst = px_argb(2, 1);
    pixman_image_composite32(PIXMAN_OP_SRC, px_solid(0xffffffff), $mask, $dst, 0, 0, 0, 0, 0, 0, 2, 1);
    expect(px_pixels($dst))->toBe([0xffffffff, 0]);

    $d2 = px_argb(2, 1);
    pixman_image_composite64f(PIXMAN_OP_SRC, px_solid(0xff00ff00), null, $d2, 0, 0, 0, 0, 1, 0, 1, 1);
    expect(px_pixels($d2))->toBe([0, 0xff00ff00]);
});

it('copies caller bits in and pixel data out', function (): void {
    $bits = pack('V*', 1, 2, 3, 4);
    $img = pixman_image_create_bits(PIXMAN_a8r8g8b8, 2, 2, $bits, 8);
    $bits[0] = "\x09";
    expect(px_pixels($img))->toBe([1, 2, 3, 4])
        ->and(pixman_image_get_width($img))->toBe(2)
        ->and(pixman_image_get_height($img))->toBe(2)
        ->and(pixman_image_get_stride($img))->toBe(8)
        ->and(pixman_image_get_depth($img))->toBe(32)
        ->and(pixman_image_get_format($img))->toBe(PIXMAN_a8r8g8b8)
        ->and(pixman_image_get_data(px_solid(0)))->toBeNull()
        ->and(pixman_image_get_data_address($img))->toBeGreaterThan(0)
        ->and(pixman_image_get_data_address(px_solid(0)))->toBe(0);

    $nc = pixman_image_create_bits_no_clear(PIXMAN_x8r8g8b8, 1, 1, pack('V', 0x00abcdef), 4);
    expect(px_pixels($nc))->toBe([0x00abcdef]);
});

it('checks bits, stride and format before pixman sees them', function (): void {
    expect(fn () => pixman_image_create_bits(PIXMAN_a8r8g8b8, 2, 2, str_repeat("\0", 15), 8))->toThrow(ValueError::class, 'at least 16 bytes')
        ->and(fn () => pixman_image_create_bits(PIXMAN_a8r8g8b8, 2, 2, str_repeat("\0", 16), 6))->toThrow(ValueError::class, 'multiple of 4')
        ->and(fn () => pixman_image_create_bits(PIXMAN_a8r8g8b8, 2, 2, str_repeat("\0", 16), 4))->toThrow(ValueError::class, 'at least 8 bytes')
        ->and(fn () => pixman_image_create_bits(12345, 1, 1, null, 0))->toThrow(ValueError::class, 'format code');
});

it('creates gradients', function (): void {
    $one = pixman_fixed_1;
    $stops = [new pixman_gradient_stop(0, new pixman_color(0, 0, 0, 0xffff)), new pixman_gradient_stop($one, new pixman_color(0xffff, 0xffff, 0xffff, 0xffff))];
    $lin = pixman_image_create_linear_gradient(new pixman_point_fixed(0, 0), new pixman_point_fixed(4 * $one, 0), $stops, 2);
    $dst = px_argb(4, 1);
    pixman_image_composite32(PIXMAN_OP_SRC, $lin, null, $dst, 0, 0, 0, 0, 0, 0, 4, 1);
    $p = px_pixels($dst);
    expect($p[0] & 0xff)->toBeLessThan($p[3] & 0xff)
        ->and(pixman_image_create_radial_gradient(new pixman_point_fixed(), new pixman_point_fixed(), 0, $one, $stops, 2))->toBeInstanceOf(pixman_image::class)
        ->and(pixman_image_create_conical_gradient(new pixman_point_fixed(), 0, $stops, 2))->toBeInstanceOf(pixman_image::class)
        ->and(fn () => pixman_image_create_linear_gradient(new pixman_point_fixed(), new pixman_point_fixed(), $stops, 3))->toThrow(ValueError::class);
});

it('holds one reference per object; unref releases the object', function (): void {
    $img = px_argb(1, 1);
    $second = pixman_image_ref($img);
    expect(pixman_image_unref($img))->toBeFalse()
        ->and(fn () => pixman_image_get_width($img))->toThrow(ValueError::class, 'released')
        ->and(pixman_image_get_width($second))->toBe(1)
        ->and(pixman_image_unref($second))->toBeTrue();
});

it('calls the destroy function with its data when pixman destroys the image', function (): void {
    $seen = [];
    $img = px_argb(1, 1);
    pixman_image_set_destroy_function($img, function (pixman_image $image, mixed $data) use (&$seen): void {
        $seen[] = $data;
        expect(fn () => pixman_image_get_width($image))->toThrow(ValueError::class);
    }, ['tag' => 7]);
    expect(pixman_image_get_destroy_data($img))->toBe(['tag' => 7]);
    $keep = pixman_image_ref($img);
    unset($img);
    expect($seen)->toBe([]);
    unset($keep);
    expect($seen)->toBe([['tag' => 7]]);
});

it('scales through a transform with repeat and filter', function (): void {
    $src = pixman_image_create_bits(PIXMAN_a8r8g8b8, 2, 1, pack('V*', 0xffff0000, 0xff0000ff), 8);
    $t = new pixman_transform();
    pixman_transform_init_scale($t, pixman_fixed_1 / 2, pixman_fixed_1);
    expect(pixman_image_set_transform($src, $t))->toBeTrue()
        ->and(pixman_image_set_filter($src, PIXMAN_FILTER_NEAREST, null, 0))->toBeTrue();
    pixman_image_set_repeat($src, PIXMAN_REPEAT_NORMAL);
    $dst = px_argb(8, 1);
    pixman_image_composite32(PIXMAN_OP_SRC, $src, null, $dst, 0, 0, 0, 0, 0, 0, 8, 1);
    expect(px_pixels($dst))->toBe([0xffff0000, 0xffff0000, 0xff0000ff, 0xff0000ff, 0xffff0000, 0xffff0000, 0xff0000ff, 0xff0000ff])
        ->and(pixman_image_set_transform($src, null))->toBeTrue();
});

it('checks convolution parameters pixman trusts', function (): void {
    $img = px_argb(2, 2);
    $one = pixman_fixed_1;
    expect(fn () => pixman_image_set_filter($img, PIXMAN_FILTER_CONVOLUTION, [3 * $one, 3 * $one, $one], 3))->toThrow(ValueError::class, '2 + width x height')
        ->and(fn () => pixman_image_set_filter($img, PIXMAN_FILTER_SEPARABLE_CONVOLUTION, [$one], 1))->toThrow(ValueError::class, 'at least 4')
        ->and(pixman_image_set_filter($img, PIXMAN_FILTER_CONVOLUTION, [$one, $one, $one], 3))->toBeTrue();

    $params = pixman_filter_create_separable_convolution($n, $one, $one, PIXMAN_KERNEL_BOX, PIXMAN_KERNEL_BOX, PIXMAN_KERNEL_BOX, PIXMAN_KERNEL_BOX, 1, 1);
    expect($n)->toBe(count($params))
        ->and(pixman_image_set_filter($img, PIXMAN_FILTER_SEPARABLE_CONVOLUTION, $params, $n))->toBeTrue();
});

it('clips the destination to a region', function (): void {
    $dst = px_argb(3, 1);
    $clip = new pixman_region32();
    pixman_region32_init_rect($clip, 1, 0, 1, 1);
    expect(pixman_image_set_clip_region32($dst, $clip))->toBeTrue();
    pixman_image_composite32(PIXMAN_OP_SRC, px_solid(0xffffffff), null, $dst, 0, 0, 0, 0, 0, 0, 3, 1);
    expect(px_pixels($dst))->toBe([0, 0xffffffff, 0])
        ->and(pixman_image_set_clip_region32($dst, null))->toBeTrue();

    $r16 = new pixman_region16();
    pixman_region_init_rect($r16, 0, 0, 1, 1);
    $r64 = new pixman_region64f();
    pixman_region64f_init_rect($r64, 0, 0, 1, 1);
    expect(pixman_image_set_clip_region($dst, $r16))->toBeTrue()
        ->and(pixman_image_set_clip_region64f($dst, $r64))->toBeTrue();
    pixman_image_set_has_client_clip($dst, true);
    pixman_image_set_source_clipping($dst, false);
});

it('applies an alpha map, component alpha and dither settings', function (): void {
    $dst = pixman_image_create_bits(PIXMAN_x8r8g8b8, 1, 1, null, 0);
    $alpha = pixman_image_create_bits(PIXMAN_a8, 1, 1, null, 0);
    pixman_image_set_alpha_map($dst, $alpha, 0, 0);
    pixman_image_composite32(PIXMAN_OP_SRC, px_solid(0x80000000), null, $dst, 0, 0, 0, 0, 0, 0, 1, 1);
    expect(ord(pixman_image_get_data($alpha)[0]))->toBe(0x80);
    pixman_image_set_alpha_map($dst, null, 0, 0);

    $mask = px_argb(1, 1);
    pixman_image_set_component_alpha($mask, true);
    expect(pixman_image_get_component_alpha($mask))->toBeTrue();
    pixman_image_set_dither($dst, PIXMAN_DITHER_ORDERED_BAYER_8);
    pixman_image_set_dither_offset($dst, 1, 2);
    expect(fn () => pixman_image_set_dither($dst, 99))->toThrow(ValueError::class)
        ->and(fn () => pixman_image_set_repeat($dst, 4))->toThrow(ValueError::class);
});

it('reads a c8 image through a copied palette', function (): void {
    $pal = array_fill(0, 256, 0);
    $pal[1] = 0xff00ff00;
    $src = pixman_image_create_bits(PIXMAN_c8, 4, 1, "\x01\x00\x01\x00", 4);
    pixman_image_set_indexed($src, new pixman_indexed(true, $pal, null));
    gc_collect_cycles();
    $dst = px_argb(4, 1);
    pixman_image_composite32(PIXMAN_OP_SRC, $src, null, $dst, 0, 0, 0, 0, 0, 0, 4, 1);
    expect(px_pixels($dst))->toBe([0xff00ff00, 0, 0xff00ff00, 0]);
    pixman_image_set_indexed($src, null);
});

it('routes pixel reads through accessor callables', function (): void {
    $src = pixman_image_create_bits(PIXMAN_a8r8g8b8, 2, 1, pack('V*', 1, 2), 8);
    $calls = 0;
    pixman_image_set_accessors($src, function (int $address, int $size) use (&$calls): int {
        $calls++;

        return 0xff445566;
    }, null);
    $dst = px_argb(2, 1);
    pixman_image_composite32(PIXMAN_OP_SRC, $src, null, $dst, 0, 0, 0, 0, 0, 0, 2, 1);
    expect($calls)->toBeGreaterThan(0)
        ->and(px_pixels($dst))->toBe([0xff445566, 0xff445566]);

    $writes = [];
    pixman_image_set_accessors($dst, null, function (int $address, int $value, int $size) use (&$writes): void {
        $writes[] = $value;
    });
    pixman_image_set_accessors($src, null, null);
    pixman_image_composite32(PIXMAN_OP_SRC, $src, null, $dst, 0, 0, 0, 0, 0, 0, 2, 1);
    expect($writes)->toBe([1, 2])
        ->and(px_pixels($dst))->toBe([0xff445566, 0xff445566]);
});

it('surfaces an exception thrown by an accessor', function (): void {
    $src = px_argb(1, 1);
    pixman_image_set_accessors($src, fn (int $a, int $s): int => throw new RuntimeException('read failed'), null);
    expect(fn () => pixman_image_composite32(PIXMAN_OP_SRC, $src, null, px_argb(1, 1), 0, 0, 0, 0, 0, 0, 1, 1))
        ->toThrow(RuntimeException::class, 'read failed');
});

it('fills rectangles and boxes', function (): void {
    $dst = px_argb(3, 1);
    $c = new pixman_color(0xffff, 0, 0, 0xffff);
    expect(pixman_image_fill_rectangles(PIXMAN_OP_SRC, $dst, $c, 1, [new pixman_rectangle16(0, 0, 1, 1)]))->toBeTrue()
        ->and(pixman_image_fill_boxes(PIXMAN_OP_SRC, $dst, $c, 1, [new pixman_box32(2, 0, 3, 1)]))->toBeTrue()
        ->and(px_pixels($dst))->toBe([0xffff0000, 0, 0xffff0000])
        ->and(fn () => pixman_image_fill_boxes(0x0e, $dst, $c, 0, []))->toThrow(ValueError::class, 'PIXMAN_OP_');
});

it('fills and blits raw strings inside their bounds only', function (): void {
    $bits = str_repeat("\0", 16);
    expect(pixman_fill($bits, 2, 32, 1, 0, 1, 2, 0xaabbccdd))->toBeTrue()
        ->and(array_values(unpack('V*', $bits)))->toBe([0, 0xaabbccdd, 0, 0xaabbccdd])
        ->and(fn () => pixman_fill($bits, 2, 32, 1, 1, 2, 1, 0))->toThrow(ValueError::class, 'too short');

    $src = pack('V*', 7, 8, 9, 10);
    $dst = str_repeat("\0", 16);
    $before = $dst;
    expect(pixman_blt($src, $dst, 2, 2, 32, 32, 0, 0, 0, 1, 2, 1))->toBeTrue()
        ->and(array_values(unpack('V*', $dst)))->toBe([0, 0, 7, 8])
        ->and($before)->toBe(str_repeat("\0", 16))
        ->and(fn () => pixman_blt($src, $dst, 2, 2, 32, 32, 0, 1, 0, 1, 2, 2))->toThrow(ValueError::class);
});

it('reports supported formats', function (): void {
    expect(pixman_format_supported_destination(PIXMAN_a8r8g8b8))->toBeTrue()
        ->and(pixman_format_supported_destination(PIXMAN_yv12))->toBeFalse()
        ->and(pixman_format_supported_source(PIXMAN_yv12))->toBeTrue()
        ->and(pixman_format_supported_source(-1))->toBeFalse();
    pixman_disable_out_of_bounds_workaround();
});
