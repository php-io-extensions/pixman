/*
 * The binding's shared machinery. See runtime.h and the design spec.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "runtime.h"
#include "../stubs/pixman_structs_arginfo.h"
#include "../stubs/pixman_constants_arginfo.h"

zend_class_entry *px_image_ce, *px_region16_ce, *px_region32_ce, *px_region64f_ce, *px_glyph_cache_ce;

static zend_class_entry *px_color_ce, *px_point_fixed_ce, *px_line_fixed_ce, *px_vector_ce, *px_transform_ce,
	*px_f_vector_ce, *px_f_transform_ce, *px_box16_ce, *px_box32_ce, *px_box64f_ce, *px_rectangle16_ce,
	*px_gradient_stop_ce, *px_indexed_ce, *px_glyph_ce, *px_edge_ce, *px_trapezoid_ce, *px_triangle_ce,
	*px_span_fix_ce, *px_trap_ce;

/* ---- struct tables ---------------------------------------------------- */

#define F(t, field, kind) { #field, kind, offsetof(t, field), 0, NULL }
#define FN(t, field, kind, count) { #field, kind, offsetof(t, field), count, NULL }
#define FS(t, field, sub) { #field, PX_STRUCT, offsetof(t, field), 0, &sub }
#define DEF(var, cname, t, fields, ce) const px_struct var = { cname, sizeof(t), fields, sizeof(fields) / sizeof(fields[0]), &ce }

static const px_field color_f[] = { F(pixman_color_t, red, PX_U16), F(pixman_color_t, green, PX_U16), F(pixman_color_t, blue, PX_U16), F(pixman_color_t, alpha, PX_U16) };
DEF(px_color, "pixman_color", pixman_color_t, color_f, px_color_ce);

static const px_field point_fixed_f[] = { F(pixman_point_fixed_t, x, PX_I32), F(pixman_point_fixed_t, y, PX_I32) };
DEF(px_point_fixed, "pixman_point_fixed", pixman_point_fixed_t, point_fixed_f, px_point_fixed_ce);

static const px_field line_fixed_f[] = { FS(pixman_line_fixed_t, p1, px_point_fixed), FS(pixman_line_fixed_t, p2, px_point_fixed) };
DEF(px_line_fixed, "pixman_line_fixed", pixman_line_fixed_t, line_fixed_f, px_line_fixed_ce);

static const px_field vector_f[] = { FN(pixman_vector_t, vector, PX_I32_ARR, 3) };
DEF(px_vector, "pixman_vector", pixman_vector_t, vector_f, px_vector_ce);

static const px_field transform_f[] = { FN(pixman_transform_t, matrix, PX_I32_MAT3, 3) };
DEF(px_transform, "pixman_transform", pixman_transform_t, transform_f, px_transform_ce);

static const px_field f_vector_f[] = { FN(pixman_f_vector_t, v, PX_F64_ARR, 3) };
DEF(px_f_vector, "pixman_f_vector", pixman_f_vector_t, f_vector_f, px_f_vector_ce);

static const px_field f_transform_f[] = { FN(pixman_f_transform_t, m, PX_F64_MAT3, 3) };
DEF(px_f_transform, "pixman_f_transform", pixman_f_transform_t, f_transform_f, px_f_transform_ce);

static const px_field box16_f[] = { F(pixman_box16_t, x1, PX_I16), F(pixman_box16_t, y1, PX_I16), F(pixman_box16_t, x2, PX_I16), F(pixman_box16_t, y2, PX_I16) };
DEF(px_box16, "pixman_box16", pixman_box16_t, box16_f, px_box16_ce);

static const px_field box32_f[] = { F(pixman_box32_t, x1, PX_I32), F(pixman_box32_t, y1, PX_I32), F(pixman_box32_t, x2, PX_I32), F(pixman_box32_t, y2, PX_I32) };
DEF(px_box32, "pixman_box32", pixman_box32_t, box32_f, px_box32_ce);

static const px_field box64f_f[] = { F(pixman_box64f_t, x1, PX_F64), F(pixman_box64f_t, y1, PX_F64), F(pixman_box64f_t, x2, PX_F64), F(pixman_box64f_t, y2, PX_F64) };
DEF(px_box64f, "pixman_box64f", pixman_box64f_t, box64f_f, px_box64f_ce);

static const px_field rectangle16_f[] = { F(pixman_rectangle16_t, x, PX_I16), F(pixman_rectangle16_t, y, PX_I16), F(pixman_rectangle16_t, width, PX_U16), F(pixman_rectangle16_t, height, PX_U16) };
DEF(px_rectangle16, "pixman_rectangle16", pixman_rectangle16_t, rectangle16_f, px_rectangle16_ce);

static const px_field gradient_stop_f[] = { F(pixman_gradient_stop_t, x, PX_I32), FS(pixman_gradient_stop_t, color, px_color) };
DEF(px_gradient_stop, "pixman_gradient_stop", pixman_gradient_stop_t, gradient_stop_f, px_gradient_stop_ce);

static const px_field indexed_f[] = { F(pixman_indexed_t, color, PX_BOOL), FN(pixman_indexed_t, rgba, PX_U32_ARR, PIXMAN_MAX_INDEXED), FN(pixman_indexed_t, ent, PX_BYTES, 32768) };
DEF(px_indexed, "pixman_indexed", pixman_indexed_t, indexed_f, px_indexed_ce);

