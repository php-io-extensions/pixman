/*
 * Images (pixman-image.c, pixman-bits-image.c, the gradients, pixman.c):
 * creation, references, properties, compositing, fills, and the raw
 * pixman_fill / pixman_blt on PHP strings.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/pixman_image_arginfo.h"

/* ---- argument checks pixman does not make ----------------------------- */

static bool i16(zend_long v, uint32_t arg) { return px_check_range(v, INT16_MIN, INT16_MAX, arg); }
static bool u16(zend_long v, uint32_t arg) { return px_check_range(v, 0, UINT16_MAX, arg); }
static bool i32(zend_long v, uint32_t arg) { return px_check_range(v, INT32_MIN, INT32_MAX, arg); }

/* pixman_op_t has gaps; a value in a gap reaches a NULL combiner. */
static bool op_ok(zend_long op, uint32_t arg)
{
	if ((op >= PIXMAN_OP_CLEAR && op <= PIXMAN_OP_SATURATE)
			|| (op >= PIXMAN_OP_DISJOINT_CLEAR && op <= PIXMAN_OP_DISJOINT_XOR)
			|| (op >= PIXMAN_OP_CONJOINT_CLEAR && op <= PIXMAN_OP_CONJOINT_XOR)
			|| (op >= PIXMAN_OP_MULTIPLY && op <= PIXMAN_OP_HSL_LUMINOSITY)) {
		return true;
	}
	zend_argument_value_error(arg, "must be a PIXMAN_OP_* constant, " ZEND_LONG_FMT " given", op);
	return false;
}

/* A format pixman knows: an unknown code has no fetcher and crashes on first use. */
static bool format_ok(zend_long format, uint32_t arg)
{
	if (format >= 0 && format <= UINT32_MAX
			&& (pixman_format_supported_source((pixman_format_code_t) format) || pixman_format_supported_destination((pixman_format_code_t) format))) {
		return true;
	}
	zend_argument_value_error(arg, "must be a supported PIXMAN_* format code, " ZEND_LONG_FMT " given", format);
	return false;
}

static pixman_image_t *img(zval *zv, uint32_t arg)
{
	return px_image_arg(zv, arg);
}

/* ---- creation --------------------------------------------------------- */

static pixman_gradient_stop_t *stops_read(HashTable *stops, zend_long n, uint32_t arg_stops, uint32_t arg_n)
{
	if (!px_check_count(n, stops, arg_n)) return NULL;
	pixman_gradient_stop_t *s = safe_emalloc(n ? n : 1, sizeof(*s), 0);
	if (!px_struct_array_read(&px_gradient_stop, stops, n, s, arg_stops)) {
		efree(s);
		return NULL;
	}
	return s;
}

