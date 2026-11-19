<?php

declare(strict_types=1);

$one = pixman_fixed_1;

function px_a8_sum(pixman_image $img): int
{
    return array_sum(unpack('C*', pixman_image_get_data($img, copy: true)));
}

it('rasterises a trapezoid into an a8 image', function () use ($one): void {
    $mask = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    $trap = new pixman_trapezoid(0, 4 * $one,
        new pixman_line_fixed(new pixman_point_fixed(0, 0), new pixman_point_fixed(0, 4 * $one)),
        new pixman_line_fixed(new pixman_point_fixed(2 * $one, 0), new pixman_point_fixed(2 * $one, 4 * $one)));
    pixman_rasterize_trapezoid($mask, $trap, 0, 0);
    $rows = str_split(pixman_image_get_data($mask, copy: true), 4);
    expect($rows[0])->toBe("\xff\xff\x00\x00");

    $m2 = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    pixman_add_trapezoids($m2, 0, 0, 1, [$trap]);
    expect(px_a8_sum($m2))->toBe(px_a8_sum($mask));

    expect(fn () => pixman_rasterize_trapezoid(px_argb(2, 2), $trap, 0, 0))->toThrow(ValueError::class, 'a1, a4 or a8');
});

it('adds traps and triangles, and composites them', function () use ($one): void {
    $mask = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    $trap = new pixman_trap(new pixman_span_fix(0, 2 * $one, 0), new pixman_span_fix(0, 2 * $one, 2 * $one));
    pixman_add_traps($mask, 0, 0, 1, [$trap]);
    expect(px_a8_sum($mask))->toBe(4 * 255);

    $tri = new pixman_triangle(new pixman_point_fixed(0, 0), new pixman_point_fixed(4 * $one, 0), new pixman_point_fixed(0, 4 * $one));
    $m2 = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    pixman_add_triangles($m2, 0, 0, 1, [$tri]);
    expect(px_a8_sum($m2))->toBeGreaterThan(0);

    $dst = px_argb(4, 4);
    pixman_composite_triangles(PIXMAN_OP_OVER, px_solid(0xffffffff), $dst, PIXMAN_a8, 0, 0, 0, 0, 1, [$tri]);
    expect(px_pixels($dst)[0])->toBe(0xffffffff);

    $dst2 = px_argb(4, 4);
    $trapz = new pixman_trapezoid(0, 4 * $one,
        new pixman_line_fixed(new pixman_point_fixed(0, 0), new pixman_point_fixed(0, 4 * $one)),
        new pixman_line_fixed(new pixman_point_fixed($one, 0), new pixman_point_fixed($one, 4 * $one)));
    pixman_composite_trapezoids(PIXMAN_OP_SRC, px_solid(0xff00ff00), $dst2, PIXMAN_a8, 0, 0, 0, 0, 1, [$trapz]);
    expect(px_pixels($dst2)[0])->toBe(0xff00ff00)
        ->and(px_pixels($dst2)[1])->toBe(0)
        ->and(fn () => pixman_composite_trapezoids(PIXMAN_OP_SRC, px_solid(0), $dst2, PIXMAN_a8r8g8b8, 0, 0, 0, 0, 0, []))->toThrow(ValueError::class);
});

it('initialises, steps and rasterises edges', function () use ($one): void {
    $t = pixman_sample_ceil_y(0, 8);
    $b = pixman_sample_floor_y(2 * $one, 8);
    $l = new pixman_edge();
    $r = new pixman_edge();
    pixman_edge_init($l, 8, $t, 0, 0, 0, 4 * $one);
    pixman_line_fixed_edge_init($r, 8, $t, new pixman_line_fixed(new pixman_point_fixed(2 * $one, 0), new pixman_point_fixed(2 * $one, 4 * $one)), 0, 0);
    expect($r->x)->toBe(2 * $one);

    $mask = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    pixman_rasterize_edges($mask, $l, $r, $t, $b);
    expect(str_split(pixman_image_get_data($mask, copy: true), 4))->toBe(["\xff\xff\x00\x00", "\xff\xff\x00\x00", "\0\0\0\0", "\0\0\0\0"])
        ->and(fn () => pixman_rasterize_edges($mask, $l, $r, 0, $b))->toThrow(ValueError::class, 'sample row')
        ->and(fn () => pixman_rasterize_edges($mask, $l, $r, $t, pixman_sample_floor_y(9 * $one, 8)))->toThrow(ValueError::class, 'inside the image');

    $e = new pixman_edge();
    pixman_edge_init($e, 8, 0, 0, 0, 4 * $one, 4 * $one);
    $x0 = $e->x;
    pixman_edge_step($e, 1);
    expect($e->x)->toBeGreaterThan($x0)
        ->and(pixman_sample_ceil_y(1, 8))->toBeGreaterThanOrEqual(1)
        ->and(pixman_sample_floor_y($one, 8))->toBeLessThanOrEqual($one)
        ->and(fn () => pixman_sample_floor_y(0, 0))->toThrow(ValueError::class, '1, 4 or 8')
        ->and(fn () => pixman_edge_step(new pixman_edge(dx: 1), 1))->toThrow(ValueError::class, 'dy 0')
        ->and(fn () => pixman_edge_step(new pixman_edge(), -1))->toThrow(ValueError::class, 'dy 0')
        ->and(fn () => pixman_edge_init(new pixman_edge(), 8, 0, 0, $one, 0, $one))->toThrow(ValueError::class, 'cannot initialise')
        ->and(fn () => pixman_edge_init(new pixman_edge(), 8, 0, 0x7fffffff, 0, -0x80000000, $one))->toThrow(ValueError::class, 'cannot initialise');
});

