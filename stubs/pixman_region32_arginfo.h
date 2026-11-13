/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 72f43045cf62772a1ff6a0448ed147793360806f */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_init, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_init_rect, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_init_rects, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
	ZEND_ARG_TYPE_INFO(0, boxes, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_init_with_extents, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, extents, pixman_box32, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_init_from_image, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region32_fini arginfo_pixman_region32_init

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_translate, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_copy, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, dest, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, source, pixman_region32, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_intersect, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, new_reg, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, reg1, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, reg2, pixman_region32, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region32_union arginfo_pixman_region32_intersect

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_intersect_rect, 0, 6, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, dest, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, source, pixman_region32, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region32_union_rect arginfo_pixman_region32_intersect_rect

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_subtract, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, reg_d, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, reg_m, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, reg_s, pixman_region32, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_inverse, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, new_reg, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, reg1, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, inv_rect, pixman_box32, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_contains_point, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, box, pixman_box32, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_contains_rectangle, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, prect, pixman_box32, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_empty, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region32_not_empty arginfo_pixman_region32_empty

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_pixman_region32_extents, 0, 1, pixman_box32, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_n_rects, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_rectangles, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
	ZEND_ARG_TYPE_INFO(1, n_rects, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_equal, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, region1, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, region2, pixman_region32, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region32_selfcheck arginfo_pixman_region32_empty

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region32_reset, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region32, 0)
	ZEND_ARG_OBJ_INFO(0, box, pixman_box32, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region32_clear arginfo_pixman_region32_init

ZEND_FUNCTION(pixman_region32_init);
ZEND_FUNCTION(pixman_region32_init_rect);
ZEND_FUNCTION(pixman_region32_init_rects);
ZEND_FUNCTION(pixman_region32_init_with_extents);
ZEND_FUNCTION(pixman_region32_init_from_image);
ZEND_FUNCTION(pixman_region32_fini);
ZEND_FUNCTION(pixman_region32_translate);
ZEND_FUNCTION(pixman_region32_copy);
ZEND_FUNCTION(pixman_region32_intersect);
ZEND_FUNCTION(pixman_region32_union);
ZEND_FUNCTION(pixman_region32_intersect_rect);
ZEND_FUNCTION(pixman_region32_union_rect);
ZEND_FUNCTION(pixman_region32_subtract);
ZEND_FUNCTION(pixman_region32_inverse);
ZEND_FUNCTION(pixman_region32_contains_point);
ZEND_FUNCTION(pixman_region32_contains_rectangle);
ZEND_FUNCTION(pixman_region32_empty);
ZEND_FUNCTION(pixman_region32_not_empty);
ZEND_FUNCTION(pixman_region32_extents);
ZEND_FUNCTION(pixman_region32_n_rects);
ZEND_FUNCTION(pixman_region32_rectangles);
ZEND_FUNCTION(pixman_region32_equal);
ZEND_FUNCTION(pixman_region32_selfcheck);
ZEND_FUNCTION(pixman_region32_reset);
ZEND_FUNCTION(pixman_region32_clear);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(pixman_region32_init, arginfo_pixman_region32_init)
	ZEND_FE(pixman_region32_init_rect, arginfo_pixman_region32_init_rect)
	ZEND_FE(pixman_region32_init_rects, arginfo_pixman_region32_init_rects)
	ZEND_FE(pixman_region32_init_with_extents, arginfo_pixman_region32_init_with_extents)
	ZEND_FE(pixman_region32_init_from_image, arginfo_pixman_region32_init_from_image)
	ZEND_FE(pixman_region32_fini, arginfo_pixman_region32_fini)
	ZEND_FE(pixman_region32_translate, arginfo_pixman_region32_translate)
	ZEND_FE(pixman_region32_copy, arginfo_pixman_region32_copy)
	ZEND_FE(pixman_region32_intersect, arginfo_pixman_region32_intersect)
	ZEND_FE(pixman_region32_union, arginfo_pixman_region32_union)
	ZEND_FE(pixman_region32_intersect_rect, arginfo_pixman_region32_intersect_rect)
	ZEND_FE(pixman_region32_union_rect, arginfo_pixman_region32_union_rect)
	ZEND_FE(pixman_region32_subtract, arginfo_pixman_region32_subtract)
	ZEND_FE(pixman_region32_inverse, arginfo_pixman_region32_inverse)
	ZEND_FE(pixman_region32_contains_point, arginfo_pixman_region32_contains_point)
	ZEND_FE(pixman_region32_contains_rectangle, arginfo_pixman_region32_contains_rectangle)
	ZEND_FE(pixman_region32_empty, arginfo_pixman_region32_empty)
	ZEND_FE(pixman_region32_not_empty, arginfo_pixman_region32_not_empty)
	ZEND_FE(pixman_region32_extents, arginfo_pixman_region32_extents)
	ZEND_FE(pixman_region32_n_rects, arginfo_pixman_region32_n_rects)
	ZEND_FE(pixman_region32_rectangles, arginfo_pixman_region32_rectangles)
	ZEND_FE(pixman_region32_equal, arginfo_pixman_region32_equal)
	ZEND_FE(pixman_region32_selfcheck, arginfo_pixman_region32_selfcheck)
	ZEND_FE(pixman_region32_reset, arginfo_pixman_region32_reset)
	ZEND_FE(pixman_region32_clear, arginfo_pixman_region32_clear)
	ZEND_FE_END
};
