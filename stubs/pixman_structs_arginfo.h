/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 83f5b8420aa9091f2967ed67484f0ee44c29eda5 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_color___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, red, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, green, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, blue, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, alpha, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_point_fixed___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_line_fixed___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, p1, pixman_point_fixed, 1, "null")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, p2, pixman_point_fixed, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_vector___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, vector, IS_ARRAY, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_transform___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, matrix, IS_ARRAY, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_f_vector___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, v, IS_ARRAY, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_f_transform___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, m, IS_ARRAY, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_box16___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x1, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y1, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x2, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y2, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

#define arginfo_class_pixman_box32___construct arginfo_class_pixman_box16___construct

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_box64f___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x1, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y1, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x2, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y2, IS_DOUBLE, 0, "0.0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_rectangle16___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, width, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, height, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_gradient_stop___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_LONG, 0, "0")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, color, pixman_color, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_indexed___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, color, _IS_BOOL, 0, "false")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, rgba, IS_ARRAY, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, ent, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_glyph___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, glyph, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_edge___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, e, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, stepx, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, signdx, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, dy, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, dx, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, stepx_small, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, stepx_big, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, dx_small, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, dx_big, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_trapezoid___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, top, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, bottom, IS_LONG, 0, "0")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, left, pixman_line_fixed, 1, "null")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, right, pixman_line_fixed, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_triangle___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, p1, pixman_point_fixed, 1, "null")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, p2, pixman_point_fixed, 1, "null")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, p3, pixman_point_fixed, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_span_fix___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, l, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, r, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pixman_trap___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, top, pixman_span_fix, 1, "null")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, bot, pixman_span_fix, 1, "null")
ZEND_END_ARG_INFO()

ZEND_METHOD(pixman_color, __construct);
ZEND_METHOD(pixman_point_fixed, __construct);
ZEND_METHOD(pixman_line_fixed, __construct);
ZEND_METHOD(pixman_vector, __construct);
ZEND_METHOD(pixman_transform, __construct);
ZEND_METHOD(pixman_f_vector, __construct);
ZEND_METHOD(pixman_f_transform, __construct);
ZEND_METHOD(pixman_box16, __construct);
ZEND_METHOD(pixman_box32, __construct);
ZEND_METHOD(pixman_box64f, __construct);
ZEND_METHOD(pixman_rectangle16, __construct);
ZEND_METHOD(pixman_gradient_stop, __construct);
ZEND_METHOD(pixman_indexed, __construct);
ZEND_METHOD(pixman_glyph, __construct);
ZEND_METHOD(pixman_edge, __construct);
ZEND_METHOD(pixman_trapezoid, __construct);
ZEND_METHOD(pixman_triangle, __construct);
ZEND_METHOD(pixman_span_fix, __construct);
ZEND_METHOD(pixman_trap, __construct);