ZEND_FUNCTION(pixman_image_create_solid_fill)
{
	zval *c;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(c, *px_color.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_color_t color;
	if (!px_struct_read(&px_color, Z_OBJ_P(c), &color)) RETURN_THROWS();
	px_image_wrap(px_image_adopt(pixman_image_create_solid_fill(&color), NULL), return_value);
}

ZEND_FUNCTION(pixman_image_create_linear_gradient)
{
	zval *a, *b;
	HashTable *stops;
	zend_long n;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(a, *px_point_fixed.ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_point_fixed.ce)
		Z_PARAM_ARRAY_HT(stops)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	pixman_point_fixed_t p1, p2;
	if (!px_struct_read(&px_point_fixed, Z_OBJ_P(a), &p1) || !px_struct_read(&px_point_fixed, Z_OBJ_P(b), &p2)) RETURN_THROWS();
	pixman_gradient_stop_t *s = stops_read(stops, n, 3, 4);
	if (!s) RETURN_THROWS();
	pixman_image_t *image = pixman_image_create_linear_gradient(&p1, &p2, s, (int) n);
	efree(s);
	px_image_wrap(px_image_adopt(image, NULL), return_value);
}

ZEND_FUNCTION(pixman_image_create_radial_gradient)
{
	zval *a, *b;
	zend_long ir, or_;
	HashTable *stops;
	zend_long n;
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(a, *px_point_fixed.ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_point_fixed.ce)
		Z_PARAM_LONG(ir)
		Z_PARAM_LONG(or_)
		Z_PARAM_ARRAY_HT(stops)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	pixman_point_fixed_t inner, outer;
	if (!px_struct_read(&px_point_fixed, Z_OBJ_P(a), &inner) || !px_struct_read(&px_point_fixed, Z_OBJ_P(b), &outer)
			|| !i32(ir, 3) || !i32(or_, 4)) RETURN_THROWS();
	pixman_gradient_stop_t *s = stops_read(stops, n, 5, 6);
	if (!s) RETURN_THROWS();
	pixman_image_t *image = pixman_image_create_radial_gradient(&inner, &outer, (pixman_fixed_t) ir, (pixman_fixed_t) or_, s, (int) n);
	efree(s);
	px_image_wrap(px_image_adopt(image, NULL), return_value);
}

ZEND_FUNCTION(pixman_image_create_conical_gradient)
{
	zval *c;
	zend_long angle;
	HashTable *stops;
	zend_long n;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(c, *px_point_fixed.ce)
		Z_PARAM_LONG(angle)
		Z_PARAM_ARRAY_HT(stops)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	pixman_point_fixed_t center;
	if (!px_struct_read(&px_point_fixed, Z_OBJ_P(c), &center) || !i32(angle, 2)) RETURN_THROWS();
	pixman_gradient_stop_t *s = stops_read(stops, n, 3, 4);
	if (!s) RETURN_THROWS();
	pixman_image_t *image = pixman_image_create_conical_gradient(&center, (pixman_fixed_t) angle, s, (int) n);
	efree(s);
	px_image_wrap(px_image_adopt(image, NULL), return_value);
}

/*
 * The bytes pixman reads from caller bits: stride x height, and for YV12 the two
 * chroma planes after them (each (stride / 2) x ((height + 1) / 2)).
 */
static bool bits_size(zend_long format, zend_long w, zend_long h, zend_long stride, size_t *need)
{
	uint64_t bpp = PIXMAN_FORMAT_BPP((uint32_t) format);
	uint64_t row = ((uint64_t) w * bpp + 7) / 8;
	if (stride <= 0 || stride % 4 != 0 || (uint64_t) stride < row) {
		zend_argument_value_error(5, "must be a positive multiple of 4 of at least %" PRIu64 " bytes for this width and format", row);
		return false;
	}
	uint64_t total = (uint64_t) stride * (uint64_t) h;
	if (format == PIXMAN_yv12) {
		total += 2 * ((uint64_t) (stride / 2) * (uint64_t) ((h + 1) / 2));
	}
	if (total > SIZE_MAX / 2) {
		zend_argument_value_error(3, "is too large");
		return false;
	}
	*need = (size_t) total;
	return true;
}

static void create_bits(INTERNAL_FUNCTION_PARAMETERS, bool clear)
{
	zend_long format, w, h, stride;
	zend_string *bits;
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(format)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_STR_OR_NULL(bits)
		Z_PARAM_LONG(stride)
	ZEND_PARSE_PARAMETERS_END();
	if (!format_ok(format, 1) || !px_check_range(w, 0, INT32_MAX, 2) || !px_check_range(h, 0, INT32_MAX, 3)) RETURN_THROWS();
	void *copy = NULL;
	if (bits) {
		size_t need;
		if (!bits_size(format, w, h, stride, &need)) RETURN_THROWS();
		if (ZSTR_LEN(bits) < need) {
			zend_argument_value_error(4, "must be at least %zu bytes (stride x height), %zu given", need, ZSTR_LEN(bits));
			RETURN_THROWS();
		}
		copy = malloc(need ? need : 4);
		if (!copy) {
			zend_throw_error(NULL, "Out of memory");
			RETURN_THROWS();
		}
		memcpy(copy, ZSTR_VAL(bits), need);
	} else if (!i32(stride, 5)) {
		RETURN_THROWS();
	}
	pixman_image_t *image = clear
		? pixman_image_create_bits((pixman_format_code_t) format, (int) w, (int) h, copy, (int) stride)
		: pixman_image_create_bits_no_clear((pixman_format_code_t) format, (int) w, (int) h, copy, (int) stride);
	px_image_wrap(px_image_adopt(image, copy), return_value);
}

ZEND_FUNCTION(pixman_image_create_bits)
{
	create_bits(INTERNAL_FUNCTION_PARAM_PASSTHRU, true);
}

ZEND_FUNCTION(pixman_image_create_bits_no_clear)
{
	create_bits(INTERNAL_FUNCTION_PARAM_PASSTHRU, false);
}

/* ---- references ------------------------------------------------------- */

ZEND_FUNCTION(pixman_image_ref)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	px_image_wrap(pixman_image_ref(image), return_value);
}

