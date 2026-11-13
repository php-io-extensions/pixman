/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 445db6145de0f1e6aa3b76b99471716337047ce6 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_pixman_image_create_solid_fill, 0, 1, pixman_image, 1)
	ZEND_ARG_OBJ_INFO(0, color, pixman_color, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_pixman_image_create_linear_gradient, 0, 4, pixman_image, 1)
	ZEND_ARG_OBJ_INFO(0, p1, pixman_point_fixed, 0)
	ZEND_ARG_OBJ_INFO(0, p2, pixman_point_fixed, 0)
	ZEND_ARG_TYPE_INFO(0, stops, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, n_stops, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_pixman_image_create_radial_gradient, 0, 6, pixman_image, 1)
	ZEND_ARG_OBJ_INFO(0, inner, pixman_point_fixed, 0)
	ZEND_ARG_OBJ_INFO(0, outer, pixman_point_fixed, 0)
	ZEND_ARG_TYPE_INFO(0, inner_radius, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, outer_radius, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stops, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, n_stops, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_pixman_image_create_conical_gradient, 0, 4, pixman_image, 1)
	ZEND_ARG_OBJ_INFO(0, center, pixman_point_fixed, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stops, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, n_stops, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_pixman_image_create_bits, 0, 5, pixman_image, 1)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bits, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, rowstride_bytes, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_image_create_bits_no_clear arginfo_pixman_image_create_bits

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_pixman_image_ref, 0, 1, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_unref, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_destroy_function, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, function, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, data, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_get_destroy_data, 0, 1, IS_MIXED, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_clip_region, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region16, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_clip_region32, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_clip_region64f, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_has_client_clip, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, clien_clip, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_transform, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, transform, pixman_transform, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_repeat, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, repeat, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_dither, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, dither, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_dither_offset, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, offset_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset_y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_filter, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, filter, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, filter_params, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(0, n_filter_params, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_source_clipping, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, source_clipping, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_alpha_map, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, alpha_map, pixman_image, 1)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_component_alpha, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, component_alpha, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_image_get_component_alpha arginfo_pixman_image_unref

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_accessors, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, read_func, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, write_func, IS_CALLABLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_set_indexed, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, indexed, pixman_indexed, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_get_data, 0, 1, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_get_data_address, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_image_get_width arginfo_pixman_image_get_data_address

#define arginfo_pixman_image_get_height arginfo_pixman_image_get_data_address

#define arginfo_pixman_image_get_stride arginfo_pixman_image_get_data_address

#define arginfo_pixman_image_get_depth arginfo_pixman_image_get_data_address