static const px_field glyph_f[] = { F(pixman_glyph_t, x, PX_I32), F(pixman_glyph_t, y, PX_I32), F(pixman_glyph_t, glyph, PX_PTR) };
DEF(px_glyph, "pixman_glyph", pixman_glyph_t, glyph_f, px_glyph_ce);

static const px_field edge_f[] = {
	F(pixman_edge_t, x, PX_I32), F(pixman_edge_t, e, PX_I32), F(pixman_edge_t, stepx, PX_I32), F(pixman_edge_t, signdx, PX_I32),
	F(pixman_edge_t, dy, PX_I32), F(pixman_edge_t, dx, PX_I32), F(pixman_edge_t, stepx_small, PX_I32), F(pixman_edge_t, stepx_big, PX_I32),
	F(pixman_edge_t, dx_small, PX_I32), F(pixman_edge_t, dx_big, PX_I32)
};
DEF(px_edge, "pixman_edge", pixman_edge_t, edge_f, px_edge_ce);

static const px_field trapezoid_f[] = { F(pixman_trapezoid_t, top, PX_I32), F(pixman_trapezoid_t, bottom, PX_I32), FS(pixman_trapezoid_t, left, px_line_fixed), FS(pixman_trapezoid_t, right, px_line_fixed) };
DEF(px_trapezoid, "pixman_trapezoid", pixman_trapezoid_t, trapezoid_f, px_trapezoid_ce);

static const px_field triangle_f[] = { FS(pixman_triangle_t, p1, px_point_fixed), FS(pixman_triangle_t, p2, px_point_fixed), FS(pixman_triangle_t, p3, px_point_fixed) };
DEF(px_triangle, "pixman_triangle", pixman_triangle_t, triangle_f, px_triangle_ce);

static const px_field span_fix_f[] = { F(pixman_span_fix_t, l, PX_I32), F(pixman_span_fix_t, r, PX_I32), F(pixman_span_fix_t, y, PX_I32) };
DEF(px_span_fix, "pixman_span_fix", pixman_span_fix_t, span_fix_f, px_span_fix_ce);

static const px_field trap_f[] = { FS(pixman_trap_t, top, px_span_fix), FS(pixman_trap_t, bot, px_span_fix) };
DEF(px_trap, "pixman_trap", pixman_trap_t, trap_f, px_trap_ce);

#undef F
#undef FN
#undef FS
#undef DEF

/* ---- struct conversion ------------------------------------------------ */

static zval *px_prop(const px_struct *def, zend_object *obj, uint32_t i)
{
	(void) def;
	zval *v = OBJ_PROP_NUM(obj, i);
	ZVAL_DEREF(v);
	return v;
}

static bool px_long_in(const px_struct *def, const px_field *f, zval *v, zend_long min, zend_long max, zend_long *out)
{
	if (Z_TYPE_P(v) != IS_LONG) {
		zend_value_error("%s::$%s must be of type int", def->name, f->name);
		return false;
	}
	if (Z_LVAL_P(v) < min || Z_LVAL_P(v) > max) {
		zend_value_error("%s::$%s must be between " ZEND_LONG_FMT " and " ZEND_LONG_FMT ", " ZEND_LONG_FMT " given",
			def->name, f->name, min, max, Z_LVAL_P(v));
		return false;
	}
	*out = Z_LVAL_P(v);
	return true;
}

static bool px_double_of(const px_struct *def, const px_field *f, zval *v, double *out)
{
	ZVAL_DEREF(v);
	if (Z_TYPE_P(v) == IS_DOUBLE) {
		*out = Z_DVAL_P(v);
		return true;
	}
	if (Z_TYPE_P(v) == IS_LONG) {
		*out = (double) Z_LVAL_P(v);
		return true;
	}
	zend_value_error("%s::$%s entries must be of type float", def->name, f->name);
	return false;
}

/* The n values of a flat array field, in order. */
static bool px_flat(const px_struct *def, const px_field *f, zval *v, uint32_t n, zval **vals)
{
	if (Z_TYPE_P(v) != IS_ARRAY || zend_hash_num_elements(Z_ARRVAL_P(v)) != n) {
		zend_value_error("%s::$%s must be an array of exactly %u entries", def->name, f->name, n);
		return false;
	}
	uint32_t i = 0;
	zval *e;
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(v), e) {
		vals[i++] = e;
	} ZEND_HASH_FOREACH_END();
	return true;
}

