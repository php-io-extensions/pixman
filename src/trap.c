/*
 * Edges, traps, trapezoids and triangles (pixman-edge.c, pixman-trap.c).
 * Edges pixman steps are written back into the objects passed in.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/pixman_trap_arginfo.h"

static bool i16(zend_long v, uint32_t arg) { return px_check_range(v, INT16_MIN, INT16_MAX, arg); }
static bool i32(zend_long v, uint32_t arg) { return px_check_range(v, INT32_MIN, INT32_MAX, arg); }

/* pixman's sample grid (N_Y_FRAC) is defined for 1, 4 and 8 bpp; bpp 0 divides by zero, large values shift past int. */
static bool bpp_ok(zend_long bpp, uint32_t arg)
{
	if (bpp == 1 || bpp == 4 || bpp == 8) return true;
	zend_argument_value_error(arg, "must be 1, 4 or 8");
	return false;
}

/* The rasterisers write into a1, a4 or a8 bits images only. */
static pixman_image_t *alpha_image(zval *zv, uint32_t arg)
{
	pixman_image_t *image = px_image_arg(zv, arg);
	if (!image) return NULL;
	pixman_format_code_t f = pixman_image_get_format(image);
	if (!pixman_image_get_data(image) || (f != PIXMAN_a1 && f != PIXMAN_a4 && f != PIXMAN_a8)) {
		zend_argument_value_error(arg, "must be an a1, a4 or a8 bits image");
		return NULL;
	}
	return image;
}

/*
 * A const T * + count pair: an array of objects, read into a copy, or a string of count structs as C lays them out,
 * read in place for the call (pixman keeps nothing). The structs to hand pixman, or NULL with an error raised; *copy
 * is what the caller efrees.
 */
static const void *structs_arg(HashTable *arr, zend_string *packed, zend_long count, const px_struct *def, size_t size,
	uint32_t count_arg, uint32_t arg, void **copy)
{
	*copy = NULL;
	if (packed) {
		size_t held = ZSTR_LEN(packed) / size;
		if (count < 0 || (zend_ulong) count > held) {
			zend_argument_value_error(count_arg, "must be between 0 and the number of %zu-byte structs the string holds (%zu), "
				ZEND_LONG_FMT " given", size, held, count);
			return NULL;
		}
		return ZSTR_VAL(packed);
	}
	if (!px_check_count(count, arr, count_arg)) return NULL;
	*copy = safe_emalloc(count ? count : 1, size, 0);
	if (!px_struct_array_read(def, arr, count, *copy, arg)) {
		efree(*copy);
		*copy = NULL;
		return NULL;
	}
	return *copy;
}

static bool op_ok(zend_long op)
{
	if ((op >= PIXMAN_OP_CLEAR && op <= PIXMAN_OP_SATURATE) || (op >= PIXMAN_OP_DISJOINT_CLEAR && op <= PIXMAN_OP_DISJOINT_XOR)
			|| (op >= PIXMAN_OP_CONJOINT_CLEAR && op <= PIXMAN_OP_CONJOINT_XOR) || (op >= PIXMAN_OP_MULTIPLY && op <= PIXMAN_OP_HSL_LUMINOSITY)) {
		return true;
	}
	zend_argument_value_error(1, "must be a PIXMAN_OP_* constant, " ZEND_LONG_FMT " given", op);
	return false;
}

/* The mask pixman builds for these is an alpha format it can rasterise into. */
static bool mask_format_ok(zend_long f, uint32_t arg)
{
	if (f == PIXMAN_a1 || f == PIXMAN_a4 || f == PIXMAN_a8) return true;
	zend_argument_value_error(arg, "must be PIXMAN_a1, PIXMAN_a4 or PIXMAN_a8");
	return false;
}


/*
 * pixman_edge_step divides by e->dy when the error term crosses zero: with dy == 0 that is a
 * division by zero (n >= 0 and ne > 0, or n < 0 and ne <= 0). Mirrors pixman's own test.
 */
static bool step_divides_by_zero(const pixman_edge_t *e, zend_long n)
{
	if (e->dy != 0) return false;
	int64_t ne = (int64_t) e->e + (int64_t) n * (int64_t) e->dx;
	return n >= 0 ? ne > 0 : ne <= 0;
}

/*
 * pixman_edge_init's own arithmetic: dx = x_bot - x_top and dy = y_bot - y_top in 32 bits,
 * then dx / dy (or -dx / dy), then a step of y_start - y_top. Refuse the inputs where that
 * overflows, traps (INT32_MIN / -1) or divides by zero (dy == 0 and the step goes up).
 */
