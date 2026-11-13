/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: e3849ea21c404f534e74009fecbdddd0c3959771 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_init, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_init_rect, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_init_rects, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_TYPE_INFO(0, boxes, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_init_with_extents, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, extents, pixman_box64f, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_init_from_image, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, image, pixman_image, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region64f_fini arginfo_pixman_region64f_init

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_translate, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_copy, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, dest, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, source, pixman_region64f, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_intersect, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, new_reg, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, reg1, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, reg2, pixman_region64f, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region64f_union arginfo_pixman_region64f_intersect

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_intersect_rect, 0, 6, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, dest, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, source, pixman_region64f, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region64f_union_rect arginfo_pixman_region64f_intersect_rect

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_subtract, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, reg_d, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, reg_m, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, reg_s, pixman_region64f, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_inverse, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, new_reg, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, reg1, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, inv_rect, pixman_box64f, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_contains_point, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, box, pixman_box64f, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_contains_rectangle, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, prect, pixman_box64f, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_empty, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region64f_not_empty arginfo_pixman_region64f_empty

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_pixman_region64f_extents, 0, 1, pixman_box64f, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_n_rects, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_rectangles, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_TYPE_INFO(1, n_rects, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_equal, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, region1, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, region2, pixman_region64f, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region64f_selfcheck arginfo_pixman_region64f_empty

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_reset, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, box, pixman_box64f, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region64f_clear arginfo_pixman_region64f_init

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_init_rectf, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_translatef, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_intersect_rectf, 0, 6, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, dest, pixman_region64f, 0)
	ZEND_ARG_OBJ_INFO(0, source, pixman_region64f, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_region64f_union_rectf arginfo_pixman_region64f_intersect_rectf

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_region64f_contains_pointf, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, region, pixman_region64f, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, box, pixman_box64f, 1)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(pixman_region64f_init);
ZEND_FUNCTION(pixman_region64f_init_rect);
ZEND_FUNCTION(pixman_region64f_init_rects);
ZEND_FUNCTION(pixman_region64f_init_with_extents);
ZEND_FUNCTION(pixman_region64f_init_from_image);
ZEND_FUNCTION(pixman_region64f_fini);
ZEND_FUNCTION(pixman_region64f_translate);
ZEND_FUNCTION(pixman_region64f_copy);
ZEND_FUNCTION(pixman_region64f_intersect);
ZEND_FUNCTION(pixman_region64f_union);
ZEND_FUNCTION(pixman_region64f_intersect_rect);
ZEND_FUNCTION(pixman_region64f_union_rect);
ZEND_FUNCTION(pixman_region64f_subtract);
ZEND_FUNCTION(pixman_region64f_inverse);
ZEND_FUNCTION(pixman_region64f_contains_point);
ZEND_FUNCTION(pixman_region64f_contains_rectangle);
ZEND_FUNCTION(pixman_region64f_empty);
ZEND_FUNCTION(pixman_region64f_not_empty);
ZEND_FUNCTION(pixman_region64f_extents);
ZEND_FUNCTION(pixman_region64f_n_rects);
ZEND_FUNCTION(pixman_region64f_rectangles);
ZEND_FUNCTION(pixman_region64f_equal);
ZEND_FUNCTION(pixman_region64f_selfcheck);
ZEND_FUNCTION(pixman_region64f_reset);
ZEND_FUNCTION(pixman_region64f_clear);
ZEND_FUNCTION(pixman_region64f_init_rectf);
ZEND_FUNCTION(pixman_region64f_translatef);
ZEND_FUNCTION(pixman_region64f_intersect_rectf);
ZEND_FUNCTION(pixman_region64f_union_rectf);
ZEND_FUNCTION(pixman_region64f_contains_pointf);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(pixman_region64f_init, arginfo_pixman_region64f_init)
	ZEND_FE(pixman_region64f_init_rect, arginfo_pixman_region64f_init_rect)
	ZEND_FE(pixman_region64f_init_rects, arginfo_pixman_region64f_init_rects)
	ZEND_FE(pixman_region64f_init_with_extents, arginfo_pixman_region64f_init_with_extents)
	ZEND_FE(pixman_region64f_init_from_image, arginfo_pixman_region64f_init_from_image)
	ZEND_FE(pixman_region64f_fini, arginfo_pixman_region64f_fini)
	ZEND_FE(pixman_region64f_translate, arginfo_pixman_region64f_translate)
	ZEND_FE(pixman_region64f_copy, arginfo_pixman_region64f_copy)
	ZEND_FE(pixman_region64f_intersect, arginfo_pixman_region64f_intersect)
	ZEND_FE(pixman_region64f_union, arginfo_pixman_region64f_union)
	ZEND_FE(pixman_region64f_intersect_rect, arginfo_pixman_region64f_intersect_rect)
	ZEND_FE(pixman_region64f_union_rect, arginfo_pixman_region64f_union_rect)
	ZEND_FE(pixman_region64f_subtract, arginfo_pixman_region64f_subtract)
	ZEND_FE(pixman_region64f_inverse, arginfo_pixman_region64f_inverse)
	ZEND_FE(pixman_region64f_contains_point, arginfo_pixman_region64f_contains_point)
	ZEND_FE(pixman_region64f_contains_rectangle, arginfo_pixman_region64f_contains_rectangle)
	ZEND_FE(pixman_region64f_empty, arginfo_pixman_region64f_empty)
	ZEND_FE(pixman_region64f_not_empty, arginfo_pixman_region64f_not_empty)
	ZEND_FE(pixman_region64f_extents, arginfo_pixman_region64f_extents)
	ZEND_FE(pixman_region64f_n_rects, arginfo_pixman_region64f_n_rects)
	ZEND_FE(pixman_region64f_rectangles, arginfo_pixman_region64f_rectangles)
	ZEND_FE(pixman_region64f_equal, arginfo_pixman_region64f_equal)
	ZEND_FE(pixman_region64f_selfcheck, arginfo_pixman_region64f_selfcheck)
	ZEND_FE(pixman_region64f_reset, arginfo_pixman_region64f_reset)
	ZEND_FE(pixman_region64f_clear, arginfo_pixman_region64f_clear)
	ZEND_FE(pixman_region64f_init_rectf, arginfo_pixman_region64f_init_rectf)
	ZEND_FE(pixman_region64f_translatef, arginfo_pixman_region64f_translatef)
	ZEND_FE(pixman_region64f_intersect_rectf, arginfo_pixman_region64f_intersect_rectf)
	ZEND_FE(pixman_region64f_union_rectf, arginfo_pixman_region64f_union_rectf)
	ZEND_FE(pixman_region64f_contains_pointf, arginfo_pixman_region64f_contains_pointf)
	ZEND_FE_END
};
