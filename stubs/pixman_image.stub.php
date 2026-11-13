<?php

/** @generate-function-entries */

function pixman_image_create_solid_fill(pixman_color $color): ?pixman_image {}

function pixman_image_create_linear_gradient(pixman_point_fixed $p1, pixman_point_fixed $p2, array $stops, int $n_stops): ?pixman_image {}

function pixman_image_create_radial_gradient(pixman_point_fixed $inner, pixman_point_fixed $outer, int $inner_radius, int $outer_radius, array $stops, int $n_stops): ?pixman_image {}

function pixman_image_create_conical_gradient(pixman_point_fixed $center, int $angle, array $stops, int $n_stops): ?pixman_image {}

function pixman_image_create_bits(int $format, int $width, int $height, ?string $bits, int $rowstride_bytes): ?pixman_image {}

function pixman_image_create_bits_no_clear(int $format, int $width, int $height, ?string $bits, int $rowstride_bytes): ?pixman_image {}

function pixman_image_ref(pixman_image $image): pixman_image {}

function pixman_image_unref(pixman_image $image): bool {}

function pixman_image_set_destroy_function(pixman_image $image, ?callable $function, mixed $data): void {}

function pixman_image_get_destroy_data(pixman_image $image): mixed {}

function pixman_image_set_clip_region(pixman_image $image, ?pixman_region16 $region): bool {}

function pixman_image_set_clip_region32(pixman_image $image, ?pixman_region32 $region): bool {}

function pixman_image_set_clip_region64f(pixman_image $image, ?pixman_region64f $region): bool {}

function pixman_image_set_has_client_clip(pixman_image $image, bool $clien_clip): void {}

function pixman_image_set_transform(pixman_image $image, ?pixman_transform $transform): bool {}

function pixman_image_set_repeat(pixman_image $image, int $repeat): void {}

function pixman_image_set_dither(pixman_image $image, int $dither): void {}

function pixman_image_set_dither_offset(pixman_image $image, int $offset_x, int $offset_y): void {}

function pixman_image_set_filter(pixman_image $image, int $filter, ?array $filter_params, int $n_filter_params): bool {}

function pixman_image_set_source_clipping(pixman_image $image, bool $source_clipping): void {}

function pixman_image_set_alpha_map(pixman_image $image, ?pixman_image $alpha_map, int $x, int $y): void {}

function pixman_image_set_component_alpha(pixman_image $image, bool $component_alpha): void {}

function pixman_image_get_component_alpha(pixman_image $image): bool {}

function pixman_image_set_accessors(pixman_image $image, ?callable $read_func, ?callable $write_func): void {}

function pixman_image_set_indexed(pixman_image $image, ?pixman_indexed $indexed): void {}

function pixman_image_get_data(pixman_image $image): ?string {}

/** Binding addition: the address pixman_image_get_data() returns in C (0 for a non-bits image). Valid while the image lives. */
function pixman_image_get_data_address(pixman_image $image): int {}

function pixman_image_get_width(pixman_image $image): int {}

function pixman_image_get_height(pixman_image $image): int {}

function pixman_image_get_stride(pixman_image $image): int {}

function pixman_image_get_depth(pixman_image $image): int {}

function pixman_image_get_format(pixman_image $image): int {}

/** @param int|null $n_values */
function pixman_filter_create_separable_convolution(?int &$n_values, int $scale_x, int $scale_y, int $reconstruct_x, int $reconstruct_y, int $sample_x, int $sample_y, int $subsample_bits_x, int $subsample_bits_y): ?array {}

function pixman_image_fill_rectangles(int $op, pixman_image $image, pixman_color $color, int $n_rects, array $rects): bool {}

function pixman_image_fill_boxes(int $op, pixman_image $dest, pixman_color $color, int $n_boxes, array $boxes): bool {}

function pixman_image_composite(int $op, pixman_image $src, ?pixman_image $mask, pixman_image $dest, int $src_x, int $src_y, int $mask_x, int $mask_y, int $dest_x, int $dest_y, int $width, int $height): void {}

function pixman_image_composite32(int $op, pixman_image $src, ?pixman_image $mask, pixman_image $dest, int $src_x, int $src_y, int $mask_x, int $mask_y, int $dest_x, int $dest_y, int $width, int $height): void {}

function pixman_image_composite64f(int $op, pixman_image $src, ?pixman_image $mask, pixman_image $dest, float $src_x, float $src_y, float $mask_x, float $mask_y, float $dest_x, float $dest_y, float $width, float $height): void {}

function pixman_disable_out_of_bounds_workaround(): void {}

function pixman_format_supported_destination(int $format): bool {}

function pixman_format_supported_source(int $format): bool {}

/** @param string $bits */
function pixman_fill(string &$bits, int $stride, int $bpp, int $x, int $y, int $width, int $height, int $_xor): bool {}

/** @param string $dst_bits */
function pixman_blt(string $src_bits, string &$dst_bits, int $src_stride, int $dst_stride, int $src_bpp, int $dst_bpp, int $src_x, int $src_y, int $dest_x, int $dest_y, int $width, int $height): bool {}
