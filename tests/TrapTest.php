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
