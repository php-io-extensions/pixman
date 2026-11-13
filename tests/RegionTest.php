<?php

declare(strict_types=1);

function px_rect32(int $x, int $y, int $w, int $h): pixman_region32
{
    $r = new pixman_region32();
    pixman_region32_init_rect($r, $x, $y, $w, $h);

    return $r;
}

it('combines regions', function (): void {
    $a = px_rect32(0, 0, 10, 10);
    $b = px_rect32(5, 5, 10, 10);
    $out = new pixman_region32();
    pixman_region32_init($out);

    expect(pixman_region32_union($out, $a, $b))->toBeTrue()
        ->and(pixman_region32_n_rects($out))->toBe(3);
    $e = pixman_region32_extents($out);
    expect([$e->x1, $e->y1, $e->x2, $e->y2])->toBe([0, 0, 15, 15]);

    pixman_region32_intersect($out, $a, $b);
    $rects = pixman_region32_rectangles($out, $n);
    expect($n)->toBe(1)
        ->and([$rects[0]->x1, $rects[0]->y1, $rects[0]->x2, $rects[0]->y2])->toBe([5, 5, 10, 10]);

    pixman_region32_subtract($out, $a, $b);
    expect(pixman_region32_contains_rectangle($out, new pixman_box32(5, 5, 10, 10)))->toBe(PIXMAN_REGION_OUT)
        ->and(pixman_region32_contains_rectangle($out, new pixman_box32(0, 0, 10, 10)))->toBe(PIXMAN_REGION_PART);

    $box = new pixman_box32();
    expect(pixman_region32_contains_point($a, 3, 3, $box))->toBeTrue()
        ->and($box->x2)->toBe(10)
        ->and(pixman_region32_contains_point($a, 30, 3, null))->toBeFalse();
});

it('initialises from boxes, extents and rects, and resets', function (): void {
    $r = new pixman_region32();
    expect(pixman_region32_init_rects($r, [new pixman_box32(0, 0, 2, 2), new pixman_box32(4, 0, 6, 2)], 2))->toBeTrue()
        ->and(pixman_region32_n_rects($r))->toBe(2)
        ->and(pixman_region32_selfcheck($r))->toBeTrue();

    pixman_region32_init_with_extents($r, new pixman_box32(1, 1, 3, 3));
    expect(pixman_region32_equal($r, px_rect32(1, 1, 2, 2)))->toBeTrue();

    pixman_region32_translate($r, 10, 0);
    expect(pixman_region32_extents($r)->x1)->toBe(11);

    pixman_region32_reset($r, new pixman_box32(0, 0, 1, 1));
    expect(pixman_region32_n_rects($r))->toBe(1);
    pixman_region32_clear($r);
    expect(pixman_region32_empty($r))->toBeTrue()
        ->and(pixman_region32_not_empty($r))->toBeFalse();

    $c = new pixman_region32();
    pixman_region32_init($c);
    expect(pixman_region32_copy($c, px_rect32(0, 0, 3, 3)))->toBeTrue()
        ->and(pixman_region32_union_rect($c, $c, 3, 0, 3, 3))->toBeTrue()
        ->and(pixman_region32_extents($c)->x2)->toBe(6)
        ->and(pixman_region32_intersect_rect($c, $c, 0, 0, 1, 1))->toBeTrue()
        ->and(pixman_region32_inverse($c, $c, new pixman_box32(0, 0, 2, 2)))->toBeTrue()
        ->and(pixman_region32_n_rects($c))->toBe(2);
});

it('builds a region from an a1 image', function (): void {
    $bits = pack('V', 0b1011) . pack('V', 0);
    $mask = pixman_image_create_bits(PIXMAN_a1, 4, 2, $bits, 4);
    $r = new pixman_region32();
    pixman_region32_init_from_image($r, $mask);
    expect(pixman_region32_n_rects($r))->toBe(2);

    $r2 = new pixman_region32();
    pixman_region32_init_from_image($r2, px_argb(2, 2));
    expect(pixman_region32_empty($r2))->toBeTrue();
});

it('rejects uninitialised and finished regions', function (): void {
    $r = new pixman_region32();
    expect(fn () => pixman_region32_n_rects($r))->toThrow(ValueError::class, 'uninitialised pixman_region32');

    pixman_region32_init($r);
    pixman_region32_fini($r);
    expect(fn () => pixman_region32_empty($r))->toThrow(ValueError::class)
        ->and(fn () => pixman_region32_init_rects($r, [], 1))->toThrow(ValueError::class);
});

it('binds region16 under the legacy names, with compute_composite_region', function (): void {
    $r = new pixman_region16();
    pixman_region_init_rect($r, 0, 0, 4, 4);
    $o = new pixman_region16();
    pixman_region_init($o);
    expect(pixman_region_union_rect($o, $r, 4, 0, 4, 4))->toBeTrue()
        ->and(pixman_region_n_rects($o))->toBe(1)
        ->and(pixman_region_extents($o)->x2)->toBe(8);

    $out = new pixman_region16();
    pixman_region_init($out);
    expect(pixman_compute_composite_region($out, px_argb(10, 10), null, px_argb(5, 5), 0, 0, 0, 0, 2, 2, 10, 10))->toBeTrue()
        ->and(pixman_region_extents($out)->x1)->toBe(2)
        ->and(pixman_region_extents($out)->x2)->toBe(5);
});

it('binds region64f with its float variants', function (): void {
    $r = new pixman_region64f();
    pixman_region64f_init_rectf($r, 0.5, 0.5, 2.0, 2.0);
    expect(pixman_region64f_extents($r)->x1)->toBe(0.5)
        ->and(pixman_region64f_contains_pointf($r, 1.0, 1.0, null))->toBeTrue();
    pixman_region64f_translatef($r, 1.0, 0.0);
    $o = new pixman_region64f();
    pixman_region64f_init($o);
    expect(pixman_region64f_union_rectf($o, $r, 10.0, 10.0, 1.0, 1.0))->toBeTrue()
        ->and(pixman_region64f_intersect_rectf($o, $o, 0.0, 0.0, 5.0, 5.0))->toBeTrue()
        ->and(pixman_region64f_extents($o)->x1)->toBe(1.5);
});