static bool px_field_read(const px_struct *def, const px_field *f, zval *v, char *base)
{
	char *p = base + f->offset;
	zend_long l;

	if (Z_TYPE_P(v) == IS_UNDEF) {
		zend_value_error("%s::$%s must be initialised", def->name, f->name);
		return false;
	}
	switch (f->kind) {
		case PX_I16:
			if (!px_long_in(def, f, v, INT16_MIN, INT16_MAX, &l)) return false;
			*(int16_t *) p = (int16_t) l;
			return true;
		case PX_U16:
			if (!px_long_in(def, f, v, 0, UINT16_MAX, &l)) return false;
			*(uint16_t *) p = (uint16_t) l;
			return true;
		case PX_I32:
			if (!px_long_in(def, f, v, INT32_MIN, INT32_MAX, &l)) return false;
			*(int32_t *) p = (int32_t) l;
			return true;
		case PX_U32:
			if (!px_long_in(def, f, v, 0, UINT32_MAX, &l)) return false;
			*(uint32_t *) p = (uint32_t) l;
			return true;
		case PX_PTR:
			if (Z_TYPE_P(v) != IS_LONG) {
				zend_value_error("%s::$%s must be of type int", def->name, f->name);
				return false;
			}
			*(const void **) p = (const void *) (uintptr_t) Z_LVAL_P(v);
			return true;
		case PX_F64:
			return px_double_of(def, f, v, (double *) p);
		case PX_BOOL:
			*(pixman_bool_t *) p = zend_is_true(v) ? 1 : 0;
			return true;
		case PX_STRUCT:
			if (Z_TYPE_P(v) != IS_OBJECT || Z_OBJCE_P(v) != *f->sub->ce) {
				zend_value_error("%s::$%s must be a %s", def->name, f->name, f->sub->name);
				return false;
			}
			return px_struct_read(f->sub, Z_OBJ_P(v), p);
		case PX_I32_ARR:
		case PX_U32_ARR: {
			zval *vals[PIXMAN_MAX_INDEXED];
			if (!px_flat(def, f, v, f->n, vals)) return false;
			for (uint32_t i = 0; i < f->n; i++) {
				zval *e = vals[i];
				ZVAL_DEREF(e);
				bool u = f->kind == PX_U32_ARR;
				if (Z_TYPE_P(e) != IS_LONG || Z_LVAL_P(e) < (u ? 0 : INT32_MIN) || Z_LVAL_P(e) > (u ? UINT32_MAX : INT32_MAX)) {
					zend_value_error("%s::$%s[%u] must be an int between %s", def->name, f->name, i, u ? "0 and 4294967295" : "-2147483648 and 2147483647");
					return false;
				}
				if (u) ((uint32_t *) p)[i] = (uint32_t) Z_LVAL_P(e);
				else ((int32_t *) p)[i] = (int32_t) Z_LVAL_P(e);
			}
			return true;
		}
		case PX_F64_ARR: {
			zval *vals[3];
			if (!px_flat(def, f, v, f->n, vals)) return false;
			for (uint32_t i = 0; i < f->n; i++) {
				if (!px_double_of(def, f, vals[i], &((double *) p)[i])) return false;
			}
			return true;
		}
		case PX_I32_MAT3:
		case PX_F64_MAT3: {
			zval *rows[3];
			if (!px_flat(def, f, v, 3, rows)) return false;
			for (uint32_t r = 0; r < 3; r++) {
				zval *row = rows[r], *cells[3];
				ZVAL_DEREF(row);
				if (!px_flat(def, f, row, 3, cells)) return false;
				for (uint32_t c = 0; c < 3; c++) {
					if (f->kind == PX_F64_MAT3) {
						if (!px_double_of(def, f, cells[c], &((double *) p)[r * 3 + c])) return false;
					} else {
						zval *e = cells[c];
						ZVAL_DEREF(e);
						if (Z_TYPE_P(e) != IS_LONG || Z_LVAL_P(e) < INT32_MIN || Z_LVAL_P(e) > INT32_MAX) {
							zend_value_error("%s::$%s[%u][%u] must be an int between -2147483648 and 2147483647", def->name, f->name, r, c);
							return false;
						}
						((int32_t *) p)[r * 3 + c] = (int32_t) Z_LVAL_P(e);
					}
				}
			}
			return true;
		}
		case PX_BYTES:
			if (Z_TYPE_P(v) != IS_STRING || Z_STRLEN_P(v) != f->n) {
				zend_value_error("%s::$%s must be a string of exactly %u bytes", def->name, f->name, f->n);
				return false;
			}
			memcpy(p, Z_STRVAL_P(v), f->n);
			return true;
	}
	return false;
}

bool px_struct_read(const px_struct *def, zend_object *obj, void *out)
{
	memset(out, 0, def->size);
	for (uint32_t i = 0; i < def->count; i++) {
		if (!px_field_read(def, &def->fields[i], px_prop(def, obj, i), (char *) out)) {
			return false;
		}
	}
	return true;
}

static void px_zero_value(const px_field *f, zval *out)
{
	switch (f->kind) {
		case PX_I32_ARR:
		case PX_U32_ARR:
			array_init_size(out, f->n);
			for (uint32_t i = 0; i < f->n; i++) add_next_index_long(out, 0);
			return;
		case PX_F64_ARR:
			array_init_size(out, f->n);
			for (uint32_t i = 0; i < f->n; i++) add_next_index_double(out, 0.0);
			return;
		case PX_I32_MAT3:
		case PX_F64_MAT3:
			array_init_size(out, 3);
			for (uint32_t r = 0; r < 3; r++) {
				zval row;
				array_init_size(&row, 3);
				for (uint32_t c = 0; c < 3; c++) {
					if (f->kind == PX_F64_MAT3) add_next_index_double(&row, 0.0);
					else add_next_index_long(&row, 0);
				}
				add_next_index_zval(out, &row);
			}
			return;
		case PX_BYTES:
			ZVAL_STR(out, zend_string_safe_alloc(1, f->n, 0, 0));
			memset(Z_STRVAL_P(out), 0, f->n);
			Z_STRVAL_P(out)[f->n] = '\0';
			return;
		case PX_STRUCT: {
			char zero[64] = {0}; /* every nested struct (point, line, colour, span) is smaller */
			px_struct_new(f->sub, zero, out);
			return;
		}
		default:
			ZVAL_LONG(out, 0);
	}
}

