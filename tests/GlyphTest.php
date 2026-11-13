<?php

declare(strict_types=1);

function px_glyph_image(): pixman_image
{
    return pixman_image_create_bits(PIXMAN_a8, 2, 2, str_repeat("\xff", 8), 4);
}

it('inserts, looks up and composites glyphs', function (): void {
    $cache = pixman_glyph_cache_create();
    pixman_glyph_cache_freeze($cache);
    $g = pixman_glyph_cache_insert($cache, 1, 65, 0, 0, px_glyph_image());
    pixman_glyph_cache_thaw($cache);

    expect($g)->not->toBe(0)
        ->and(pixman_glyph_cache_lookup($cache, 1, 65))->toBe($g)
        ->and(pixman_glyph_cache_lookup($cache, 1, 66))->toBe(0);

    $glyphs = [new pixman_glyph(1, 0, $g)];
    $ext = new pixman_box32();
    pixman_glyph_get_extents($cache, 1, $glyphs, $ext);
    expect([$ext->x1, $ext->y1, $ext->x2, $ext->y2])->toBe([1, 0, 3, 2])
        ->and(pixman_glyph_get_mask_format($cache, 1, $glyphs))->toBe(PIXMAN_a8);

    $dst = px_argb(4, 2);
    pixman_composite_glyphs_no_mask(PIXMAN_OP_SRC, px_solid(0xffffffff), $dst, 0, 0, 0, 0, $cache, 1, $glyphs);
    expect(px_pixels($dst))->toBe([0, 0xffffffff, 0xffffffff, 0, 0, 0xffffffff, 0xffffffff, 0]);

    $dst2 = px_argb(4, 2);
    pixman_composite_glyphs(PIXMAN_OP_OVER, px_solid(0xff0000ff), $dst2, PIXMAN_a8, 0, 0, 0, 0, 0, 0, 4, 2, $cache, 1, $glyphs);
    expect(px_pixels($dst2)[1])->toBe(0xff0000ff);
});

it('rejects glyph handles the cache does not hold', function (): void {
    $cache = pixman_glyph_cache_create();
    pixman_glyph_cache_freeze($cache);
    $g = pixman_glyph_cache_insert($cache, 1, 2, 0, 0, px_glyph_image());
    expect(fn () => pixman_glyph_cache_insert($cache, 1, 2, 0, 0, px_glyph_image()))->toThrow(ValueError::class, 'already cached');
    pixman_glyph_cache_thaw($cache);

    $dst = px_argb(2, 2);
    expect(fn () => pixman_composite_glyphs_no_mask(PIXMAN_OP_SRC, px_solid(0), $dst, 0, 0, 0, 0, $cache, 1, [new pixman_glyph(0, 0, 12345)]))
        ->toThrow(ValueError::class, 'not a glyph held by this cache');

    pixman_glyph_cache_remove($cache, 1, 2);
    expect(fn () => pixman_glyph_get_mask_format($cache, 1, [new pixman_glyph(0, 0, $g)]))->toThrow(ValueError::class)
        ->and(fn () => pixman_glyph_cache_thaw($cache))->toThrow(ValueError::class, 'more times');
});

it('destroys a cache even while frozen, and refuses use afterwards', function (): void {
    $cache = pixman_glyph_cache_create();
    pixman_glyph_cache_freeze($cache);
    pixman_glyph_cache_insert($cache, 3, 4, 0, 0, px_glyph_image());
    pixman_glyph_cache_destroy($cache);
    expect(fn () => pixman_glyph_cache_lookup($cache, 3, 4))->toThrow(ValueError::class, 'destroyed');

    $frozen = pixman_glyph_cache_create();
    pixman_glyph_cache_freeze($frozen);
    unset($frozen);
    expect(true)->toBeTrue();
});