ZEND_FUNCTION(pixman_image_unref)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	px_image_from(Z_OBJ_P(i))->image = NULL;
	RETURN_BOOL(pixman_image_unref(image));
}

ZEND_FUNCTION(pixman_image_set_destroy_function)
{
	zval *i, *data;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_FUNC_OR_NULL(fci, fcc)
		Z_PARAM_ZVAL(data)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	px_image_rec *rec = px_image_rec_of(image);
	zval_ptr_dtor(&rec->destroy_fn);
	zval_ptr_dtor(&rec->destroy_data);
	if (ZEND_FCI_INITIALIZED(fci)) {
		ZVAL_COPY(&rec->destroy_fn, &fci.function_name);
	} else {
		ZVAL_UNDEF(&rec->destroy_fn);
	}
	ZVAL_COPY(&rec->destroy_data, data);
}

ZEND_FUNCTION(pixman_image_get_destroy_data)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	RETURN_COPY(&px_image_rec_of(image)->destroy_data);
}

/* ---- properties ------------------------------------------------------- */

ZEND_FUNCTION(pixman_image_set_clip_region)
{
	zval *i, *r;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(r, px_region16_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	pixman_region16_t *region = px_region16_arg(r, 2);
	if (EG(exception)) RETURN_THROWS();
	RETURN_BOOL(pixman_image_set_clip_region(image, region));
}

ZEND_FUNCTION(pixman_image_set_clip_region32)
{
	zval *i, *r;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(r, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	pixman_region32_t *region = px_region32_arg(r, 2);
	if (EG(exception)) RETURN_THROWS();
	RETURN_BOOL(pixman_image_set_clip_region32(image, region));
}

ZEND_FUNCTION(pixman_image_set_clip_region64f)
{
	zval *i, *r;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(r, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	pixman_region64f_t *region = px_region64f_arg(r, 2);
	if (EG(exception)) RETURN_THROWS();
	RETURN_BOOL(pixman_image_set_clip_region64f(image, region));
}

ZEND_FUNCTION(pixman_image_set_has_client_clip)
{
	zval *i;
	bool v;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_BOOL(v)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	pixman_image_set_has_client_clip(image, v);
}

ZEND_FUNCTION(pixman_image_set_transform)
{
	zval *i, *t;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(t, *px_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	pixman_transform_t m;
	if (t && !px_struct_read(&px_transform, Z_OBJ_P(t), &m)) RETURN_THROWS();
	RETURN_BOOL(pixman_image_set_transform(image, t ? &m : NULL));
}

ZEND_FUNCTION(pixman_image_set_repeat)
{
	zval *i;
	zend_long v;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_LONG(v)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image || !px_check_range(v, PIXMAN_REPEAT_NONE, PIXMAN_REPEAT_REFLECT, 2)) RETURN_THROWS();
	pixman_image_set_repeat(image, (pixman_repeat_t) v);
}

ZEND_FUNCTION(pixman_image_set_dither)
{
	zval *i;
	zend_long v;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_LONG(v)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image || !px_check_range(v, PIXMAN_DITHER_NONE, PIXMAN_DITHER_ORDERED_BLUE_NOISE_64, 2)) RETURN_THROWS();
	pixman_image_set_dither(image, (pixman_dither_t) v);
}

ZEND_FUNCTION(pixman_image_set_dither_offset)
{
	zval *i;
	zend_long x, y;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image || !i32(x, 2) || !i32(y, 3)) RETURN_THROWS();
	pixman_image_set_dither_offset(image, (int) x, (int) y);
}

/*
 * pixman_image_set_filter copies the parameters and checks the count only for
 * SEPARABLE_CONVOLUTION, after reading the first four. CONVOLUTION's width x
 * height kernel is read at composite time with no check. Both are checked here.
 */
static bool filter_params_ok(zend_long filter, const pixman_fixed_t *p, zend_long n)
{
	if (filter == PIXMAN_FILTER_CONVOLUTION) {
		if (n < 2) {
			zend_argument_value_error(4, "must be at least 2 for PIXMAN_FILTER_CONVOLUTION (width, height, then the kernel)");
			return false;
		}
		zend_long w = pixman_fixed_to_int(p[0]), h = pixman_fixed_to_int(p[1]);
		if (w < 0 || h < 0 || n != 2 + w * h) {
			zend_argument_value_error(4, "must be 2 + width x height for PIXMAN_FILTER_CONVOLUTION");
			return false;
		}
	} else if (filter == PIXMAN_FILTER_SEPARABLE_CONVOLUTION) {
		if (n < 4) {
			zend_argument_value_error(4, "must be at least 4 for PIXMAN_FILTER_SEPARABLE_CONVOLUTION");
			return false;
		}
		zend_long w = pixman_fixed_to_int(p[0]), h = pixman_fixed_to_int(p[1]);
		zend_long xb = pixman_fixed_to_int(p[2]), yb = pixman_fixed_to_int(p[3]);
		if (w < 0 || h < 0 || xb < 0 || xb > 16 || yb < 0 || yb > 16
				|| n != 4 + ((zend_long) 1 << xb) * w + ((zend_long) 1 << yb) * h) {
			zend_argument_value_error(4, "must be 4 + (1 << x_phase_bits) x width + (1 << y_phase_bits) x height, with phase bits 0 to 16");
			return false;
		}
	}
	return true;
}

ZEND_FUNCTION(pixman_image_set_filter)
{
	zval *i;
	zend_long filter, n;
	HashTable *params;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_LONG(filter)
		Z_PARAM_ARRAY_HT_OR_NULL(params)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image || !px_check_range(filter, PIXMAN_FILTER_FAST, PIXMAN_FILTER_SEPARABLE_CONVOLUTION, 2) || !px_check_count(n, params, 4)) RETURN_THROWS();
	pixman_fixed_t *p = safe_emalloc(n ? n : 1, sizeof(*p), 0);
	zend_long k = 0;
	zval *e;
	if (params) {
		ZEND_HASH_FOREACH_VAL(params, e) {
			if (k >= n) break;
			ZVAL_DEREF(e);
			if (Z_TYPE_P(e) != IS_LONG || Z_LVAL_P(e) < INT32_MIN || Z_LVAL_P(e) > INT32_MAX) {
				efree(p);
				zend_argument_value_error(3, "must contain only 16.16 fixed-point ints");
				RETURN_THROWS();
			}
			p[k++] = (pixman_fixed_t) Z_LVAL_P(e);
		} ZEND_HASH_FOREACH_END();
	}
	if (!filter_params_ok(filter, p, n)) {
		efree(p);
		RETURN_THROWS();
	}
	pixman_bool_t ok = pixman_image_set_filter(image, (pixman_filter_t) filter, n ? p : NULL, (int) n);
	efree(p);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_image_set_source_clipping)
{
	zval *i;
	bool v;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_BOOL(v)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	pixman_image_set_source_clipping(image, v);
}

