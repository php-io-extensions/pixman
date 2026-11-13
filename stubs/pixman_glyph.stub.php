<?php

/** @generate-function-entries */

function pixman_glyph_cache_create(): ?pixman_glyph_cache {}

function pixman_glyph_cache_destroy(pixman_glyph_cache $cache): void {}

function pixman_glyph_cache_freeze(pixman_glyph_cache $cache): void {}

function pixman_glyph_cache_thaw(pixman_glyph_cache $cache): void {}

function pixman_glyph_cache_lookup(pixman_glyph_cache $cache, int $font_key, int $glyph_key): int {}

function pixman_glyph_cache_insert(pixman_glyph_cache $cache, int $font_key, int $glyph_key, int $origin_x, int $origin_y, pixman_image $glyph_image): int {}

function pixman_glyph_cache_remove(pixman_glyph_cache $cache, int $font_key, int $glyph_key): void {}

function pixman_glyph_get_extents(pixman_glyph_cache $cache, int $n_glyphs, array $glyphs, pixman_box32 $extents): void {}

function pixman_glyph_get_mask_format(pixman_glyph_cache $cache, int $n_glyphs, array $glyphs): int {}

function pixman_composite_glyphs(int $op, pixman_image $src, pixman_image $dest, int $mask_format, int $src_x, int $src_y, int $mask_x, int $mask_y, int $dest_x, int $dest_y, int $width, int $height, pixman_glyph_cache $cache, int $n_glyphs, array $glyphs): void {}

function pixman_composite_glyphs_no_mask(int $op, pixman_image $src, pixman_image $dest, int $src_x, int $src_y, int $dest_x, int $dest_y, pixman_glyph_cache $cache, int $n_glyphs, array $glyphs): void {}