static void px_field_value(const px_field *f, const char *base, zval *out)
{
	const char *p = base + f->offset;
	switch (f->kind) {
		case PX_I16: ZVAL_LONG(out, *(const int16_t *) p); return;
		case PX_U16: ZVAL_LONG(out, *(const uint16_t *) p); return;
		case PX_I32: ZVAL_LONG(out, *(const int32_t *) p); return;
		case PX_U32: ZVAL_LONG(out, *(const uint32_t *) p); return;
		case PX_PTR: ZVAL_LONG(out, (zend_long) (uintptr_t) *(const void * const *) p); return;
		case PX_F64: ZVAL_DOUBLE(out, *(const double *) p); return;
		case PX_BOOL: ZVAL_BOOL(out, *(const pixman_bool_t *) p != 0); return;
		case PX_STRUCT: px_struct_new(f->sub, p, out); return;
		case PX_I32_ARR:
		case PX_U32_ARR:
			array_init_size(out, f->n);
			for (uint32_t i = 0; i < f->n; i++) {
				add_next_index_long(out, f->kind == PX_U32_ARR ? (zend_long) ((const uint32_t *) p)[i] : (zend_long) ((const int32_t *) p)[i]);
			}
			return;
		case PX_F64_ARR:
			array_init_size(out, f->n);
			for (uint32_t i = 0; i < f->n; i++) add_next_index_double(out, ((const double *) p)[i]);
			return;
		case PX_I32_MAT3:
		case PX_F64_MAT3:
			array_init_size(out, 3);
			for (uint32_t r = 0; r < 3; r++) {
				zval row;
				array_init_size(&row, 3);
				for (uint32_t c = 0; c < 3; c++) {
					if (f->kind == PX_F64_MAT3) add_next_index_double(&row, ((const double *) p)[r * 3 + c]);
					else add_next_index_long(&row, ((const int32_t *) p)[r * 3 + c]);
				}
				add_next_index_zval(out, &row);
			}
			return;
		case PX_BYTES:
			ZVAL_STRINGL(out, p, f->n);
			return;
	}
}

static void px_assign(const px_struct *def, zend_object *obj, uint32_t i, zval *value)
{
	const char *name = def->fields[i].name;
	zend_update_property(*def->ce, obj, name, strlen(name), value);
	zval_ptr_dtor(value);
}

void px_struct_write(const px_struct *def, zend_object *obj, const void *in)
{
	for (uint32_t i = 0; i < def->count; i++) {
		const px_field *f = &def->fields[i];
		if (f->kind == PX_STRUCT) {
			zval *cur = px_prop(def, obj, i);
			if (Z_TYPE_P(cur) == IS_OBJECT && Z_OBJCE_P(cur) == *f->sub->ce) {
				px_struct_write(f->sub, Z_OBJ_P(cur), (const char *) in + f->offset);
				continue;
			}
		}
		zval v;
		px_field_value(f, (const char *) in, &v);
		px_assign(def, obj, i, &v);
	}
}

void px_struct_new(const px_struct *def, const void *in, zval *out)
{
	object_init_ex(out, *def->ce);
	for (uint32_t i = 0; i < def->count; i++) {
		zval v;
		px_field_value(&def->fields[i], (const char *) in, &v);
		px_assign(def, Z_OBJ_P(out), i, &v);
	}
}

void px_struct_construct(const px_struct *def, INTERNAL_FUNCTION_PARAMETERS)
{
	zval *args = NULL;
	uint32_t argc = 0;

	ZEND_PARSE_PARAMETERS_START(0, def->count)
		Z_PARAM_VARIADIC('*', args, argc)
	ZEND_PARSE_PARAMETERS_END();

	zend_object *obj = Z_OBJ_P(ZEND_THIS);
	for (uint32_t i = 0; i < def->count; i++) {
		const px_field *f = &def->fields[i];
		zval v;
		if (i < argc && Z_TYPE(args[i]) != IS_UNDEF && Z_TYPE(args[i]) != IS_NULL) {
			ZVAL_COPY(&v, &args[i]);
		} else if (f->kind == PX_STRUCT || f->kind == PX_I32_ARR || f->kind == PX_U32_ARR || f->kind == PX_F64_ARR
				|| f->kind == PX_I32_MAT3 || f->kind == PX_F64_MAT3 || f->kind == PX_BYTES) {
			px_zero_value(f, &v);
		} else {
			continue; /* scalar: the property default */
		}
		px_assign(def, obj, i, &v);
		if (EG(exception)) {
			return;
		}
	}
	/* A value of the right PHP type can still be out of the C field's range or the wrong length. */
	char scratch[sizeof(pixman_indexed_t)];
	px_struct_read(def, obj, scratch);
}