ZEND_FUNCTION(pixman_image_set_alpha_map)
{
	zval *i, *a;
	zend_long x, y;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(a, px_image_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	pixman_image_t *alpha = img(a, 2);
	if (EG(exception) || !i16(x, 3) || !i16(y, 4)) RETURN_THROWS();
	pixman_image_set_alpha_map(image, alpha, (int16_t) x, (int16_t) y);
}

ZEND_FUNCTION(pixman_image_set_component_alpha)
{
	zval *i;
	bool v;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_BOOL(v)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	pixman_image_set_component_alpha(image, v);
}

ZEND_FUNCTION(pixman_image_get_component_alpha)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	RETURN_BOOL(pixman_image_get_component_alpha(image));
}

ZEND_FUNCTION(pixman_image_set_accessors)
{
	zval *i;
	zend_fcall_info rf = empty_fcall_info, wf = empty_fcall_info;
	zend_fcall_info_cache rc = empty_fcall_info_cache, wc = empty_fcall_info_cache;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_FUNC_OR_NULL(rf, rc)
		Z_PARAM_FUNC_OR_NULL(wf, wc)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	px_image_rec *rec = px_image_rec_of(image);
	zval_ptr_dtor(&rec->read_fn);
	zval_ptr_dtor(&rec->write_fn);
	ZVAL_UNDEF(&rec->read_fn);
	ZVAL_UNDEF(&rec->write_fn);
	if (ZEND_FCI_INITIALIZED(rf)) ZVAL_COPY(&rec->read_fn, &rf.function_name);
	if (ZEND_FCI_INITIALIZED(wf)) ZVAL_COPY(&rec->write_fn, &wf.function_name);
	px_accessors_set(image, rec);
}

