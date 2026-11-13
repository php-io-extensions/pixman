<?php

declare(strict_types=1);

$one = pixman_fixed_1;

it('initialises, multiplies and inverts fixed transforms', function () use ($one): void {
    $s = new pixman_transform();
    pixman_transform_init_scale($s, 2 * $one, 3 * $one);
    expect($s->matrix)->toBe([[2 * $one, 0, 0], [0, 3 * $one, 0], [0, 0, $one]])
        ->and(pixman_transform_is_scale($s))->toBeTrue();

    $inv = new pixman_transform();
    expect(pixman_transform_invert($inv, $s))->toBeTrue()
        ->and(pixman_transform_is_inverse($s, $inv))->toBeTrue();

    $id = new pixman_transform();
    pixman_transform_init_identity($id);
    $m = new pixman_transform();
    expect(pixman_transform_multiply($m, $s, $id))->toBeTrue()
        ->and($m->matrix)->toBe($s->matrix);
});

it('maps a point and writes the vector back', function () use ($one): void {
    $t = new pixman_transform();
    pixman_transform_init_translate($t, 5 * $one, -2 * $one);
    $v = new pixman_vector([$one, $one, $one]);
    expect(pixman_transform_point($t, $v))->toBeTrue()
        ->and($v->vector)->toBe([6 * $one, -1 * $one, $one]);
});

it('updates forward and reverse, either of which may be null', function () use ($one): void {
    $f = new pixman_transform();
    $r = new pixman_transform();
    pixman_transform_init_identity($f);
    pixman_transform_init_identity($r);
    expect(pixman_transform_translate($f, $r, 3 * $one, 0))->toBeTrue()
        ->and($f->matrix[0][2])->toBe(3 * $one)
        ->and($r->matrix[0][2])->toBe(-3 * $one)
        ->and(pixman_transform_scale(null, $r, 2 * $one, 2 * $one))->toBeTrue();
});

it('bounds a box', function () use ($one): void {
    $t = new pixman_transform();
    pixman_transform_init_scale($t, 2 * $one, 2 * $one);
    $b = new pixman_box16(1, 1, 3, 3);
    expect(pixman_transform_bounds($t, $b))->toBeTrue()
        ->and([$b->x1, $b->y1, $b->x2, $b->y2])->toBe([2, 2, 6, 6]);
});

it('converts between fixed and float transforms', function () use ($one): void {
    $ft = new pixman_f_transform();
    pixman_f_transform_init_rotate($ft, 0.0, 1.0);
    $t = new pixman_transform();
    expect(pixman_transform_from_pixman_f_transform($t, $ft))->toBeTrue()
        ->and($t->matrix[0])->toBe([0, -$one, 0]);

    $back = new pixman_f_transform();
    pixman_f_transform_from_pixman_transform($back, $t);
    expect($back->m[1][0])->toBe(1.0);

    $v = new pixman_f_vector([1.0, 0.0, 1.0]);
    expect(pixman_f_transform_point($ft, $v))->toBeTrue()
        ->and($v->v)->toBe([0.0, 1.0, 1.0]);

    $fi = new pixman_f_transform();
    pixman_f_transform_init_identity($fi);
    $fm = new pixman_f_transform();
    pixman_f_transform_multiply($fm, $ft, $fi);
    expect($fm->m)->toBe($ft->m);
    $finv = new pixman_f_transform();
    expect(pixman_f_transform_invert($finv, $ft))->toBeTrue();

    $fb = new pixman_box16(0, 0, 2, 1);
    expect(pixman_f_transform_bounds($ft, $fb))->toBeTrue();
    pixman_f_transform_init_scale($fi, 2.0, 2.0);
    pixman_f_transform_init_translate($fi, 1.0, 1.0);
    $p = new pixman_f_vector([0.0, 0.0, 1.0]);
    pixman_f_transform_point_3d($fi, $p);
    expect($p->v)->toBe([1.0, 1.0, 1.0])
        ->and(pixman_f_transform_scale($fi, null, 2.0, 2.0))->toBeTrue()
        ->and(pixman_f_transform_rotate($fi, null, 1.0, 0.0))->toBeTrue()
        ->and(pixman_f_transform_translate($fi, null, 1.0, 0.0))->toBeTrue();
});

it('rejects a fixed value outside int32', function (): void {
    expect(fn () => pixman_transform_init_scale(new pixman_transform(), 1 << 40, 1))->toThrow(ValueError::class);
});
