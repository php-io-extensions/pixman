<?php

/** @generate-function-entries */

function pixman_region64f_init(pixman_region64f $region): void {}

function pixman_region64f_init_rect(pixman_region64f $region, int $x, int $y, int $width, int $height): void {}

function pixman_region64f_init_rects(pixman_region64f $region, array $boxes, int $count): bool {}

function pixman_region64f_init_with_extents(pixman_region64f $region, pixman_box64f $extents): void {}

function pixman_region64f_init_from_image(pixman_region64f $region, pixman_image $image): void {}

function pixman_region64f_fini(pixman_region64f $region): void {}

function pixman_region64f_translate(pixman_region64f $region, int $x, int $y): void {}

function pixman_region64f_copy(pixman_region64f $dest, pixman_region64f $source): bool {}

function pixman_region64f_intersect(pixman_region64f $new_reg, pixman_region64f $reg1, pixman_region64f $reg2): bool {}

function pixman_region64f_union(pixman_region64f $new_reg, pixman_region64f $reg1, pixman_region64f $reg2): bool {}

function pixman_region64f_intersect_rect(pixman_region64f $dest, pixman_region64f $source, int $x, int $y, int $width, int $height): bool {}

function pixman_region64f_union_rect(pixman_region64f $dest, pixman_region64f $source, int $x, int $y, int $width, int $height): bool {}

function pixman_region64f_subtract(pixman_region64f $reg_d, pixman_region64f $reg_m, pixman_region64f $reg_s): bool {}

function pixman_region64f_inverse(pixman_region64f $new_reg, pixman_region64f $reg1, pixman_box64f $inv_rect): bool {}

function pixman_region64f_contains_point(pixman_region64f $region, int $x, int $y, ?pixman_box64f $box): bool {}

function pixman_region64f_contains_rectangle(pixman_region64f $region, pixman_box64f $prect): int {}

function pixman_region64f_empty(pixman_region64f $region): bool {}

function pixman_region64f_not_empty(pixman_region64f $region): bool {}

function pixman_region64f_extents(pixman_region64f $region): pixman_box64f {}

function pixman_region64f_n_rects(pixman_region64f $region): int {}

/** @param int|null $n_rects */
function pixman_region64f_rectangles(pixman_region64f $region, ?int &$n_rects): array {}

function pixman_region64f_equal(pixman_region64f $region1, pixman_region64f $region2): bool {}

function pixman_region64f_selfcheck(pixman_region64f $region): bool {}

function pixman_region64f_reset(pixman_region64f $region, pixman_box64f $box): void {}

function pixman_region64f_clear(pixman_region64f $region): void {}

function pixman_region64f_init_rectf(pixman_region64f $region, float $x, float $y, float $width, float $height): void {}

function pixman_region64f_translatef(pixman_region64f $region, float $x, float $y): void {}

function pixman_region64f_intersect_rectf(pixman_region64f $dest, pixman_region64f $source, float $x, float $y, float $width, float $height): bool {}

function pixman_region64f_union_rectf(pixman_region64f $dest, pixman_region64f $source, float $x, float $y, float $width, float $height): bool {}

function pixman_region64f_contains_pointf(pixman_region64f $region, float $x, float $y, ?pixman_box64f $box): bool {}
