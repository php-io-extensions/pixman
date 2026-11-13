<?php

/** @generate-function-entries */

function pixman_region32_init(pixman_region32 $region): void {}

function pixman_region32_init_rect(pixman_region32 $region, int $x, int $y, int $width, int $height): void {}

function pixman_region32_init_rects(pixman_region32 $region, array $boxes, int $count): bool {}

function pixman_region32_init_with_extents(pixman_region32 $region, pixman_box32 $extents): void {}

function pixman_region32_init_from_image(pixman_region32 $region, pixman_image $image): void {}

function pixman_region32_fini(pixman_region32 $region): void {}

function pixman_region32_translate(pixman_region32 $region, int $x, int $y): void {}

function pixman_region32_copy(pixman_region32 $dest, pixman_region32 $source): bool {}

function pixman_region32_intersect(pixman_region32 $new_reg, pixman_region32 $reg1, pixman_region32 $reg2): bool {}

function pixman_region32_union(pixman_region32 $new_reg, pixman_region32 $reg1, pixman_region32 $reg2): bool {}

function pixman_region32_intersect_rect(pixman_region32 $dest, pixman_region32 $source, int $x, int $y, int $width, int $height): bool {}

function pixman_region32_union_rect(pixman_region32 $dest, pixman_region32 $source, int $x, int $y, int $width, int $height): bool {}

function pixman_region32_subtract(pixman_region32 $reg_d, pixman_region32 $reg_m, pixman_region32 $reg_s): bool {}

function pixman_region32_inverse(pixman_region32 $new_reg, pixman_region32 $reg1, pixman_box32 $inv_rect): bool {}

function pixman_region32_contains_point(pixman_region32 $region, int $x, int $y, ?pixman_box32 $box): bool {}

function pixman_region32_contains_rectangle(pixman_region32 $region, pixman_box32 $prect): int {}

function pixman_region32_empty(pixman_region32 $region): bool {}

function pixman_region32_not_empty(pixman_region32 $region): bool {}

function pixman_region32_extents(pixman_region32 $region): pixman_box32 {}

function pixman_region32_n_rects(pixman_region32 $region): int {}

/** @param int|null $n_rects */
function pixman_region32_rectangles(pixman_region32 $region, ?int &$n_rects): array {}

function pixman_region32_equal(pixman_region32 $region1, pixman_region32 $region2): bool {}

function pixman_region32_selfcheck(pixman_region32 $region): bool {}

function pixman_region32_reset(pixman_region32 $region, pixman_box32 $box): void {}

function pixman_region32_clear(pixman_region32 $region): void {}