static bool edge_init_ok(zend_long y_start, zend_long x_top, zend_long y_top, zend_long x_bot, zend_long y_bot, uint32_t arg)
{
	int64_t dx = (int64_t) x_bot - x_top, dy = (int64_t) y_bot - y_top, n = (int64_t) y_start - y_top;
	if (dx < INT32_MIN || dx > INT32_MAX || dy < INT32_MIN || dy > INT32_MAX || n < INT32_MIN || n > INT32_MAX
			|| (dy == -1 && dx == INT32_MIN) || (dy == 0 && n < 0)) {
		zend_argument_value_error(arg, "describes an edge pixman cannot initialise (overflow, or zero height stepped upwards)");
		return false;
	}
	return true;
}

ZEND_FUNCTION(pixman_sample_ceil_y)
{
	zend_long y, bpp;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(bpp)
	ZEND_PARSE_PARAMETERS_END();
	if (!i32(y, 1) || !bpp_ok(bpp, 2)) RETURN_THROWS();
	RETURN_LONG(pixman_sample_ceil_y((pixman_fixed_t) y, (int) bpp));
}

ZEND_FUNCTION(pixman_sample_floor_y)
{
	zend_long y, bpp;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(bpp)
	ZEND_PARSE_PARAMETERS_END();
	if (!i32(y, 1) || !bpp_ok(bpp, 2)) RETURN_THROWS();
	RETURN_LONG(pixman_sample_floor_y((pixman_fixed_t) y, (int) bpp));
}

ZEND_FUNCTION(pixman_edge_step)
{
	zval *e;
	zend_long n;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(e, *px_edge.ce)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	pixman_edge_t edge;
	if (!px_struct_read(&px_edge, Z_OBJ_P(e), &edge) || !px_check_range(n, INT_MIN, INT_MAX, 2)) RETURN_THROWS();
	if (step_divides_by_zero(&edge, n)) {
		zend_argument_value_error(1, "has dy 0, and this step would divide by it");
		RETURN_THROWS();
	}
	pixman_edge_step(&edge, (int) n);
	px_struct_write(&px_edge, Z_OBJ_P(e), &edge);
}

ZEND_FUNCTION(pixman_edge_init)
{
	zval *e;
	zend_long bpp, ys, xt, yt, xb, yb;
	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_OBJECT_OF_CLASS(e, *px_edge.ce)
		Z_PARAM_LONG(bpp)
		Z_PARAM_LONG(ys)
		Z_PARAM_LONG(xt)
		Z_PARAM_LONG(yt)
		Z_PARAM_LONG(xb)
		Z_PARAM_LONG(yb)
	ZEND_PARSE_PARAMETERS_END();
	if (!bpp_ok(bpp, 2) || !i32(ys, 3) || !i32(xt, 4) || !i32(yt, 5) || !i32(xb, 6) || !i32(yb, 7)
			|| !edge_init_ok(ys, xt, yt, xb, yb, 1)) RETURN_THROWS();
	pixman_edge_t edge = {0};
	pixman_edge_init(&edge, (int) bpp, (pixman_fixed_t) ys, (pixman_fixed_t) xt, (pixman_fixed_t) yt, (pixman_fixed_t) xb, (pixman_fixed_t) yb);
	px_struct_write(&px_edge, Z_OBJ_P(e), &edge);
}

ZEND_FUNCTION(pixman_line_fixed_edge_init)
{
	zval *e, *l;
	zend_long bpp, y, xo, yo;
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(e, *px_edge.ce)
		Z_PARAM_LONG(bpp)
		Z_PARAM_LONG(y)
		Z_PARAM_OBJECT_OF_CLASS(l, *px_line_fixed.ce)
		Z_PARAM_LONG(xo)
		Z_PARAM_LONG(yo)
	ZEND_PARSE_PARAMETERS_END();
	pixman_line_fixed_t line;
	if (!bpp_ok(bpp, 2) || !i32(y, 3) || !px_struct_read(&px_line_fixed, Z_OBJ_P(l), &line)
			|| !px_check_range(xo, INT_MIN, INT_MAX, 5) || !px_check_range(yo, INT_MIN, INT_MAX, 6)) RETURN_THROWS();
	/* pixman_line_fixed_edge_init: top is the end with the smaller y, both offset by the fixed offsets (32-bit wrap). */
	const pixman_point_fixed_t *top = line.p1.y <= line.p2.y ? &line.p1 : &line.p2, *bot = top == &line.p1 ? &line.p2 : &line.p1;
	int32_t xof = (int32_t) ((uint32_t) xo << 16), yof = (int32_t) ((uint32_t) yo << 16);
	if (!edge_init_ok(y, (int32_t) ((uint32_t) top->x + (uint32_t) xof), (int32_t) ((uint32_t) top->y + (uint32_t) yof),
			(int32_t) ((uint32_t) bot->x + (uint32_t) xof), (int32_t) ((uint32_t) bot->y + (uint32_t) yof), 4)) RETURN_THROWS();
	pixman_edge_t edge = {0};
	pixman_line_fixed_edge_init(&edge, (int) bpp, (pixman_fixed_t) y, &line, (int) xo, (int) yo);
	px_struct_write(&px_edge, Z_OBJ_P(e), &edge);
}