it('takes a trap, trapezoid or triangle array as a string of the C structs too, read in place', function () use ($one): void {
    // pixman_trap_t is top {l, r, y}, bot {l, r, y}; pixman_trapezoid_t top, bottom, left {p1, p2}, right {p1, p2};
    // pixman_triangle_t p1, p2, p3: int32 16.16 each, in the platform's order. A second struct in each string is
    // there to show that only the first n are read.
    $trap = new pixman_trap(new pixman_span_fix(0, 2 * $one, 0), new pixman_span_fix(0, 2 * $one, 2 * $one));
    $traps = pack('l*', 0, 2 * $one, 0, 0, 2 * $one, 2 * $one, 0, 4 * $one, 0, 0, 4 * $one, 4 * $one);
    $byObjects = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    $byString = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    pixman_add_traps($byObjects, 0, 0, 1, [$trap]);
    pixman_add_traps($byString, 0, 0, 1, $traps);
    expect(pixman_image_get_data($byString, copy: true))->toBe(pixman_image_get_data($byObjects, copy: true))
        ->and(px_a8_sum($byString))->toBe(4 * 255);

    $trapezoid = new pixman_trapezoid(0, 4 * $one,
        new pixman_line_fixed(new pixman_point_fixed(0, 0), new pixman_point_fixed(0, 4 * $one)),
        new pixman_line_fixed(new pixman_point_fixed(2 * $one, 0), new pixman_point_fixed(2 * $one, 4 * $one)));
    $trapezoids = pack('l*', 0, 4 * $one, 0, 0, 0, 4 * $one, 2 * $one, 0, 2 * $one, 4 * $one);
    $byObjects = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    $byString = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    pixman_add_trapezoids($byObjects, 0, 0, 1, [$trapezoid]);
    pixman_add_trapezoids($byString, 0, 0, 1, $trapezoids);
    expect(pixman_image_get_data($byString, copy: true))->toBe(pixman_image_get_data($byObjects, copy: true))
        ->and(px_a8_sum($byString))->toBe(8 * 255);

    $dst = px_argb(4, 4);
    pixman_composite_trapezoids(PIXMAN_OP_SRC, px_solid(0xff00ff00), $dst, PIXMAN_a8, 0, 0, 0, 0, 1, $trapezoids);
    expect(px_pixels($dst))->toBe([0xff00ff00, 0xff00ff00, 0, 0, 0xff00ff00, 0xff00ff00, 0, 0, 0xff00ff00, 0xff00ff00, 0, 0, 0xff00ff00, 0xff00ff00, 0, 0]);

    // the upper-left half of a 4 x 4 square, and a second triangle that is not read
    $triangle = new pixman_triangle(new pixman_point_fixed(0, 0), new pixman_point_fixed(4 * $one, 0), new pixman_point_fixed(0, 4 * $one));
    $triangles = pack('l*', 0, 0, 4 * $one, 0, 0, 4 * $one, 4 * $one, 4 * $one, 0, 4 * $one, 4 * $one, 0);
    $byObjects = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    $byString = pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0);
    pixman_add_triangles($byObjects, 0, 0, 1, [$triangle]);
    pixman_add_triangles($byString, 0, 0, 1, $triangles);
    expect(pixman_image_get_data($byString, copy: true))->toBe(pixman_image_get_data($byObjects, copy: true));

    $byObjects = px_argb(4, 4);
    $byString = px_argb(4, 4);
    pixman_composite_triangles(PIXMAN_OP_OVER, px_solid(0xffffffff), $byObjects, PIXMAN_a8, 0, 0, 0, 0, 1, [$triangle]);
    pixman_composite_triangles(PIXMAN_OP_OVER, px_solid(0xffffffff), $byString, PIXMAN_a8, 0, 0, 0, 0, 1, $triangles);
    expect(px_pixels($byString))->toBe(px_pixels($byObjects))
        ->and(px_pixels($byString)[0])->toBe(0xffffffff)
        ->and(px_pixels($byString)[15])->toBe(0);

    // two triangles' worth is all the string holds: three is refused by the count
    expect(fn () => pixman_composite_triangles(PIXMAN_OP_OVER, px_solid(0), px_argb(4, 4), PIXMAN_a8, 0, 0, 0, 0, 3, $triangles))
        ->toThrow(ValueError::class, 'structs the string holds (2)')
        ->and(fn () => pixman_add_traps(pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0), 0, 0, 1, substr($traps, 0, 23)))
        ->toThrow(ValueError::class, 'structs the string holds (0)')
        ->and(fn () => pixman_add_trapezoids(pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0), 0, 0, -1, $trapezoids))
        ->toThrow(ValueError::class);
});
