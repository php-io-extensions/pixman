<?php

/** @generate-function-entries */

function pixman_transform_init_identity(pixman_transform $matrix): void {}

function pixman_transform_point_3d(pixman_transform $transform, pixman_vector $vector): bool {}

function pixman_transform_point(pixman_transform $transform, pixman_vector $vector): bool {}

function pixman_transform_multiply(pixman_transform $dst, pixman_transform $l, pixman_transform $r): bool {}

function pixman_transform_init_scale(pixman_transform $t, int $sx, int $sy): void {}

function pixman_transform_scale(?pixman_transform $forward, ?pixman_transform $reverse, int $sx, int $sy): bool {}

function pixman_transform_init_rotate(pixman_transform $t, int $cos, int $sin): void {}

function pixman_transform_rotate(?pixman_transform $forward, ?pixman_transform $reverse, int $c, int $s): bool {}

function pixman_transform_init_translate(pixman_transform $t, int $tx, int $ty): void {}

function pixman_transform_translate(?pixman_transform $forward, ?pixman_transform $reverse, int $tx, int $ty): bool {}

function pixman_transform_bounds(pixman_transform $matrix, pixman_box16 $b): bool {}

function pixman_transform_invert(pixman_transform $dst, pixman_transform $src): bool {}

function pixman_transform_is_identity(pixman_transform $t): bool {}

function pixman_transform_is_scale(pixman_transform $t): bool {}

function pixman_transform_is_int_translate(pixman_transform $t): bool {}

function pixman_transform_is_inverse(pixman_transform $a, pixman_transform $b): bool {}

function pixman_transform_from_pixman_f_transform(pixman_transform $t, pixman_f_transform $ft): bool {}

function pixman_f_transform_from_pixman_transform(pixman_f_transform $ft, pixman_transform $t): void {}

function pixman_f_transform_invert(pixman_f_transform $dst, pixman_f_transform $src): bool {}

function pixman_f_transform_point(pixman_f_transform $t, pixman_f_vector $v): bool {}

function pixman_f_transform_point_3d(pixman_f_transform $t, pixman_f_vector $v): void {}

function pixman_f_transform_multiply(pixman_f_transform $dst, pixman_f_transform $l, pixman_f_transform $r): void {}

function pixman_f_transform_init_scale(pixman_f_transform $t, float $sx, float $sy): void {}

function pixman_f_transform_scale(?pixman_f_transform $forward, ?pixman_f_transform $reverse, float $sx, float $sy): bool {}

function pixman_f_transform_init_rotate(pixman_f_transform $t, float $cos, float $sin): void {}

function pixman_f_transform_rotate(?pixman_f_transform $forward, ?pixman_f_transform $reverse, float $c, float $s): bool {}

function pixman_f_transform_init_translate(pixman_f_transform $t, float $tx, float $ty): void {}

function pixman_f_transform_translate(?pixman_f_transform $forward, ?pixman_f_transform $reverse, float $tx, float $ty): bool {}

function pixman_f_transform_bounds(pixman_f_transform $t, pixman_box16 $b): bool {}

function pixman_f_transform_init_identity(pixman_f_transform $t): void {}