bool px_check_count(zend_long count, HashTable *arr, uint32_t arg_num)
{
	if (count < 0 || (arr ? count > (zend_long) zend_hash_num_elements(arr) : count > 0)) {
		zend_argument_value_error(arg_num, "must be between 0 and the number of entries given (%u), " ZEND_LONG_FMT " given",
			arr ? zend_hash_num_elements(arr) : 0, count);
		return false;
	}
	return true;
}

bool px_struct_array_read(const px_struct *def, HashTable *arr, zend_long count, void *out, uint32_t arg_num)
{
	zend_long i = 0;
	zval *e;
	ZEND_HASH_FOREACH_VAL(arr, e) {
		if (i >= count) {
			break;
		}
		ZVAL_DEREF(e);
		if (Z_TYPE_P(e) != IS_OBJECT || Z_OBJCE_P(e) != *def->ce) {
			zend_argument_type_error(arg_num, "must contain only %s, %s found", def->name, zend_zval_value_name(e));
			return false;
		}
		if (!px_struct_read(def, Z_OBJ_P(e), (char *) out + i * def->size)) {
			return false;
		}
		i++;
	} ZEND_HASH_FOREACH_END();
	return true;
}

bool px_check_range(zend_long v, zend_long min, zend_long max, uint32_t arg_num)
{
	if (v < min || v > max) {
		zend_argument_value_error(arg_num, "must be between " ZEND_LONG_FMT " and " ZEND_LONG_FMT ", " ZEND_LONG_FMT " given", min, max, v);
		return false;
	}
	return true;
}