ZEND_FUNCTION(pixman_image_set_indexed)
{
	zval *i, *x;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(x, *px_indexed.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	pixman_indexed_t *copy = NULL;
	if (x) {
		copy = malloc(sizeof(*copy));
		if (!copy) {
			zend_throw_error(NULL, "Out of memory");
			RETURN_THROWS();
		}
		if (!px_struct_read(&px_indexed, Z_OBJ_P(x), copy)) {
			free(copy);
			RETURN_THROWS();
		}
	}
	/* pixman keeps the pointer: the image holds the copy until the next call or its destruction. */
	px_image_rec *rec = px_image_rec_of(image);
	pixman_image_set_indexed(image, copy);
	free(rec->indexed);
	rec->indexed = copy;
}

ZEND_FUNCTION(pixman_image_get_data)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	uint32_t *data = pixman_image_get_data(image);
	if (!data) RETURN_NULL();
	int stride = pixman_image_get_stride(image);
	int height = pixman_image_get_height(image);
	if (stride < 0) {
		/* Bottom-up bits start at the last row; the copy runs top row first in memory order. */
		RETURN_STRINGL((const char *) data + (size_t) stride * (size_t) (height - 1), (size_t) (-stride) * (size_t) height);
	}
	RETURN_STRINGL((const char *) data, (size_t) stride * (size_t) height);
}

ZEND_FUNCTION(pixman_image_get_data_address)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	RETURN_LONG((zend_long) (uintptr_t) pixman_image_get_data(image));
}

ZEND_FUNCTION(pixman_image_get_width)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	RETURN_LONG(pixman_image_get_width(image));
}

ZEND_FUNCTION(pixman_image_get_height)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	RETURN_LONG(pixman_image_get_height(image));
}

ZEND_FUNCTION(pixman_image_get_stride)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	RETURN_LONG(pixman_image_get_stride(image));
}

ZEND_FUNCTION(pixman_image_get_depth)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	RETURN_LONG(pixman_image_get_depth(image));
}

ZEND_FUNCTION(pixman_image_get_format)
{
	zval *i;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 1);
	if (!image) RETURN_THROWS();
	RETURN_LONG(pixman_image_get_format(image));
}

