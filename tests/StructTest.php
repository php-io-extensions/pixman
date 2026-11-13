<?php

declare(strict_types=1);

it('constructs value structs with C zero defaults and nested structs', function (): void {
    $t = new pixman_trapezoid();
    expect($t->top)->toBe(0)
        ->and($t->left)->toBeInstanceOf(pixman_line_fixed::class)
        ->and($t->left->p1)->toBeInstanceOf(pixman_point_fixed::class)
        ->and((new pixman_transform())->matrix)->toBe([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
        ->and((new pixman_f_vector())->v)->toBe([0.0, 0.0, 0.0])
        ->and(count((new pixman_indexed())->rgba))->toBe(256)
        ->and(strlen((new pixman_indexed())->ent))->toBe(32768);
});

it('takes named arguments', function (): void {
    $c = new pixman_color(alpha: 0xffff, blue: 7);
    expect([$c->red, $c->green, $c->blue, $c->alpha])->toBe([0, 0, 7, 0xffff]);
});

it('rejects values outside the C field', function (): void {
    expect(fn () => new pixman_box16(40000))->toThrow(ValueError::class, 'pixman_box16::$x1 must be between -32768 and 32767')
        ->and(fn () => new pixman_vector([1, 2]))->toThrow(ValueError::class, 'exactly 3 entries')
        ->and(fn () => new pixman_indexed(false, null, 'short'))->toThrow(ValueError::class, 'exactly 32768 bytes');
});

it('checks a struct again when a function reads it', function (): void {
    $box = new pixman_box32();
    $box->x1 = PHP_INT_MAX;
    $r = new pixman_region32();
    expect(fn () => pixman_region32_init_with_extents($r, $box))->toThrow(ValueError::class, 'pixman_box32::$x1');
});

it('refuses to construct or clone handles', function (): void {
    expect(fn () => new pixman_image())->toThrow(Error::class, 'Cannot directly construct pixman_image')
        ->and(fn () => new pixman_glyph_cache())->toThrow(Error::class)
        ->and(fn () => clone px_argb(1, 1))->toThrow(Error::class);
});

it('registers the enum and fixed-point constants', function (): void {
    expect(PIXMAN_OP_OVER)->toBe(3)
        ->and(PIXMAN_a8r8g8b8)->toBe(0x20028888)
        ->and(pixman_fixed_1)->toBe(65536)
        ->and(PIXMAN_VERSION_STRING)->toBe('0.46.4')
        ->and(PIXMAN_REGION_PART)->toBe(2);
});