ZEND_FUNCTION(pixman_rasterize_edges)
{
	zval *i, *l, *r;
	zend_long t, b;
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(l, *px_edge.ce)
		Z_PARAM_OBJECT_OF_CLASS(r, *px_edge.ce)
		Z_PARAM_LONG(t)
		Z_PARAM_LONG(b)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = alpha_image(i, 1);
	pixman_edge_t le, re;
	if (!image || !px_struct_read(&px_edge, Z_OBJ_P(l), &le) || !px_struct_read(&px_edge, Z_OBJ_P(r), &re)
			|| !i32(t, 4) || !i32(b, 5)) RETURN_THROWS();
	/*
	 * pixman walks rows from t until y == b exactly, with no bounds: t and b must be on the
	 * sample grid for the image's bpp, t <= b, t >= 0 and b's row inside the image. These are
	 * the values pixman_rasterize_trapezoid derives before it calls this. A grid value is one
	 * pixman_sample_ceil_y leaves unchanged (pixman_sample_floor_y is strictly below).
	 */
	int bpp = PIXMAN_FORMAT_BPP(pixman_image_get_format(image));
	if (t < 0 || pixman_sample_ceil_y((pixman_fixed_t) t, bpp) != t) {
		zend_argument_value_error(4, "must be a non-negative sample row (pixman_sample_ceil_y(t, %d) == t)", bpp);
		RETURN_THROWS();
	}
	if (b < t || pixman_sample_ceil_y((pixman_fixed_t) b, bpp) != b || pixman_fixed_to_int((pixman_fixed_t) b) >= pixman_image_get_height(image)) {
		zend_argument_value_error(5, "must be a sample row at or after t inside the image (pixman_sample_ceil_y(b, %d) == b)", bpp);
		RETURN_THROWS();
	}
	pixman_rasterize_edges(image, &le, &re, (pixman_fixed_t) t, (pixman_fixed_t) b);
	px_struct_write(&px_edge, Z_OBJ_P(l), &le);
	px_struct_write(&px_edge, Z_OBJ_P(r), &re);
}

ZEND_FUNCTION(pixman_add_traps)
{
	zval *i;
	zend_long xo, yo, n;
	HashTable *arr = NULL;
	zend_string *packed = NULL;
	void *copy;
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_LONG(xo)
		Z_PARAM_LONG(yo)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT_OR_STR(arr, packed)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = alpha_image(i, 1);
	if (!image || !i16(xo, 2) || !i16(yo, 3) ) RETURN_THROWS();
	const pixman_trap_t *t = structs_arg(arr, packed, n, &px_trap, sizeof(pixman_trap_t), 4, 5, &copy);
	if (!t) RETURN_THROWS();
	pixman_add_traps(image, (int16_t) xo, (int16_t) yo, (int) n, t);
	if (copy) efree(copy);
}

ZEND_FUNCTION(pixman_add_trapezoids)
{
	zval *i;
	zend_long xo, yo, n;
	HashTable *arr = NULL;
	zend_string *packed = NULL;
	void *copy;
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_LONG(xo)
		Z_PARAM_LONG(yo)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT_OR_STR(arr, packed)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = alpha_image(i, 1);
	if (!image || !i16(xo, 2) || !px_check_range(yo, INT_MIN, INT_MAX, 3) ) RETURN_THROWS();
	const pixman_trapezoid_t *t = structs_arg(arr, packed, n, &px_trapezoid, sizeof(pixman_trapezoid_t), 4, 5, &copy);
	if (!t) RETURN_THROWS();
	pixman_add_trapezoids(image, (int16_t) xo, (int) yo, (int) n, t);
	if (copy) efree(copy);
}