ZEND_FUNCTION(pixman_filter_create_separable_convolution)
{
	zval *nv;
	zend_long sx, sy, rx, ry, smx, smy, bx, by;
	ZEND_PARSE_PARAMETERS_START(9, 9)
		Z_PARAM_ZVAL(nv)
		Z_PARAM_LONG(sx)
		Z_PARAM_LONG(sy)
		Z_PARAM_LONG(rx)
		Z_PARAM_LONG(ry)
		Z_PARAM_LONG(smx)
		Z_PARAM_LONG(smy)
		Z_PARAM_LONG(bx)
		Z_PARAM_LONG(by)
	ZEND_PARSE_PARAMETERS_END();
	if (!i32(sx, 2) || !i32(sy, 3)
			|| !px_check_range(rx, PIXMAN_KERNEL_IMPULSE, PIXMAN_KERNEL_LANCZOS3_STRETCHED, 4)
			|| !px_check_range(ry, PIXMAN_KERNEL_IMPULSE, PIXMAN_KERNEL_LANCZOS3_STRETCHED, 5)
			|| !px_check_range(smx, PIXMAN_KERNEL_IMPULSE, PIXMAN_KERNEL_LANCZOS3_STRETCHED, 6)
			|| !px_check_range(smy, PIXMAN_KERNEL_IMPULSE, PIXMAN_KERNEL_LANCZOS3_STRETCHED, 7)
			|| !px_check_range(bx, 0, 16, 8) || !px_check_range(by, 0, 16, 9)) RETURN_THROWS();
	int n = 0;
	pixman_fixed_t *p = pixman_filter_create_separable_convolution(&n, (pixman_fixed_t) sx, (pixman_fixed_t) sy,
		(pixman_kernel_t) rx, (pixman_kernel_t) ry, (pixman_kernel_t) smx, (pixman_kernel_t) smy, (int) bx, (int) by);
	ZEND_TRY_ASSIGN_REF_LONG(nv, p ? n : 0);
	if (!p) RETURN_NULL();
	array_init_size(return_value, (uint32_t) n);
	for (int k = 0; k < n; k++) add_next_index_long(return_value, p[k]);
	free(p);
}

/* ---- fills and compositing ------------------------------------------- */

ZEND_FUNCTION(pixman_image_fill_rectangles)
{
	zend_long op, n;
	zval *i, *c;
	HashTable *rects;
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(op)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(c, *px_color.ce)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT(rects)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 2);
	pixman_color_t color;
	if (!image || !op_ok(op, 1) || !px_struct_read(&px_color, Z_OBJ_P(c), &color) || !px_check_count(n, rects, 4)) RETURN_THROWS();
	pixman_rectangle16_t *r = safe_emalloc(n ? n : 1, sizeof(*r), 0);
	if (!px_struct_array_read(&px_rectangle16, rects, n, r, 5)) {
		efree(r);
		RETURN_THROWS();
	}
	pixman_bool_t ok = pixman_image_fill_rectangles((pixman_op_t) op, image, &color, (int) n, r);
	efree(r);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_image_fill_boxes)
{
	zend_long op, n;
	zval *i, *c;
	HashTable *boxes;
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(op)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(c, *px_color.ce)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT(boxes)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = img(i, 2);
	pixman_color_t color;
	if (!image || !op_ok(op, 1) || !px_struct_read(&px_color, Z_OBJ_P(c), &color) || !px_check_count(n, boxes, 4)) RETURN_THROWS();
	pixman_box32_t *b = safe_emalloc(n ? n : 1, sizeof(*b), 0);
	if (!px_struct_array_read(&px_box32, boxes, n, b, 5)) {
		efree(b);
		RETURN_THROWS();
	}
	pixman_bool_t ok = pixman_image_fill_boxes((pixman_op_t) op, image, &color, (int) n, b);
	efree(b);
	RETURN_BOOL(ok);
}

/* The three images of a composite: src and dest live, mask null or live. */
static bool composite_images(zval *s, zval *m, zval *d, pixman_image_t **src, pixman_image_t **mask, pixman_image_t **dest)
{
	*src = img(s, 2);
	if (!*src) return false;
	*mask = img(m, 3);
	if (EG(exception)) return false;
	*dest = img(d, 4);
	return *dest != NULL;
}

