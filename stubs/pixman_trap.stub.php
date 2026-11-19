<?php

/** @generate-function-entries */

function pixman_sample_ceil_y(int $y, int $bpp): int {}

function pixman_sample_floor_y(int $y, int $bpp): int {}

function pixman_edge_step(pixman_edge $e, int $n): void {}

function pixman_edge_init(pixman_edge $e, int $bpp, int $y_start, int $x_top, int $y_top, int $x_bot, int $y_bot): void {}

function pixman_line_fixed_edge_init(pixman_edge $e, int $bpp, int $y, pixman_line_fixed $line, int $x_off, int $y_off): void {}

function pixman_rasterize_edges(pixman_image $image, pixman_edge $l, pixman_edge $r, int $t, int $b): void {}

function pixman_add_traps(pixman_image $image, int $x_off, int $y_off, int $ntrap, array|string $traps): void {}

function pixman_add_trapezoids(pixman_image $image, int $x_off, int $y_off, int $ntraps, array|string $traps): void {}

function pixman_rasterize_trapezoid(pixman_image $image, pixman_trapezoid $trap, int $x_off, int $y_off): void {}

function pixman_composite_trapezoids(int $op, pixman_image $src, pixman_image $dst, int $mask_format, int $x_src, int $y_src, int $x_dst, int $y_dst, int $n_traps, array|string $traps): void {}

function pixman_composite_triangles(int $op, pixman_image $src, pixman_image $dst, int $mask_format, int $x_src, int $y_src, int $x_dst, int $y_dst, int $n_tris, array|string $tris): void {}

function pixman_add_triangles(pixman_image $image, int $x_off, int $y_off, int $n_tris, array|string $tris): void {}