ZEND_FUNCTION(pixman_rasterize_trapezoid)
{
	zval *i, *z;
	zend_long xo, yo;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(z, *px_trapezoid.ce)
		Z_PARAM_LONG(xo)
		Z_PARAM_LONG(yo)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = alpha_image(i, 1);
	pixman_trapezoid_t trap;
	if (!image || !px_struct_read(&px_trapezoid, Z_OBJ_P(z), &trap)
			|| !px_check_range(xo, INT_MIN, INT_MAX, 3) || !px_check_range(yo, INT_MIN, INT_MAX, 4)) RETURN_THROWS();
	pixman_rasterize_trapezoid(image, &trap, (int) xo, (int) yo);
}

ZEND_FUNCTION(pixman_composite_trapezoids)
{
	zend_long op, mf, xs, ys, xd, yd, n;
	zval *s, *d;
	HashTable *arr = NULL;
	zend_string *packed = NULL;
	void *copy;
	ZEND_PARSE_PARAMETERS_START(10, 10)
		Z_PARAM_LONG(op)
		Z_PARAM_OBJECT_OF_CLASS(s, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(d, px_image_ce)
		Z_PARAM_LONG(mf)
		Z_PARAM_LONG(xs)
		Z_PARAM_LONG(ys)
		Z_PARAM_LONG(xd)
		Z_PARAM_LONG(yd)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT_OR_STR(arr, packed)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *src = px_image_arg(s, 2);
	pixman_image_t *dst = src ? px_image_arg(d, 3) : NULL;
	if (!dst || !op_ok(op) || !mask_format_ok(mf, 4) || !px_check_range(xs, INT_MIN, INT_MAX, 5) || !px_check_range(ys, INT_MIN, INT_MAX, 6)
			|| !px_check_range(xd, INT_MIN, INT_MAX, 7) || !px_check_range(yd, INT_MIN, INT_MAX, 8) ) RETURN_THROWS();
	const pixman_trapezoid_t *t = structs_arg(arr, packed, n, &px_trapezoid, sizeof(pixman_trapezoid_t), 9, 10, &copy);
	if (!t) RETURN_THROWS();
	pixman_composite_trapezoids((pixman_op_t) op, src, dst, (pixman_format_code_t) mf, (int) xs, (int) ys, (int) xd, (int) yd, (int) n, t);
	if (copy) efree(copy);
}

ZEND_FUNCTION(pixman_composite_triangles)
{
	zend_long op, mf, xs, ys, xd, yd, n;
	zval *s, *d;
	HashTable *arr = NULL;
	zend_string *packed = NULL;
	void *copy;
	ZEND_PARSE_PARAMETERS_START(10, 10)
		Z_PARAM_LONG(op)
		Z_PARAM_OBJECT_OF_CLASS(s, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(d, px_image_ce)
		Z_PARAM_LONG(mf)
		Z_PARAM_LONG(xs)
		Z_PARAM_LONG(ys)
		Z_PARAM_LONG(xd)
		Z_PARAM_LONG(yd)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT_OR_STR(arr, packed)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *src = px_image_arg(s, 2);
	pixman_image_t *dst = src ? px_image_arg(d, 3) : NULL;
	if (!dst || !op_ok(op) || !mask_format_ok(mf, 4) || !px_check_range(xs, INT_MIN, INT_MAX, 5) || !px_check_range(ys, INT_MIN, INT_MAX, 6)
			|| !px_check_range(xd, INT_MIN, INT_MAX, 7) || !px_check_range(yd, INT_MIN, INT_MAX, 8) ) RETURN_THROWS();
	const pixman_triangle_t *t = structs_arg(arr, packed, n, &px_triangle, sizeof(pixman_triangle_t), 9, 10, &copy);
	if (!t) RETURN_THROWS();
	pixman_composite_triangles((pixman_op_t) op, src, dst, (pixman_format_code_t) mf, (int) xs, (int) ys, (int) xd, (int) yd, (int) n, t);
	if (copy) efree(copy);
}

ZEND_FUNCTION(pixman_add_triangles)
{
	zval *i;
	zend_long xo, yo, n;
	HashTable *arr = NULL;
	zend_string *packed = NULL;
	void *copy;
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
		Z_PARAM_LONG(xo)
		Z_PARAM_LONG(yo)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT_OR_STR(arr, packed)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = alpha_image(i, 1);
	if (!image || !i32(xo, 2) || !i32(yo, 3) ) RETURN_THROWS();
	const pixman_triangle_t *t = structs_arg(arr, packed, n, &px_triangle, sizeof(pixman_triangle_t), 4, 5, &copy);
	if (!t) RETURN_THROWS();
	pixman_add_triangles(image, (int32_t) xo, (int32_t) yo, (int) n, t);
	if (copy) efree(copy);
}

void px_trap_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