ZEND_FUNCTION(pixman_image_composite)
{
	zend_long op, sx, sy, mx, my, dx, dy, w, h;
	zval *s, *m, *d;
	ZEND_PARSE_PARAMETERS_START(12, 12)
		Z_PARAM_LONG(op)
		Z_PARAM_OBJECT_OF_CLASS(s, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(m, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(d, px_image_ce)
		Z_PARAM_LONG(sx)
		Z_PARAM_LONG(sy)
		Z_PARAM_LONG(mx)
		Z_PARAM_LONG(my)
		Z_PARAM_LONG(dx)
		Z_PARAM_LONG(dy)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *src, *mask, *dest;
	if (!op_ok(op, 1) || !composite_images(s, m, d, &src, &mask, &dest)
			|| !i16(sx, 5) || !i16(sy, 6) || !i16(mx, 7) || !i16(my, 8) || !i16(dx, 9) || !i16(dy, 10)
			|| !u16(w, 11) || !u16(h, 12)) RETURN_THROWS();
	pixman_image_composite((pixman_op_t) op, src, mask, dest, (int16_t) sx, (int16_t) sy, (int16_t) mx, (int16_t) my,
		(int16_t) dx, (int16_t) dy, (uint16_t) w, (uint16_t) h);
}

ZEND_FUNCTION(pixman_image_composite32)
{
	zend_long op, sx, sy, mx, my, dx, dy, w, h;
	zval *s, *m, *d;
	ZEND_PARSE_PARAMETERS_START(12, 12)
		Z_PARAM_LONG(op)
		Z_PARAM_OBJECT_OF_CLASS(s, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(m, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(d, px_image_ce)
		Z_PARAM_LONG(sx)
		Z_PARAM_LONG(sy)
		Z_PARAM_LONG(mx)
		Z_PARAM_LONG(my)
		Z_PARAM_LONG(dx)
		Z_PARAM_LONG(dy)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *src, *mask, *dest;
	if (!op_ok(op, 1) || !composite_images(s, m, d, &src, &mask, &dest)
			|| !i32(sx, 5) || !i32(sy, 6) || !i32(mx, 7) || !i32(my, 8) || !i32(dx, 9) || !i32(dy, 10)
			|| !i32(w, 11) || !i32(h, 12)) RETURN_THROWS();
	pixman_image_composite32((pixman_op_t) op, src, mask, dest, (int32_t) sx, (int32_t) sy, (int32_t) mx, (int32_t) my,
		(int32_t) dx, (int32_t) dy, (int32_t) w, (int32_t) h);
}

ZEND_FUNCTION(pixman_image_composite64f)
{
	zend_long op;
	double sx, sy, mx, my, dx, dy, w, h;
	zval *s, *m, *d;
	ZEND_PARSE_PARAMETERS_START(12, 12)
		Z_PARAM_LONG(op)
		Z_PARAM_OBJECT_OF_CLASS(s, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(m, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(d, px_image_ce)
		Z_PARAM_DOUBLE(sx)
		Z_PARAM_DOUBLE(sy)
		Z_PARAM_DOUBLE(mx)
		Z_PARAM_DOUBLE(my)
		Z_PARAM_DOUBLE(dx)
		Z_PARAM_DOUBLE(dy)
		Z_PARAM_DOUBLE(w)
		Z_PARAM_DOUBLE(h)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *src, *mask, *dest;
	if (!op_ok(op, 1) || !composite_images(s, m, d, &src, &mask, &dest)) RETURN_THROWS();
	pixman_image_composite64f((pixman_op_t) op, src, mask, dest, sx, sy, mx, my, dx, dy, w, h);
}

ZEND_FUNCTION(pixman_disable_out_of_bounds_workaround)
{
	ZEND_PARSE_PARAMETERS_NONE();
	pixman_disable_out_of_bounds_workaround();
}

ZEND_FUNCTION(pixman_format_supported_destination)
{
	zend_long f;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(f)
	ZEND_PARSE_PARAMETERS_END();
	RETURN_BOOL(f >= 0 && f <= UINT32_MAX && pixman_format_supported_destination((pixman_format_code_t) f));
}

ZEND_FUNCTION(pixman_format_supported_source)
{
	zend_long f;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(f)
	ZEND_PARSE_PARAMETERS_END();
	RETURN_BOOL(f >= 0 && f <= UINT32_MAX && pixman_format_supported_source((pixman_format_code_t) f));
}

/*
 * pixman_fill and pixman_blt write raw memory with no bounds: every row the
 * call touches must lie inside the string. Strides are in uint32_t units, as
 * in C. The last byte a row touches is rounded up to a whole uint32_t, which
 * is what the 1 bpp path writes.
 */
static bool rect_inside(size_t len, zend_long stride, zend_long bpp, zend_long x, zend_long y, zend_long w, zend_long h,
	uint32_t arg_bits, uint32_t arg_stride)
{
	if (stride <= 0 || stride > INT32_MAX / 4) {
		zend_argument_value_error(arg_stride, "must be a positive stride in uint32_t units");
		return false;
	}
	if (x < 0 || y < 0 || w < 0 || h < 0 || x > INT32_MAX || y > INT32_MAX || w > INT32_MAX || h > INT32_MAX) {
		zend_argument_value_error(arg_bits, "rectangle must have non-negative position and size");
		return false;
	}
	if (w == 0 || h == 0) {
		return true;
	}
	uint64_t row_end = (((uint64_t) (x + w) * (uint64_t) bpp + 31) / 32) * 4;
	uint64_t row_bytes = (uint64_t) stride * 4;
	if (row_end > row_bytes || (uint64_t) (y + h - 1) * row_bytes + row_end > len) {
		zend_argument_value_error(arg_bits, "is too short for the rectangle at this stride and bpp");
		return false;
	}
	return true;
}

static bool bpp_ok(zend_long bpp, uint32_t arg)
{
	if (bpp == 1 || bpp == 8 || bpp == 16 || bpp == 24 || bpp == 32) return true;
	zend_argument_value_error(arg, "must be 1, 8, 16, 24 or 32");
	return false;
}

ZEND_FUNCTION(pixman_fill)
{
	zval *ref;
	zend_long stride, bpp, x, y, w, h, xor_;
	ZEND_PARSE_PARAMETERS_START(8, 8)
		Z_PARAM_ZVAL(ref)
		Z_PARAM_LONG(stride)
		Z_PARAM_LONG(bpp)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(xor_)
	ZEND_PARSE_PARAMETERS_END();
	zval *bits = Z_REFVAL_P(ref);
	if (Z_TYPE_P(bits) != IS_STRING) {
		zend_argument_type_error(1, "must be of type string, %s given", zend_zval_value_name(bits));
		RETURN_THROWS();
	}
	if (!bpp_ok(bpp, 3) || !px_check_range(xor_, 0, UINT32_MAX, 8)
			|| !rect_inside(Z_STRLEN_P(bits), stride, bpp, x, y, w, h, 1, 2)) RETURN_THROWS();
	SEPARATE_STRING(bits);
	zend_string_forget_hash_val(Z_STR_P(bits));
	RETURN_BOOL(pixman_fill((uint32_t *) Z_STRVAL_P(bits), (int) stride, (int) bpp, (int) x, (int) y, (int) w, (int) h, (uint32_t) xor_));
}

ZEND_FUNCTION(pixman_blt)
{
	zend_string *src;
	zval *ref;
	zend_long ss, ds, sb, db, sx, sy, dx, dy, w, h;
	ZEND_PARSE_PARAMETERS_START(12, 12)
		Z_PARAM_STR(src)
		Z_PARAM_ZVAL(ref)
		Z_PARAM_LONG(ss)
		Z_PARAM_LONG(ds)
		Z_PARAM_LONG(sb)
		Z_PARAM_LONG(db)
		Z_PARAM_LONG(sx)
		Z_PARAM_LONG(sy)
		Z_PARAM_LONG(dx)
		Z_PARAM_LONG(dy)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	zval *dst = Z_REFVAL_P(ref);
	if (Z_TYPE_P(dst) != IS_STRING) {
		zend_argument_type_error(2, "must be of type string, %s given", zend_zval_value_name(dst));
		RETURN_THROWS();
	}
	if (!bpp_ok(sb, 5) || !bpp_ok(db, 6)
			|| !rect_inside(ZSTR_LEN(src), ss, sb, sx, sy, w, h, 1, 3)
			|| !rect_inside(Z_STRLEN_P(dst), ds, db, dx, dy, w, h, 2, 4)) RETURN_THROWS();
	/* Hold the source: separating dst may drop the last other reference to a shared string. */
	zend_string_addref(src);
	SEPARATE_STRING(dst);
	zend_string_forget_hash_val(Z_STR_P(dst));
	pixman_bool_t ok = pixman_blt((uint32_t *) ZSTR_VAL(src), (uint32_t *) Z_STRVAL_P(dst), (int) ss, (int) ds, (int) sb, (int) db,
		(int) sx, (int) sy, (int) dx, (int) dy, (int) w, (int) h);
	zend_string_release(src);
	RETURN_BOOL(ok);
}

void px_image_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
