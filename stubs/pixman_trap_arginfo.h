/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 8c7967ac5f601c63ec90918c2bd9c21e7bfe57b2 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_sample_ceil_y, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bpp, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_sample_floor_y arginfo_pixman_sample_ceil_y

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_edge_step, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, e, pixman_edge, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_edge_init, 0, 7, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, e, pixman_edge, 0)
	ZEND_ARG_TYPE_INFO(0, bpp, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_start, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x_top, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_top, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x_bot, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_bot, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_line_fixed_edge_init, 0, 6, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, e, pixman_edge, 0)
	ZEND_ARG_TYPE_INFO(0, bpp, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, line, pixman_line_fixed, 0)
	ZEND_ARG_TYPE_INFO(0, x_off, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_off, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_rasterize_edges, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, l, pixman_edge, 0)
	ZEND_ARG_OBJ_INFO(0, r, pixman_edge, 0)
	ZEND_ARG_TYPE_INFO(0, t, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_add_traps, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, x_off, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_off, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ntrap, IS_LONG, 0)
	ZEND_ARG_TYPE_MASK(0, traps, MAY_BE_ARRAY|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_add_trapezoids, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, x_off, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_off, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ntraps, IS_LONG, 0)
	ZEND_ARG_TYPE_MASK(0, traps, MAY_BE_ARRAY|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_rasterize_trapezoid, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, trap, pixman_trapezoid, 0)
	ZEND_ARG_TYPE_INFO(0, x_off, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_off, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_composite_trapezoids, 0, 10, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, src, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, dst, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, mask_format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x_src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x_dst, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_dst, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, n_traps, IS_LONG, 0)
	ZEND_ARG_TYPE_MASK(0, traps, MAY_BE_ARRAY|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_composite_triangles, 0, 10, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, src, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, dst, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, mask_format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x_src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x_dst, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_dst, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, n_tris, IS_LONG, 0)
	ZEND_ARG_TYPE_MASK(0, tris, MAY_BE_ARRAY|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_add_triangles, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, x_off, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y_off, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, n_tris, IS_LONG, 0)
	ZEND_ARG_TYPE_MASK(0, tris, MAY_BE_ARRAY|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(pixman_sample_ceil_y);
ZEND_FUNCTION(pixman_sample_floor_y);
ZEND_FUNCTION(pixman_edge_step);
ZEND_FUNCTION(pixman_edge_init);
ZEND_FUNCTION(pixman_line_fixed_edge_init);
ZEND_FUNCTION(pixman_rasterize_edges);
ZEND_FUNCTION(pixman_add_traps);
ZEND_FUNCTION(pixman_add_trapezoids);
ZEND_FUNCTION(pixman_rasterize_trapezoid);
ZEND_FUNCTION(pixman_composite_trapezoids);
ZEND_FUNCTION(pixman_composite_triangles);
ZEND_FUNCTION(pixman_add_triangles);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(pixman_sample_ceil_y, arginfo_pixman_sample_ceil_y)
	ZEND_FE(pixman_sample_floor_y, arginfo_pixman_sample_floor_y)
	ZEND_FE(pixman_edge_step, arginfo_pixman_edge_step)
	ZEND_FE(pixman_edge_init, arginfo_pixman_edge_init)
	ZEND_FE(pixman_line_fixed_edge_init, arginfo_pixman_line_fixed_edge_init)
	ZEND_FE(pixman_rasterize_edges, arginfo_pixman_rasterize_edges)
	ZEND_FE(pixman_add_traps, arginfo_pixman_add_traps)
	ZEND_FE(pixman_add_trapezoids, arginfo_pixman_add_trapezoids)
	ZEND_FE(pixman_rasterize_trapezoid, arginfo_pixman_rasterize_trapezoid)
	ZEND_FE(pixman_composite_trapezoids, arginfo_pixman_composite_trapezoids)
	ZEND_FE(pixman_composite_triangles, arginfo_pixman_composite_triangles)
	ZEND_FE(pixman_add_triangles, arginfo_pixman_add_triangles)
	ZEND_FE_END
};
