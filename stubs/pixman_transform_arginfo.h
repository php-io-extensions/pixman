/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 8ff9d51e07c8a9d906a249e4b75deea2b3c5a0bb */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_init_identity, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, matrix, pixman_transform, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_point_3d, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, transform, pixman_transform, 0)
	ZEND_ARG_OBJ_INFO(0, vector, pixman_vector, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_transform_point arginfo_pixman_transform_point_3d

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_multiply, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, dst, pixman_transform, 0)
	ZEND_ARG_OBJ_INFO(0, l, pixman_transform, 0)
	ZEND_ARG_OBJ_INFO(0, r, pixman_transform, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_init_scale, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_transform, 0)
	ZEND_ARG_TYPE_INFO(0, sx, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sy, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_scale, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, forward, pixman_transform, 1)
	ZEND_ARG_OBJ_INFO(0, reverse, pixman_transform, 1)
	ZEND_ARG_TYPE_INFO(0, sx, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sy, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_init_rotate, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_transform, 0)
	ZEND_ARG_TYPE_INFO(0, cos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sin, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_rotate, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, forward, pixman_transform, 1)
	ZEND_ARG_OBJ_INFO(0, reverse, pixman_transform, 1)
	ZEND_ARG_TYPE_INFO(0, c, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_init_translate, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_transform, 0)
	ZEND_ARG_TYPE_INFO(0, tx, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ty, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_translate, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, forward, pixman_transform, 1)
	ZEND_ARG_OBJ_INFO(0, reverse, pixman_transform, 1)
	ZEND_ARG_TYPE_INFO(0, tx, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ty, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_bounds, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, matrix, pixman_transform, 0)
	ZEND_ARG_OBJ_INFO(0, b, pixman_box16, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_invert, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, dst, pixman_transform, 0)
	ZEND_ARG_OBJ_INFO(0, src, pixman_transform, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_is_identity, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_transform, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_transform_is_scale arginfo_pixman_transform_is_identity

#define arginfo_pixman_transform_is_int_translate arginfo_pixman_transform_is_identity

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_is_inverse, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, a, pixman_transform, 0)
	ZEND_ARG_OBJ_INFO(0, b, pixman_transform, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_transform_from_pixman_f_transform, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_transform, 0)
	ZEND_ARG_OBJ_INFO(0, ft, pixman_f_transform, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_from_pixman_transform, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, ft, pixman_f_transform, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_transform, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_invert, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, dst, pixman_f_transform, 0)
	ZEND_ARG_OBJ_INFO(0, src, pixman_f_transform, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_point, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_f_transform, 0)
	ZEND_ARG_OBJ_INFO(0, v, pixman_f_vector, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_point_3d, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_f_transform, 0)
	ZEND_ARG_OBJ_INFO(0, v, pixman_f_vector, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_multiply, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, dst, pixman_f_transform, 0)
	ZEND_ARG_OBJ_INFO(0, l, pixman_f_transform, 0)
	ZEND_ARG_OBJ_INFO(0, r, pixman_f_transform, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_init_scale, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_f_transform, 0)
	ZEND_ARG_TYPE_INFO(0, sx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_scale, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, forward, pixman_f_transform, 1)
	ZEND_ARG_OBJ_INFO(0, reverse, pixman_f_transform, 1)
	ZEND_ARG_TYPE_INFO(0, sx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_init_rotate, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_f_transform, 0)
	ZEND_ARG_TYPE_INFO(0, cos, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sin, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_rotate, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, forward, pixman_f_transform, 1)
	ZEND_ARG_OBJ_INFO(0, reverse, pixman_f_transform, 1)
	ZEND_ARG_TYPE_INFO(0, c, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_init_translate, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_f_transform, 0)
	ZEND_ARG_TYPE_INFO(0, tx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ty, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_translate, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, forward, pixman_f_transform, 1)
	ZEND_ARG_OBJ_INFO(0, reverse, pixman_f_transform, 1)
	ZEND_ARG_TYPE_INFO(0, tx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ty, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_bounds, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_f_transform, 0)
	ZEND_ARG_OBJ_INFO(0, b, pixman_box16, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_f_transform_init_identity, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, t, pixman_f_transform, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(pixman_transform_init_identity);
ZEND_FUNCTION(pixman_transform_point_3d);
ZEND_FUNCTION(pixman_transform_point);
ZEND_FUNCTION(pixman_transform_multiply);
ZEND_FUNCTION(pixman_transform_init_scale);
ZEND_FUNCTION(pixman_transform_scale);
ZEND_FUNCTION(pixman_transform_init_rotate);
ZEND_FUNCTION(pixman_transform_rotate);
ZEND_FUNCTION(pixman_transform_init_translate);
ZEND_FUNCTION(pixman_transform_translate);
ZEND_FUNCTION(pixman_transform_bounds);
ZEND_FUNCTION(pixman_transform_invert);
ZEND_FUNCTION(pixman_transform_is_identity);
ZEND_FUNCTION(pixman_transform_is_scale);
ZEND_FUNCTION(pixman_transform_is_int_translate);
ZEND_FUNCTION(pixman_transform_is_inverse);
ZEND_FUNCTION(pixman_transform_from_pixman_f_transform);
ZEND_FUNCTION(pixman_f_transform_from_pixman_transform);
ZEND_FUNCTION(pixman_f_transform_invert);
ZEND_FUNCTION(pixman_f_transform_point);
ZEND_FUNCTION(pixman_f_transform_point_3d);
ZEND_FUNCTION(pixman_f_transform_multiply);
ZEND_FUNCTION(pixman_f_transform_init_scale);
ZEND_FUNCTION(pixman_f_transform_scale);
ZEND_FUNCTION(pixman_f_transform_init_rotate);
ZEND_FUNCTION(pixman_f_transform_rotate);
ZEND_FUNCTION(pixman_f_transform_init_translate);
ZEND_FUNCTION(pixman_f_transform_translate);
ZEND_FUNCTION(pixman_f_transform_bounds);
ZEND_FUNCTION(pixman_f_transform_init_identity);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(pixman_transform_init_identity, arginfo_pixman_transform_init_identity)
	ZEND_FE(pixman_transform_point_3d, arginfo_pixman_transform_point_3d)
	ZEND_FE(pixman_transform_point, arginfo_pixman_transform_point)
	ZEND_FE(pixman_transform_multiply, arginfo_pixman_transform_multiply)
	ZEND_FE(pixman_transform_init_scale, arginfo_pixman_transform_init_scale)
	ZEND_FE(pixman_transform_scale, arginfo_pixman_transform_scale)
	ZEND_FE(pixman_transform_init_rotate, arginfo_pixman_transform_init_rotate)
	ZEND_FE(pixman_transform_rotate, arginfo_pixman_transform_rotate)
	ZEND_FE(pixman_transform_init_translate, arginfo_pixman_transform_init_translate)
	ZEND_FE(pixman_transform_translate, arginfo_pixman_transform_translate)
	ZEND_FE(pixman_transform_bounds, arginfo_pixman_transform_bounds)
	ZEND_FE(pixman_transform_invert, arginfo_pixman_transform_invert)
	ZEND_FE(pixman_transform_is_identity, arginfo_pixman_transform_is_identity)
	ZEND_FE(pixman_transform_is_scale, arginfo_pixman_transform_is_scale)
	ZEND_FE(pixman_transform_is_int_translate, arginfo_pixman_transform_is_int_translate)
	ZEND_FE(pixman_transform_is_inverse, arginfo_pixman_transform_is_inverse)
	ZEND_FE(pixman_transform_from_pixman_f_transform, arginfo_pixman_transform_from_pixman_f_transform)
	ZEND_FE(pixman_f_transform_from_pixman_transform, arginfo_pixman_f_transform_from_pixman_transform)
	ZEND_FE(pixman_f_transform_invert, arginfo_pixman_f_transform_invert)
	ZEND_FE(pixman_f_transform_point, arginfo_pixman_f_transform_point)
	ZEND_FE(pixman_f_transform_point_3d, arginfo_pixman_f_transform_point_3d)
	ZEND_FE(pixman_f_transform_multiply, arginfo_pixman_f_transform_multiply)
	ZEND_FE(pixman_f_transform_init_scale, arginfo_pixman_f_transform_init_scale)
	ZEND_FE(pixman_f_transform_scale, arginfo_pixman_f_transform_scale)
	ZEND_FE(pixman_f_transform_init_rotate, arginfo_pixman_f_transform_init_rotate)
	ZEND_FE(pixman_f_transform_rotate, arginfo_pixman_f_transform_rotate)
	ZEND_FE(pixman_f_transform_init_translate, arginfo_pixman_f_transform_init_translate)
	ZEND_FE(pixman_f_transform_translate, arginfo_pixman_f_transform_translate)
	ZEND_FE(pixman_f_transform_bounds, arginfo_pixman_f_transform_bounds)
	ZEND_FE(pixman_f_transform_init_identity, arginfo_pixman_f_transform_init_identity)
	ZEND_FE_END
};