#define arginfo_pixman_image_get_format arginfo_pixman_image_get_data_address

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_filter_create_separable_convolution, 0, 9, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(1, n_values, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(0, scale_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scale_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, reconstruct_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, reconstruct_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sample_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sample_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, subsample_bits_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, subsample_bits_y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_fill_rectangles, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, color, pixman_color, 0)
	ZEND_ARG_TYPE_INFO(0, n_rects, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, rects, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_fill_boxes, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, dest, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, color, pixman_color, 0)
	ZEND_ARG_TYPE_INFO(0, n_boxes, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, boxes, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_composite, 0, 12, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, src, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, mask, pixman_image, 1)
	ZEND_ARG_OBJ_INFO(0, dest, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, src_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mask_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mask_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dest_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dest_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_image_composite32 arginfo_pixman_image_composite

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_image_composite64f, 0, 12, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, src, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, mask, pixman_image, 1)
	ZEND_ARG_OBJ_INFO(0, dest, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, src_x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, src_y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, mask_x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, mask_y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, dest_x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, dest_y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_disable_out_of_bounds_workaround, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_format_supported_destination, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_format_supported_source arginfo_pixman_format_supported_destination

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_fill, 0, 8, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(1, bits, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, stride, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bpp, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, _xor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_blt, 0, 12, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, src_bits, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(1, dst_bits, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, src_stride, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst_stride, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_bpp, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst_bpp, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dest_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dest_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(pixman_image_create_solid_fill);
ZEND_FUNCTION(pixman_image_create_linear_gradient);
ZEND_FUNCTION(pixman_image_create_radial_gradient);
ZEND_FUNCTION(pixman_image_create_conical_gradient);
ZEND_FUNCTION(pixman_image_create_bits);
ZEND_FUNCTION(pixman_image_create_bits_no_clear);
ZEND_FUNCTION(pixman_image_ref);
ZEND_FUNCTION(pixman_image_unref);
ZEND_FUNCTION(pixman_image_set_destroy_function);
ZEND_FUNCTION(pixman_image_get_destroy_data);
ZEND_FUNCTION(pixman_image_set_clip_region);
ZEND_FUNCTION(pixman_image_set_clip_region32);
ZEND_FUNCTION(pixman_image_set_clip_region64f);
ZEND_FUNCTION(pixman_image_set_has_client_clip);
ZEND_FUNCTION(pixman_image_set_transform);
ZEND_FUNCTION(pixman_image_set_repeat);
ZEND_FUNCTION(pixman_image_set_dither);
ZEND_FUNCTION(pixman_image_set_dither_offset);
ZEND_FUNCTION(pixman_image_set_filter);
ZEND_FUNCTION(pixman_image_set_source_clipping);
ZEND_FUNCTION(pixman_image_set_alpha_map);
ZEND_FUNCTION(pixman_image_set_component_alpha);
ZEND_FUNCTION(pixman_image_get_component_alpha);
ZEND_FUNCTION(pixman_image_set_accessors);
ZEND_FUNCTION(pixman_image_set_indexed);
ZEND_FUNCTION(pixman_image_get_data);
ZEND_FUNCTION(pixman_image_get_data_address);
ZEND_FUNCTION(pixman_image_get_width);
ZEND_FUNCTION(pixman_image_get_height);
ZEND_FUNCTION(pixman_image_get_stride);
ZEND_FUNCTION(pixman_image_get_depth);
ZEND_FUNCTION(pixman_image_get_format);
ZEND_FUNCTION(pixman_filter_create_separable_convolution);
ZEND_FUNCTION(pixman_image_fill_rectangles);
ZEND_FUNCTION(pixman_image_fill_boxes);
ZEND_FUNCTION(pixman_image_composite);
ZEND_FUNCTION(pixman_image_composite32);
ZEND_FUNCTION(pixman_image_composite64f);
ZEND_FUNCTION(pixman_disable_out_of_bounds_workaround);
ZEND_FUNCTION(pixman_format_supported_destination);
ZEND_FUNCTION(pixman_format_supported_source);
ZEND_FUNCTION(pixman_fill);
ZEND_FUNCTION(pixman_blt);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(pixman_image_create_solid_fill, arginfo_pixman_image_create_solid_fill)
	ZEND_FE(pixman_image_create_linear_gradient, arginfo_pixman_image_create_linear_gradient)
	ZEND_FE(pixman_image_create_radial_gradient, arginfo_pixman_image_create_radial_gradient)
	ZEND_FE(pixman_image_create_conical_gradient, arginfo_pixman_image_create_conical_gradient)
	ZEND_FE(pixman_image_create_bits, arginfo_pixman_image_create_bits)
	ZEND_FE(pixman_image_create_bits_no_clear, arginfo_pixman_image_create_bits_no_clear)
	ZEND_FE(pixman_image_ref, arginfo_pixman_image_ref)
	ZEND_FE(pixman_image_unref, arginfo_pixman_image_unref)
	ZEND_FE(pixman_image_set_destroy_function, arginfo_pixman_image_set_destroy_function)
	ZEND_FE(pixman_image_get_destroy_data, arginfo_pixman_image_get_destroy_data)
	ZEND_FE(pixman_image_set_clip_region, arginfo_pixman_image_set_clip_region)
	ZEND_FE(pixman_image_set_clip_region32, arginfo_pixman_image_set_clip_region32)
	ZEND_FE(pixman_image_set_clip_region64f, arginfo_pixman_image_set_clip_region64f)
	ZEND_FE(pixman_image_set_has_client_clip, arginfo_pixman_image_set_has_client_clip)
	ZEND_FE(pixman_image_set_transform, arginfo_pixman_image_set_transform)
	ZEND_FE(pixman_image_set_repeat, arginfo_pixman_image_set_repeat)
	ZEND_FE(pixman_image_set_dither, arginfo_pixman_image_set_dither)
	ZEND_FE(pixman_image_set_dither_offset, arginfo_pixman_image_set_dither_offset)
	ZEND_FE(pixman_image_set_filter, arginfo_pixman_image_set_filter)
	ZEND_FE(pixman_image_set_source_clipping, arginfo_pixman_image_set_source_clipping)
	ZEND_FE(pixman_image_set_alpha_map, arginfo_pixman_image_set_alpha_map)
	ZEND_FE(pixman_image_set_component_alpha, arginfo_pixman_image_set_component_alpha)
	ZEND_FE(pixman_image_get_component_alpha, arginfo_pixman_image_get_component_alpha)
	ZEND_FE(pixman_image_set_accessors, arginfo_pixman_image_set_accessors)
	ZEND_FE(pixman_image_set_indexed, arginfo_pixman_image_set_indexed)
	ZEND_FE(pixman_image_get_data, arginfo_pixman_image_get_data)
	ZEND_FE(pixman_image_get_data_address, arginfo_pixman_image_get_data_address)
	ZEND_FE(pixman_image_get_width, arginfo_pixman_image_get_width)
	ZEND_FE(pixman_image_get_height, arginfo_pixman_image_get_height)
	ZEND_FE(pixman_image_get_stride, arginfo_pixman_image_get_stride)
	ZEND_FE(pixman_image_get_depth, arginfo_pixman_image_get_depth)
	ZEND_FE(pixman_image_get_format, arginfo_pixman_image_get_format)
	ZEND_FE(pixman_filter_create_separable_convolution, arginfo_pixman_filter_create_separable_convolution)
	ZEND_FE(pixman_image_fill_rectangles, arginfo_pixman_image_fill_rectangles)
	ZEND_FE(pixman_image_fill_boxes, arginfo_pixman_image_fill_boxes)
	ZEND_FE(pixman_image_composite, arginfo_pixman_image_composite)
	ZEND_FE(pixman_image_composite32, arginfo_pixman_image_composite32)
	ZEND_FE(pixman_image_composite64f, arginfo_pixman_image_composite64f)
	ZEND_FE(pixman_disable_out_of_bounds_workaround, arginfo_pixman_disable_out_of_bounds_workaround)
	ZEND_FE(pixman_format_supported_destination, arginfo_pixman_format_supported_destination)
	ZEND_FE(pixman_format_supported_source, arginfo_pixman_format_supported_source)
	ZEND_FE(pixman_fill, arginfo_pixman_fill)
	ZEND_FE(pixman_blt, arginfo_pixman_blt)
	ZEND_FE_END
};