/* Value-struct constructors: each one its own method, sharing px_struct_construct. */
ZEND_METHOD(pixman_color, __construct) { px_struct_construct(&px_color, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_point_fixed, __construct) { px_struct_construct(&px_point_fixed, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_line_fixed, __construct) { px_struct_construct(&px_line_fixed, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_vector, __construct) { px_struct_construct(&px_vector, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_transform, __construct) { px_struct_construct(&px_transform, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_f_vector, __construct) { px_struct_construct(&px_f_vector, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_f_transform, __construct) { px_struct_construct(&px_f_transform, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_box16, __construct) { px_struct_construct(&px_box16, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_box32, __construct) { px_struct_construct(&px_box32, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_box64f, __construct) { px_struct_construct(&px_box64f, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_rectangle16, __construct) { px_struct_construct(&px_rectangle16, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_gradient_stop, __construct) { px_struct_construct(&px_gradient_stop, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_indexed, __construct) { px_struct_construct(&px_indexed, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_glyph, __construct) { px_struct_construct(&px_glyph, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_edge, __construct) { px_struct_construct(&px_edge, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_trapezoid, __construct) { px_struct_construct(&px_trapezoid, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_triangle, __construct) { px_struct_construct(&px_triangle, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_span_fix, __construct) { px_struct_construct(&px_span_fix, INTERNAL_FUNCTION_PARAM_PASSTHRU); }
ZEND_METHOD(pixman_trap, __construct) { px_struct_construct(&px_trap, INTERNAL_FUNCTION_PARAM_PASSTHRU); }

/* ---- images ----------------------------------------------------------- */

static zend_object_handlers px_image_handlers;

/* Images with accessors set, by record. The trampolines find the record whose bits hold an address. */
ZEND_TLS HashTable *px_accessor_images;

static zend_object *px_image_create(zend_class_entry *ce)
{
	px_image_obj *o = zend_object_alloc(sizeof(px_image_obj), ce);
	o->image = NULL;
	zend_object_std_init(&o->std, ce);
	object_properties_init(&o->std, ce);
	o->std.handlers = &px_image_handlers;
	return &o->std;
}

static void px_image_free(zend_object *obj)
{
	px_image_obj *o = px_image_from(obj);
	if (o->image) {
		pixman_image_t *image = o->image;
		o->image = NULL;
		pixman_image_unref(image);
	}
	zend_object_std_dtor(obj);
}

static zend_function *px_no_constructor(zend_object *obj)
{
	zend_throw_error(NULL, "Cannot directly construct %s, use the pixman function that creates one", ZSTR_VAL(obj->ce->name));
	return NULL;
}

void px_image_wrap(pixman_image_t *image, zval *out)
{
	if (!image) {
		ZVAL_NULL(out);
		return;
	}
	object_init_ex(out, px_image_ce);
	px_image_from(Z_OBJ_P(out))->image = image;
}

pixman_image_t *px_image_arg(zval *zv, uint32_t arg_num)
{
	if (!zv || Z_TYPE_P(zv) != IS_OBJECT) {
		return NULL;
	}
	px_image_obj *o = px_image_from(Z_OBJ_P(zv));
	if (!o->image) {
		zend_argument_value_error(arg_num, "is a released pixman_image");
	}
	return o->image;
}

px_image_rec *px_image_rec_of(pixman_image_t *image)
{
	return (px_image_rec *) pixman_image_get_destroy_data(image);
}

static void px_accessor_forget(px_image_rec *rec)
{
	if (px_accessor_images) {
		zend_hash_index_del(px_accessor_images, (zend_ulong) (uintptr_t) rec);
	}
}

static void px_image_destroyed(pixman_image_t *image, void *data)
{
	px_image_rec *rec = data;
	(void) image;

	if (Z_TYPE(rec->destroy_fn) != IS_UNDEF && EG(active) && !(EG(flags) & EG_FLAGS_OBJECT_STORE_NO_REUSE)) {
		zval args[2], retval;
		object_init_ex(&args[0], px_image_ce); /* released: image is NULL */
		ZVAL_COPY_VALUE(&args[1], &rec->destroy_data);
		call_user_function(NULL, NULL, &rec->destroy_fn, &retval, 2, args);
		zval_ptr_dtor(&retval);
		zval_ptr_dtor(&args[0]);
	}
	px_accessor_forget(rec);
	zval_ptr_dtor(&rec->destroy_fn);
	zval_ptr_dtor(&rec->destroy_data);
	zval_ptr_dtor(&rec->read_fn);
	zval_ptr_dtor(&rec->write_fn);
	free(rec->bits);
	free(rec->indexed);
	free(rec);
}

pixman_image_t *px_image_adopt(pixman_image_t *image, void *bits)
{
	if (!image) {
		free(bits);
		return NULL;
	}
	px_image_rec *rec = calloc(1, sizeof(*rec));
	if (!rec) {
		pixman_image_unref(image);
		free(bits);
		zend_throw_error(NULL, "Out of memory");
		return NULL;
	}
	ZVAL_UNDEF(&rec->destroy_fn);
	ZVAL_NULL(&rec->destroy_data);
	ZVAL_UNDEF(&rec->read_fn);
	ZVAL_UNDEF(&rec->write_fn);
	rec->bits = bits;
	rec->image = image;
	pixman_image_set_destroy_function(image, px_image_destroyed, rec);
	return image;
}

/* The record whose bits hold `address`, if it has accessors set. */
static px_image_rec *px_accessor_owner(const void *address)
{
	if (!px_accessor_images) {
		return NULL;
	}
	zval *zv;
	ZEND_HASH_FOREACH_VAL(px_accessor_images, zv) {
		px_image_rec *rec = Z_PTR_P(zv);
		const char *start = (const char *) pixman_image_get_data(rec->image);
		if (!start) {
			continue;
		}
		const char *end = start + (size_t) pixman_image_get_stride(rec->image) * (size_t) pixman_image_get_height(rec->image);
		if ((const char *) address >= start && (const char *) address < end) {
			return rec;
		}
	} ZEND_HASH_FOREACH_END();
	return NULL;
}

static uint32_t px_read_direct(const void *src, int size)
{
	switch (size) {
		case 1: return *(const uint8_t *) src;
		case 2: return *(const uint16_t *) src;
		default: return *(const uint32_t *) src;
	}
}

static void px_write_direct(void *dst, uint32_t value, int size)
{
	switch (size) {
		case 1: *(uint8_t *) dst = (uint8_t) value; return;
		case 2: *(uint16_t *) dst = (uint16_t) value; return;
		default: *(uint32_t *) dst = value; return;
	}
}

static uint32_t px_read_trampoline(const void *src, int size)
{
	px_image_rec *rec = px_accessor_owner(src);
	if (!rec || Z_TYPE(rec->read_fn) == IS_UNDEF) {
		return px_read_direct(src, size);
	}
	if (EG(exception)) {
		return 0;
	}
	zval args[2], retval;
	ZVAL_LONG(&args[0], (zend_long) (uintptr_t) src);
	ZVAL_LONG(&args[1], size);
	uint32_t value = 0;
	if (call_user_function(NULL, NULL, &rec->read_fn, &retval, 2, args) == SUCCESS && !EG(exception)) {
		value = (uint32_t) zval_get_long(&retval);
	}
	zval_ptr_dtor(&retval);
	return value;
}

static void px_write_trampoline(void *dst, uint32_t value, int size)
{
	px_image_rec *rec = px_accessor_owner(dst);
	if (!rec || Z_TYPE(rec->write_fn) == IS_UNDEF) {
		px_write_direct(dst, value, size);
		return;
	}
	if (EG(exception)) {
		return;
	}
	zval args[3], retval;
	ZVAL_LONG(&args[0], (zend_long) (uintptr_t) dst);
	ZVAL_LONG(&args[1], value);
	ZVAL_LONG(&args[2], size);
	call_user_function(NULL, NULL, &rec->write_fn, &retval, 3, args);
	zval_ptr_dtor(&retval);
}

void px_accessors_set(pixman_image_t *image, px_image_rec *rec)
{
	bool any = Z_TYPE(rec->read_fn) != IS_UNDEF || Z_TYPE(rec->write_fn) != IS_UNDEF;
	if (any) {
		if (!px_accessor_images) {
			ALLOC_HASHTABLE(px_accessor_images);
			zend_hash_init(px_accessor_images, 8, NULL, NULL, 0);
		}
		zval ptr;
		ZVAL_PTR(&ptr, rec);
		zend_hash_index_update(px_accessor_images, (zend_ulong) (uintptr_t) rec, &ptr);
		/* Both trampolines always: pixman calls whichever it needs, and a NULL one would crash it. */
		pixman_image_set_accessors(image, px_read_trampoline, px_write_trampoline);
	} else {
		px_accessor_forget(rec);
		pixman_image_set_accessors(image, NULL, NULL);
	}
}

/* ---- regions ---------------------------------------------------------- */

static zend_object_handlers px_region16_handlers, px_region32_handlers, px_region64f_handlers;

static zend_object *px_region16_create(zend_class_entry *ce)
{
	px_region16_obj *o = zend_object_alloc(sizeof(px_region16_obj), ce);
	o->initialised = false;
	zend_object_std_init(&o->std, ce);
	object_properties_init(&o->std, ce);
	o->std.handlers = &px_region16_handlers;
	return &o->std;
}

static zend_object *px_region32_create(zend_class_entry *ce)
{
	px_region32_obj *o = zend_object_alloc(sizeof(px_region32_obj), ce);
	o->initialised = false;
	zend_object_std_init(&o->std, ce);
	object_properties_init(&o->std, ce);
	o->std.handlers = &px_region32_handlers;
	return &o->std;
}

static zend_object *px_region64f_create(zend_class_entry *ce)
{
	px_region64f_obj *o = zend_object_alloc(sizeof(px_region64f_obj), ce);
	o->initialised = false;
	zend_object_std_init(&o->std, ce);
	object_properties_init(&o->std, ce);
	o->std.handlers = &px_region64f_handlers;
	return &o->std;
}

static void px_region16_free(zend_object *obj)
{
	px_region16_obj *o = px_region16_from(obj);
	if (o->initialised) {
		pixman_region_fini(&o->region);
		o->initialised = false;
	}
	zend_object_std_dtor(obj);
}

static void px_region32_free(zend_object *obj)
{
	px_region32_obj *o = px_region32_from(obj);
	if (o->initialised) {
		pixman_region32_fini(&o->region);
		o->initialised = false;
	}
	zend_object_std_dtor(obj);
}

static void px_region64f_free(zend_object *obj)
{
	px_region64f_obj *o = px_region64f_from(obj);
	if (o->initialised) {
		pixman_region64f_fini(&o->region);
		o->initialised = false;
	}
	zend_object_std_dtor(obj);
}

pixman_region16_t *px_region16_arg(zval *zv, uint32_t arg_num)
{
	if (!zv || Z_TYPE_P(zv) != IS_OBJECT) return NULL;
	px_region16_obj *o = px_region16_from(Z_OBJ_P(zv));
	if (!o->initialised) {
		zend_argument_value_error(arg_num, "is an uninitialised pixman_region16");
		return NULL;
	}
	return &o->region;
}

pixman_region32_t *px_region32_arg(zval *zv, uint32_t arg_num)
{
	if (!zv || Z_TYPE_P(zv) != IS_OBJECT) return NULL;
	px_region32_obj *o = px_region32_from(Z_OBJ_P(zv));
	if (!o->initialised) {
		zend_argument_value_error(arg_num, "is an uninitialised pixman_region32");
		return NULL;
	}
	return &o->region;
}

pixman_region64f_t *px_region64f_arg(zval *zv, uint32_t arg_num)
{
	if (!zv || Z_TYPE_P(zv) != IS_OBJECT) return NULL;
	px_region64f_obj *o = px_region64f_from(Z_OBJ_P(zv));
	if (!o->initialised) {
		zend_argument_value_error(arg_num, "is an uninitialised pixman_region64f");
		return NULL;
	}
	return &o->region;
}

pixman_region16_t *px_region16_for_init(zval *zv)
{
	px_region16_obj *o = px_region16_from(Z_OBJ_P(zv));
	if (o->initialised) pixman_region_fini(&o->region);
	o->initialised = true;
	return &o->region;
}

pixman_region32_t *px_region32_for_init(zval *zv)
{
	px_region32_obj *o = px_region32_from(Z_OBJ_P(zv));
	if (o->initialised) pixman_region32_fini(&o->region);
	o->initialised = true;
	return &o->region;
}

pixman_region64f_t *px_region64f_for_init(zval *zv)
{
	px_region64f_obj *o = px_region64f_from(Z_OBJ_P(zv));
	if (o->initialised) pixman_region64f_fini(&o->region);
	o->initialised = true;
	return &o->region;
}

/* ---- glyph caches ----------------------------------------------------- */

static zend_object_handlers px_glyph_cache_handlers;

static zend_object *px_glyph_cache_create_obj(zend_class_entry *ce)
{
	px_glyph_cache_obj *o = zend_object_alloc(sizeof(px_glyph_cache_obj), ce);
	o->cache = NULL;
	o->frozen = 0;
	zend_object_std_init(&o->std, ce);
	object_properties_init(&o->std, ce);
	o->std.handlers = &px_glyph_cache_handlers;
	zend_hash_init(&o->glyphs, 8, NULL, ZVAL_PTR_DTOR, 0);
	return &o->std;
}

static void px_glyph_cache_free(zend_object *obj)
{
	px_glyph_cache_obj *o = px_glyph_cache_from(obj);
	if (o->cache) {
		px_glyph_cache_release(o);
	}
	zend_hash_destroy(&o->glyphs);
	zend_object_std_dtor(obj);
}

void px_glyph_cache_release(px_glyph_cache_obj *o)
{
	while (o->frozen > 0) {
		pixman_glyph_cache_thaw(o->cache);
		o->frozen--;
	}
	pixman_glyph_cache_destroy(o->cache);
	o->cache = NULL;
	zend_hash_clean(&o->glyphs);
}

px_glyph_cache_obj *px_glyph_cache_arg(zval *zv, uint32_t arg_num)
{
	px_glyph_cache_obj *o = px_glyph_cache_from(Z_OBJ_P(zv));
	if (!o->cache) {
		zend_argument_value_error(arg_num, "is a destroyed pixman_glyph_cache");
		return NULL;
	}
	return o;
}

void px_glyph_record(px_glyph_cache_obj *cache, const void *glyph, zend_long font_key, zend_long glyph_key)
{
	zval keys;
	array_init_size(&keys, 2);
	add_next_index_long(&keys, font_key);
	add_next_index_long(&keys, glyph_key);
	zend_hash_index_update(&cache->glyphs, (zend_ulong) (uintptr_t) glyph, &keys);
}

void px_glyph_forget(px_glyph_cache_obj *cache, const void *glyph)
{
	zend_hash_index_del(&cache->glyphs, (zend_ulong) (uintptr_t) glyph);
}

bool px_glyphs_read(px_glyph_cache_obj *cache, HashTable *arr, zend_long count, pixman_glyph_t *out, uint32_t arg_num)
{
	if (!px_struct_array_read(&px_glyph, arr, count, out, arg_num)) {
		return false;
	}
	for (zend_long i = 0; i < count; i++) {
		zval *keys = zend_hash_index_find(&cache->glyphs, (zend_ulong) (uintptr_t) out[i].glyph);
		const void *found = NULL;
		if (keys) {
			zend_long fk = Z_LVAL_P(zend_hash_index_find(Z_ARRVAL_P(keys), 0));
			zend_long gk = Z_LVAL_P(zend_hash_index_find(Z_ARRVAL_P(keys), 1));
			found = pixman_glyph_cache_lookup(cache->cache, (void *) (uintptr_t) fk, (void *) (uintptr_t) gk);
		}
		if (!found || found != out[i].glyph) {
			zend_argument_value_error(arg_num, "entry " ZEND_LONG_FMT " is not a glyph held by this cache (never returned, removed, or evicted by thaw)", i);
			return false;
		}
	}
	return true;
}

/* ---- module ----------------------------------------------------------- */

void px_runtime_minit(int module_number)
{
	register_pixman_constants_symbols(module_number);

	px_color_ce = register_class_pixman_color();
	px_point_fixed_ce = register_class_pixman_point_fixed();
	px_line_fixed_ce = register_class_pixman_line_fixed();
	px_vector_ce = register_class_pixman_vector();
	px_transform_ce = register_class_pixman_transform();
	px_f_vector_ce = register_class_pixman_f_vector();
	px_f_transform_ce = register_class_pixman_f_transform();
	px_box16_ce = register_class_pixman_box16();
	px_box32_ce = register_class_pixman_box32();
	px_box64f_ce = register_class_pixman_box64f();
	px_rectangle16_ce = register_class_pixman_rectangle16();
	px_gradient_stop_ce = register_class_pixman_gradient_stop();
	px_indexed_ce = register_class_pixman_indexed();
	px_glyph_ce = register_class_pixman_glyph();
	px_edge_ce = register_class_pixman_edge();
	px_trapezoid_ce = register_class_pixman_trapezoid();
	px_triangle_ce = register_class_pixman_triangle();
	px_span_fix_ce = register_class_pixman_span_fix();
	px_trap_ce = register_class_pixman_trap();

	px_image_ce = register_class_pixman_image();
	px_image_ce->create_object = px_image_create;
	memcpy(&px_image_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	px_image_handlers.offset = XtOffsetOf(px_image_obj, std);
	px_image_handlers.free_obj = px_image_free;
	px_image_handlers.clone_obj = NULL;
	px_image_handlers.get_constructor = px_no_constructor;

	px_region16_ce = register_class_pixman_region16();
	px_region16_ce->create_object = px_region16_create;
	memcpy(&px_region16_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	px_region16_handlers.offset = XtOffsetOf(px_region16_obj, std);
	px_region16_handlers.free_obj = px_region16_free;
	px_region16_handlers.clone_obj = NULL;

	px_region32_ce = register_class_pixman_region32();
	px_region32_ce->create_object = px_region32_create;
	memcpy(&px_region32_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	px_region32_handlers.offset = XtOffsetOf(px_region32_obj, std);
	px_region32_handlers.free_obj = px_region32_free;
	px_region32_handlers.clone_obj = NULL;

	px_region64f_ce = register_class_pixman_region64f();
	px_region64f_ce->create_object = px_region64f_create;
	memcpy(&px_region64f_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	px_region64f_handlers.offset = XtOffsetOf(px_region64f_obj, std);
	px_region64f_handlers.free_obj = px_region64f_free;
	px_region64f_handlers.clone_obj = NULL;

	px_glyph_cache_ce = register_class_pixman_glyph_cache();
	px_glyph_cache_ce->create_object = px_glyph_cache_create_obj;
	memcpy(&px_glyph_cache_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	px_glyph_cache_handlers.offset = XtOffsetOf(px_glyph_cache_obj, std);
	px_glyph_cache_handlers.free_obj = px_glyph_cache_free;
	px_glyph_cache_handlers.clone_obj = NULL;
	px_glyph_cache_handlers.get_constructor = px_no_constructor;
}

void px_runtime_rshutdown(void)
{
	if (px_accessor_images) {
		zend_hash_destroy(px_accessor_images);
		FREE_HASHTABLE(px_accessor_images);
		px_accessor_images = NULL;
	}
}