static const zend_function_entry class_pixman_color_methods[] = {
	ZEND_ME(pixman_color, __construct, arginfo_class_pixman_color___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_point_fixed_methods[] = {
	ZEND_ME(pixman_point_fixed, __construct, arginfo_class_pixman_point_fixed___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_line_fixed_methods[] = {
	ZEND_ME(pixman_line_fixed, __construct, arginfo_class_pixman_line_fixed___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_vector_methods[] = {
	ZEND_ME(pixman_vector, __construct, arginfo_class_pixman_vector___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_transform_methods[] = {
	ZEND_ME(pixman_transform, __construct, arginfo_class_pixman_transform___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_f_vector_methods[] = {
	ZEND_ME(pixman_f_vector, __construct, arginfo_class_pixman_f_vector___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_f_transform_methods[] = {
	ZEND_ME(pixman_f_transform, __construct, arginfo_class_pixman_f_transform___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_box16_methods[] = {
	ZEND_ME(pixman_box16, __construct, arginfo_class_pixman_box16___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_box32_methods[] = {
	ZEND_ME(pixman_box32, __construct, arginfo_class_pixman_box32___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_box64f_methods[] = {
	ZEND_ME(pixman_box64f, __construct, arginfo_class_pixman_box64f___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_rectangle16_methods[] = {
	ZEND_ME(pixman_rectangle16, __construct, arginfo_class_pixman_rectangle16___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_gradient_stop_methods[] = {
	ZEND_ME(pixman_gradient_stop, __construct, arginfo_class_pixman_gradient_stop___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_indexed_methods[] = {
	ZEND_ME(pixman_indexed, __construct, arginfo_class_pixman_indexed___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_glyph_methods[] = {
	ZEND_ME(pixman_glyph, __construct, arginfo_class_pixman_glyph___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_edge_methods[] = {
	ZEND_ME(pixman_edge, __construct, arginfo_class_pixman_edge___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_trapezoid_methods[] = {
	ZEND_ME(pixman_trapezoid, __construct, arginfo_class_pixman_trapezoid___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_triangle_methods[] = {
	ZEND_ME(pixman_triangle, __construct, arginfo_class_pixman_triangle___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_span_fix_methods[] = {
	ZEND_ME(pixman_span_fix, __construct, arginfo_class_pixman_span_fix___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_pixman_trap_methods[] = {
	ZEND_ME(pixman_trap, __construct, arginfo_class_pixman_trap___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_pixman_color(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_color", class_pixman_color_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_red_default_value;
	ZVAL_LONG(&property_red_default_value, 0);
	zend_string *property_red_name = zend_string_init("red", sizeof("red") - 1, 1);
	zend_declare_typed_property(class_entry, property_red_name, &property_red_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_red_name);

	zval property_green_default_value;
	ZVAL_LONG(&property_green_default_value, 0);
	zend_string *property_green_name = zend_string_init("green", sizeof("green") - 1, 1);
	zend_declare_typed_property(class_entry, property_green_name, &property_green_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_green_name);

	zval property_blue_default_value;
	ZVAL_LONG(&property_blue_default_value, 0);
	zend_string *property_blue_name = zend_string_init("blue", sizeof("blue") - 1, 1);
	zend_declare_typed_property(class_entry, property_blue_name, &property_blue_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_blue_name);

	zval property_alpha_default_value;
	ZVAL_LONG(&property_alpha_default_value, 0);
	zend_string *property_alpha_name = zend_string_init("alpha", sizeof("alpha") - 1, 1);
	zend_declare_typed_property(class_entry, property_alpha_name, &property_alpha_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_alpha_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_point_fixed(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_point_fixed", class_pixman_point_fixed_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x_default_value;
	ZVAL_LONG(&property_x_default_value, 0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_LONG(&property_y_default_value, 0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_line_fixed(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_line_fixed", class_pixman_line_fixed_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_p1_default_value;
	ZVAL_UNDEF(&property_p1_default_value);
	zend_string *property_p1_name = zend_string_init("p1", sizeof("p1") - 1, 1);
	zend_string *property_p1_class_pixman_point_fixed = zend_string_init("pixman_point_fixed", sizeof("pixman_point_fixed")-1, 1);
	zend_declare_typed_property(class_entry, property_p1_name, &property_p1_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_p1_class_pixman_point_fixed, 0, 0));
	zend_string_release(property_p1_name);

	zval property_p2_default_value;
	ZVAL_UNDEF(&property_p2_default_value);
	zend_string *property_p2_name = zend_string_init("p2", sizeof("p2") - 1, 1);
	zend_string *property_p2_class_pixman_point_fixed = zend_string_init("pixman_point_fixed", sizeof("pixman_point_fixed")-1, 1);
	zend_declare_typed_property(class_entry, property_p2_name, &property_p2_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_p2_class_pixman_point_fixed, 0, 0));
	zend_string_release(property_p2_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_vector(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_vector", class_pixman_vector_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_vector_default_value;
	ZVAL_EMPTY_ARRAY(&property_vector_default_value);
	zend_string *property_vector_name = zend_string_init("vector", sizeof("vector") - 1, 1);
	zend_declare_typed_property(class_entry, property_vector_name, &property_vector_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_vector_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_transform(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_transform", class_pixman_transform_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_matrix_default_value;
	ZVAL_EMPTY_ARRAY(&property_matrix_default_value);
	zend_string *property_matrix_name = zend_string_init("matrix", sizeof("matrix") - 1, 1);
	zend_declare_typed_property(class_entry, property_matrix_name, &property_matrix_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_matrix_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_f_vector(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_f_vector", class_pixman_f_vector_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_v_default_value;
	ZVAL_EMPTY_ARRAY(&property_v_default_value);
	zend_string *property_v_name = zend_string_init("v", sizeof("v") - 1, 1);
	zend_declare_typed_property(class_entry, property_v_name, &property_v_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_v_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_f_transform(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_f_transform", class_pixman_f_transform_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_m_default_value;
	ZVAL_EMPTY_ARRAY(&property_m_default_value);
	zend_string *property_m_name = zend_string_init("m", sizeof("m") - 1, 1);
	zend_declare_typed_property(class_entry, property_m_name, &property_m_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_m_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_box16(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_box16", class_pixman_box16_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x1_default_value;
	ZVAL_LONG(&property_x1_default_value, 0);
	zend_string *property_x1_name = zend_string_init("x1", sizeof("x1") - 1, 1);
	zend_declare_typed_property(class_entry, property_x1_name, &property_x1_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x1_name);

	zval property_y1_default_value;
	ZVAL_LONG(&property_y1_default_value, 0);
	zend_string *property_y1_name = zend_string_init("y1", sizeof("y1") - 1, 1);
	zend_declare_typed_property(class_entry, property_y1_name, &property_y1_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y1_name);

	zval property_x2_default_value;
	ZVAL_LONG(&property_x2_default_value, 0);
	zend_string *property_x2_name = zend_string_init("x2", sizeof("x2") - 1, 1);
	zend_declare_typed_property(class_entry, property_x2_name, &property_x2_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x2_name);

	zval property_y2_default_value;
	ZVAL_LONG(&property_y2_default_value, 0);
	zend_string *property_y2_name = zend_string_init("y2", sizeof("y2") - 1, 1);
	zend_declare_typed_property(class_entry, property_y2_name, &property_y2_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y2_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_box32(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_box32", class_pixman_box32_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x1_default_value;
	ZVAL_LONG(&property_x1_default_value, 0);
	zend_string *property_x1_name = zend_string_init("x1", sizeof("x1") - 1, 1);
	zend_declare_typed_property(class_entry, property_x1_name, &property_x1_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x1_name);

	zval property_y1_default_value;
	ZVAL_LONG(&property_y1_default_value, 0);
	zend_string *property_y1_name = zend_string_init("y1", sizeof("y1") - 1, 1);
	zend_declare_typed_property(class_entry, property_y1_name, &property_y1_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y1_name);

	zval property_x2_default_value;
	ZVAL_LONG(&property_x2_default_value, 0);
	zend_string *property_x2_name = zend_string_init("x2", sizeof("x2") - 1, 1);
	zend_declare_typed_property(class_entry, property_x2_name, &property_x2_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x2_name);

	zval property_y2_default_value;
	ZVAL_LONG(&property_y2_default_value, 0);
	zend_string *property_y2_name = zend_string_init("y2", sizeof("y2") - 1, 1);
	zend_declare_typed_property(class_entry, property_y2_name, &property_y2_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y2_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_box64f(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_box64f", class_pixman_box64f_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x1_default_value;
	ZVAL_DOUBLE(&property_x1_default_value, 0.0);
	zend_string *property_x1_name = zend_string_init("x1", sizeof("x1") - 1, 1);
	zend_declare_typed_property(class_entry, property_x1_name, &property_x1_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_x1_name);

	zval property_y1_default_value;
	ZVAL_DOUBLE(&property_y1_default_value, 0.0);
	zend_string *property_y1_name = zend_string_init("y1", sizeof("y1") - 1, 1);
	zend_declare_typed_property(class_entry, property_y1_name, &property_y1_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_y1_name);

	zval property_x2_default_value;
	ZVAL_DOUBLE(&property_x2_default_value, 0.0);
	zend_string *property_x2_name = zend_string_init("x2", sizeof("x2") - 1, 1);
	zend_declare_typed_property(class_entry, property_x2_name, &property_x2_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_x2_name);

	zval property_y2_default_value;
	ZVAL_DOUBLE(&property_y2_default_value, 0.0);
	zend_string *property_y2_name = zend_string_init("y2", sizeof("y2") - 1, 1);
	zend_declare_typed_property(class_entry, property_y2_name, &property_y2_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_y2_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_rectangle16(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_rectangle16", class_pixman_rectangle16_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x_default_value;
	ZVAL_LONG(&property_x_default_value, 0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_LONG(&property_y_default_value, 0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y_name);

	zval property_width_default_value;
	ZVAL_LONG(&property_width_default_value, 0);
	zend_string *property_width_name = zend_string_init("width", sizeof("width") - 1, 1);
	zend_declare_typed_property(class_entry, property_width_name, &property_width_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_width_name);

	zval property_height_default_value;
	ZVAL_LONG(&property_height_default_value, 0);
	zend_string *property_height_name = zend_string_init("height", sizeof("height") - 1, 1);
	zend_declare_typed_property(class_entry, property_height_name, &property_height_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_height_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_gradient_stop(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_gradient_stop", class_pixman_gradient_stop_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x_default_value;
	ZVAL_LONG(&property_x_default_value, 0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_color_default_value;
	ZVAL_UNDEF(&property_color_default_value);
	zend_string *property_color_name = zend_string_init("color", sizeof("color") - 1, 1);
	zend_string *property_color_class_pixman_color = zend_string_init("pixman_color", sizeof("pixman_color")-1, 1);
	zend_declare_typed_property(class_entry, property_color_name, &property_color_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_color_class_pixman_color, 0, 0));
	zend_string_release(property_color_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_indexed(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_indexed", class_pixman_indexed_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_color_default_value;
	ZVAL_FALSE(&property_color_default_value);
	zend_string *property_color_name = zend_string_init("color", sizeof("color") - 1, 1);
	zend_declare_typed_property(class_entry, property_color_name, &property_color_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_color_name);

	zval property_rgba_default_value;
	ZVAL_EMPTY_ARRAY(&property_rgba_default_value);
	zend_string *property_rgba_name = zend_string_init("rgba", sizeof("rgba") - 1, 1);
	zend_declare_typed_property(class_entry, property_rgba_name, &property_rgba_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_rgba_name);

	zval property_ent_default_value;
	ZVAL_EMPTY_STRING(&property_ent_default_value);
	zend_string *property_ent_name = zend_string_init("ent", sizeof("ent") - 1, 1);
	zend_declare_typed_property(class_entry, property_ent_name, &property_ent_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
	zend_string_release(property_ent_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_glyph(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_glyph", class_pixman_glyph_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x_default_value;
	ZVAL_LONG(&property_x_default_value, 0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_LONG(&property_y_default_value, 0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y_name);

	zval property_glyph_default_value;
	ZVAL_LONG(&property_glyph_default_value, 0);
	zend_string *property_glyph_name = zend_string_init("glyph", sizeof("glyph") - 1, 1);
	zend_declare_typed_property(class_entry, property_glyph_name, &property_glyph_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_glyph_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_edge(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_edge", class_pixman_edge_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x_default_value;
	ZVAL_LONG(&property_x_default_value, 0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_e_default_value;
	ZVAL_LONG(&property_e_default_value, 0);
	zend_string *property_e_name = zend_string_init("e", sizeof("e") - 1, 1);
	zend_declare_typed_property(class_entry, property_e_name, &property_e_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_e_name);

	zval property_stepx_default_value;
	ZVAL_LONG(&property_stepx_default_value, 0);
	zend_string *property_stepx_name = zend_string_init("stepx", sizeof("stepx") - 1, 1);
	zend_declare_typed_property(class_entry, property_stepx_name, &property_stepx_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_stepx_name);

	zval property_signdx_default_value;
	ZVAL_LONG(&property_signdx_default_value, 0);
	zend_string *property_signdx_name = zend_string_init("signdx", sizeof("signdx") - 1, 1);
	zend_declare_typed_property(class_entry, property_signdx_name, &property_signdx_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_signdx_name);

	zval property_dy_default_value;
	ZVAL_LONG(&property_dy_default_value, 0);
	zend_string *property_dy_name = zend_string_init("dy", sizeof("dy") - 1, 1);
	zend_declare_typed_property(class_entry, property_dy_name, &property_dy_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_dy_name);

	zval property_dx_default_value;
	ZVAL_LONG(&property_dx_default_value, 0);
	zend_string *property_dx_name = zend_string_init("dx", sizeof("dx") - 1, 1);
	zend_declare_typed_property(class_entry, property_dx_name, &property_dx_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_dx_name);

	zval property_stepx_small_default_value;
	ZVAL_LONG(&property_stepx_small_default_value, 0);
	zend_string *property_stepx_small_name = zend_string_init("stepx_small", sizeof("stepx_small") - 1, 1);
	zend_declare_typed_property(class_entry, property_stepx_small_name, &property_stepx_small_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_stepx_small_name);

	zval property_stepx_big_default_value;
	ZVAL_LONG(&property_stepx_big_default_value, 0);
	zend_string *property_stepx_big_name = zend_string_init("stepx_big", sizeof("stepx_big") - 1, 1);
	zend_declare_typed_property(class_entry, property_stepx_big_name, &property_stepx_big_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_stepx_big_name);

	zval property_dx_small_default_value;
	ZVAL_LONG(&property_dx_small_default_value, 0);
	zend_string *property_dx_small_name = zend_string_init("dx_small", sizeof("dx_small") - 1, 1);
	zend_declare_typed_property(class_entry, property_dx_small_name, &property_dx_small_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_dx_small_name);

	zval property_dx_big_default_value;
	ZVAL_LONG(&property_dx_big_default_value, 0);
	zend_string *property_dx_big_name = zend_string_init("dx_big", sizeof("dx_big") - 1, 1);
	zend_declare_typed_property(class_entry, property_dx_big_name, &property_dx_big_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_dx_big_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_trapezoid(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_trapezoid", class_pixman_trapezoid_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_top_default_value;
	ZVAL_LONG(&property_top_default_value, 0);
	zend_string *property_top_name = zend_string_init("top", sizeof("top") - 1, 1);
	zend_declare_typed_property(class_entry, property_top_name, &property_top_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_top_name);

	zval property_bottom_default_value;
	ZVAL_LONG(&property_bottom_default_value, 0);
	zend_string *property_bottom_name = zend_string_init("bottom", sizeof("bottom") - 1, 1);
	zend_declare_typed_property(class_entry, property_bottom_name, &property_bottom_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_bottom_name);

	zval property_left_default_value;
	ZVAL_UNDEF(&property_left_default_value);
	zend_string *property_left_name = zend_string_init("left", sizeof("left") - 1, 1);
	zend_string *property_left_class_pixman_line_fixed = zend_string_init("pixman_line_fixed", sizeof("pixman_line_fixed")-1, 1);
	zend_declare_typed_property(class_entry, property_left_name, &property_left_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_left_class_pixman_line_fixed, 0, 0));
	zend_string_release(property_left_name);

	zval property_right_default_value;
	ZVAL_UNDEF(&property_right_default_value);
	zend_string *property_right_name = zend_string_init("right", sizeof("right") - 1, 1);
	zend_string *property_right_class_pixman_line_fixed = zend_string_init("pixman_line_fixed", sizeof("pixman_line_fixed")-1, 1);
	zend_declare_typed_property(class_entry, property_right_name, &property_right_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_right_class_pixman_line_fixed, 0, 0));
	zend_string_release(property_right_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_triangle(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_triangle", class_pixman_triangle_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_p1_default_value;
	ZVAL_UNDEF(&property_p1_default_value);
	zend_string *property_p1_name = zend_string_init("p1", sizeof("p1") - 1, 1);
	zend_string *property_p1_class_pixman_point_fixed = zend_string_init("pixman_point_fixed", sizeof("pixman_point_fixed")-1, 1);
	zend_declare_typed_property(class_entry, property_p1_name, &property_p1_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_p1_class_pixman_point_fixed, 0, 0));
	zend_string_release(property_p1_name);

	zval property_p2_default_value;
	ZVAL_UNDEF(&property_p2_default_value);
	zend_string *property_p2_name = zend_string_init("p2", sizeof("p2") - 1, 1);
	zend_string *property_p2_class_pixman_point_fixed = zend_string_init("pixman_point_fixed", sizeof("pixman_point_fixed")-1, 1);
	zend_declare_typed_property(class_entry, property_p2_name, &property_p2_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_p2_class_pixman_point_fixed, 0, 0));
	zend_string_release(property_p2_name);

	zval property_p3_default_value;
	ZVAL_UNDEF(&property_p3_default_value);
	zend_string *property_p3_name = zend_string_init("p3", sizeof("p3") - 1, 1);
	zend_string *property_p3_class_pixman_point_fixed = zend_string_init("pixman_point_fixed", sizeof("pixman_point_fixed")-1, 1);
	zend_declare_typed_property(class_entry, property_p3_name, &property_p3_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_p3_class_pixman_point_fixed, 0, 0));
	zend_string_release(property_p3_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_span_fix(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_span_fix", class_pixman_span_fix_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_l_default_value;
	ZVAL_LONG(&property_l_default_value, 0);
	zend_string *property_l_name = zend_string_init("l", sizeof("l") - 1, 1);
	zend_declare_typed_property(class_entry, property_l_name, &property_l_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_l_name);

	zval property_r_default_value;
	ZVAL_LONG(&property_r_default_value, 0);
	zend_string *property_r_name = zend_string_init("r", sizeof("r") - 1, 1);
	zend_declare_typed_property(class_entry, property_r_name, &property_r_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_r_name);

	zval property_y_default_value;
	ZVAL_LONG(&property_y_default_value, 0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_trap(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_trap", class_pixman_trap_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_top_default_value;
	ZVAL_UNDEF(&property_top_default_value);
	zend_string *property_top_name = zend_string_init("top", sizeof("top") - 1, 1);
	zend_string *property_top_class_pixman_span_fix = zend_string_init("pixman_span_fix", sizeof("pixman_span_fix")-1, 1);
	zend_declare_typed_property(class_entry, property_top_name, &property_top_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_top_class_pixman_span_fix, 0, 0));
	zend_string_release(property_top_name);

	zval property_bot_default_value;
	ZVAL_UNDEF(&property_bot_default_value);
	zend_string *property_bot_name = zend_string_init("bot", sizeof("bot") - 1, 1);
	zend_string *property_bot_class_pixman_span_fix = zend_string_init("pixman_span_fix", sizeof("pixman_span_fix")-1, 1);
	zend_declare_typed_property(class_entry, property_bot_name, &property_bot_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_bot_class_pixman_span_fix, 0, 0));
	zend_string_release(property_bot_name);

	return class_entry;
}

static zend_class_entry *register_class_pixman_image(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_image", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_pixman_region16(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_region16", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_pixman_region32(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_region32", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_pixman_region64f(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_region64f", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_pixman_glyph_cache(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "pixman_glyph_cache", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}
