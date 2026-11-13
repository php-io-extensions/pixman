<?php

/** @generate-function-entries */

function pixman_region_init(pixman_region16 $region): void {}

function pixman_region_init_rect(pixman_region16 $region, int $x, int $y, int $width, int $height): void {}

function pixman_region_init_rects(pixman_region16 $region, array $boxes, int $count): bool {}

function pixman_region_init_with_extents(pixman_region16 $region, pixman_box16 $extents): void {}

function pixman_region_init_from_image(pixman_region16 $region, pixman_image $image): void {}

function pixman_region_fini(pixman_region16 $region): void {}

function pixman_region_translate(pixman_region16 $region, int $x, int $y): void {}

function pixman_region_copy(pixman_region16 $dest, pixman_region16 $source): bool {}

function pixman_region_intersect(pixman_region16 $new_reg, pixman_region16 $reg1, pixman_region16 $reg2): bool {}

function pixman_region_union(pixman_region16 $new_reg, pixman_region16 $reg1, pixman_region16 $reg2): bool {}

function pixman_region_intersect_rect(pixman_region16 $dest, pixman_region16 $source, int $x, int $y, int $width, int $height): bool {}

function pixman_region_union_rect(pixman_region16 $dest, pixman_region16 $source, int $x, int $y, int $width, int $height): bool {}

function pixman_region_subtract(pixman_region16 $reg_d, pixman_region16 $reg_m, pixman_region16 $reg_s): bool {}

function pixman_region_inverse(pixman_region16 $new_reg, pixman_region16 $reg1, pixman_box16 $inv_rect): bool {}

function pixman_region_contains_point(pixman_region16 $region, int $x, int $y, ?pixman_box16 $box): bool {}

function pixman_region_contains_rectangle(pixman_region16 $region, pixman_box16 $prect): int {}

function pixman_region_empty(pixman_region16 $region): bool {}

function pixman_region_not_empty(pixman_region16 $region): bool {}

function pixman_region_extents(pixman_region16 $region): pixman_box16 {}

function pixman_region_n_rects(pixman_region16 $region): int {}

/** @param int|null $n_rects */
function pixman_region_rectangles(pixman_region16 $region, ?int &$n_rects): array {}

function pixman_region_equal(pixman_region16 $region1, pixman_region16 $region2): bool {}

function pixman_region_selfcheck(pixman_region16 $region): bool {}

function pixman_region_reset(pixman_region16 $region, pixman_box16 $box): void {}

function pixman_region_clear(pixman_region16 $region): void {}

function pixman_compute_composite_region(pixman_region16 $region, pixman_image $src_image, ?pixman_image $mask_image, pixman_image $dest_image, int $src_x, int $src_y, int $mask_x, int $mask_y, int $dest_x, int $dest_y, int $width, int $height): bool {}
