/*
 * pixman_region32_* (pixman-region32.c). A region object is C storage: init*
 * initialises it (releasing it first if it was), fini releases it.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/pixman_region32_arginfo.h"

/* Width and height are C `unsigned int`. */
static bool ext(zend_long v, uint32_t arg) { return px_check_range(v, 0, UINT32_MAX, arg); }
static bool pos(zend_long v, uint32_t arg) { return px_check_range(v, INT_MIN, INT_MAX, arg); }

ZEND_FUNCTION(pixman_region32_init)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_init(px_region32_for_init(r));
}

ZEND_FUNCTION(pixman_region32_init_rect)
{
	zval *r;
	zend_long x, y, w, h;
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	if (!pos(x, 2) || !pos(y, 3) || !ext(w, 4) || !ext(h, 5)) RETURN_THROWS();
	pixman_region32_init_rect(px_region32_for_init(r), (int) x, (int) y, (unsigned int) w, (unsigned int) h);
}

ZEND_FUNCTION(pixman_region32_init_rects)
{
	zval *r;
	HashTable *boxes;
	zend_long count;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
		Z_PARAM_ARRAY_HT(boxes)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();
	if (!px_check_count(count, boxes, 3)) RETURN_THROWS();
	pixman_box32_t *b = safe_emalloc(count ? count : 1, sizeof(*b), 0);
	if (!px_struct_array_read(&px_box32, boxes, count, b, 2)) {
		efree(b);
		RETURN_THROWS();
	}
	pixman_bool_t ok = pixman_region32_init_rects(px_region32_for_init(r), b, (int) count);
	efree(b);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_region32_init_with_extents)
{
	zval *r, *e;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(e, *px_box32.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_box32_t b;
	if (!px_struct_read(&px_box32, Z_OBJ_P(e), &b)) RETURN_THROWS();
	pixman_region32_init_with_extents(px_region32_for_init(r), &b);
}

ZEND_FUNCTION(pixman_region32_init_from_image)
{
	zval *r, *i;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = px_image_arg(i, 2);
	if (!image) RETURN_THROWS();
	pixman_region32_t *region = px_region32_for_init(r);
	/* pixman returns before initialising when the image is not a1 bits: start from an empty region. */
	pixman_region32_init(region);
	pixman_region32_init_from_image(region, image);
}

ZEND_FUNCTION(pixman_region32_fini)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	if (!region) RETURN_THROWS();
	pixman_region32_fini(region);
	px_region32_from(Z_OBJ_P(r))->initialised = false;
}

ZEND_FUNCTION(pixman_region32_translate)
{
	zval *r;
	zend_long x, y;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	if (!region || !pos(x, 2) || !pos(y, 3)) RETURN_THROWS();
	pixman_region32_translate(region, (int) x, (int) y);
}

ZEND_FUNCTION(pixman_region32_copy)
{
	zval *d, *s;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(d, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(s, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *dest = px_region32_arg(d, 1), *source = dest ? px_region32_arg(s, 2) : NULL;
	if (!source) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_copy(dest, source));
}

ZEND_FUNCTION(pixman_region32_intersect)
{
	zval *n, *a, *b;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(n, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(a, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *nr = px_region32_arg(n, 1), *ra = nr ? px_region32_arg(a, 2) : NULL, *rb = ra ? px_region32_arg(b, 3) : NULL;
	if (!rb) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_intersect(nr, ra, rb));
}

ZEND_FUNCTION(pixman_region32_union)
{
	zval *n, *a, *b;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(n, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(a, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *nr = px_region32_arg(n, 1), *ra = nr ? px_region32_arg(a, 2) : NULL, *rb = ra ? px_region32_arg(b, 3) : NULL;
	if (!rb) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_union(nr, ra, rb));
}

ZEND_FUNCTION(pixman_region32_intersect_rect)
{
	zval *d, *s;
	zend_long x, y, w, h;
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(d, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(s, px_region32_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *dest = px_region32_arg(d, 1), *source = dest ? px_region32_arg(s, 2) : NULL;
	if (!source || !pos(x, 3) || !pos(y, 4) || !ext(w, 5) || !ext(h, 6)) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_intersect_rect(dest, source, (int) x, (int) y, (unsigned int) w, (unsigned int) h));
}

ZEND_FUNCTION(pixman_region32_union_rect)
{
	zval *d, *s;
	zend_long x, y, w, h;
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(d, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(s, px_region32_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *dest = px_region32_arg(d, 1), *source = dest ? px_region32_arg(s, 2) : NULL;
	if (!source || !pos(x, 3) || !pos(y, 4) || !ext(w, 5) || !ext(h, 6)) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_union_rect(dest, source, (int) x, (int) y, (unsigned int) w, (unsigned int) h));
}

ZEND_FUNCTION(pixman_region32_subtract)
{
	zval *d, *m, *s;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(d, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(m, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(s, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *rd = px_region32_arg(d, 1), *rm = rd ? px_region32_arg(m, 2) : NULL, *rs = rm ? px_region32_arg(s, 3) : NULL;
	if (!rs) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_subtract(rd, rm, rs));
}

ZEND_FUNCTION(pixman_region32_inverse)
{
	zval *n, *a, *b;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(n, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(a, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_box32.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *nr = px_region32_arg(n, 1), *ra = nr ? px_region32_arg(a, 2) : NULL;
	pixman_box32_t box;
	if (!ra || !px_struct_read(&px_box32, Z_OBJ_P(b), &box)) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_inverse(nr, ra, &box));
}

ZEND_FUNCTION(pixman_region32_contains_point)
{
	zval *r, *b;
	zend_long x, y;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(b, *px_box32.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	if (!region || !pos(x, 2) || !pos(y, 3)) RETURN_THROWS();
	pixman_box32_t box = {0};
	pixman_bool_t in = pixman_region32_contains_point(region, (int) x, (int) y, b ? &box : NULL);
	if (b && in) px_struct_write(&px_box32, Z_OBJ_P(b), &box);
	RETURN_BOOL(in);
}

ZEND_FUNCTION(pixman_region32_contains_rectangle)
{
	zval *r, *b;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_box32.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	pixman_box32_t box;
	if (!region || !px_struct_read(&px_box32, Z_OBJ_P(b), &box)) RETURN_THROWS();
	RETURN_LONG(pixman_region32_contains_rectangle(region, &box));
}

ZEND_FUNCTION(pixman_region32_empty)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	if (!region) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_empty(region));
}

ZEND_FUNCTION(pixman_region32_not_empty)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	if (!region) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_not_empty(region));
}

ZEND_FUNCTION(pixman_region32_extents)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	if (!region) RETURN_THROWS();
	px_struct_new(&px_box32, pixman_region32_extents(region), return_value);
}

ZEND_FUNCTION(pixman_region32_n_rects)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	if (!region) RETURN_THROWS();
	RETURN_LONG(pixman_region32_n_rects(region));
}

ZEND_FUNCTION(pixman_region32_rectangles)
{
	zval *r, *n;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
		Z_PARAM_ZVAL(n)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	if (!region) RETURN_THROWS();
	int count = 0;
	pixman_box32_t *boxes = pixman_region32_rectangles(region, &count);
	array_init_size(return_value, (uint32_t) count);
	for (int i = 0; i < count; i++) {
		zval b;
		px_struct_new(&px_box32, &boxes[i], &b);
		add_next_index_zval(return_value, &b);
	}
	ZEND_TRY_ASSIGN_REF_LONG(n, count);
}

ZEND_FUNCTION(pixman_region32_equal)
{
	zval *a, *b;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(a, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *ra = px_region32_arg(a, 1), *rb = ra ? px_region32_arg(b, 2) : NULL;
	if (!rb) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_equal(ra, rb));
}

ZEND_FUNCTION(pixman_region32_selfcheck)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	if (!region) RETURN_THROWS();
	RETURN_BOOL(pixman_region32_selfcheck(region));
}

ZEND_FUNCTION(pixman_region32_reset)
{
	zval *r, *b;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_box32.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	pixman_box32_t box;
	if (!region || !px_struct_read(&px_box32, Z_OBJ_P(b), &box)) RETURN_THROWS();
	pixman_region32_reset(region, &box);
}

ZEND_FUNCTION(pixman_region32_clear)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region32_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region32_t *region = px_region32_arg(r, 1);
	if (!region) RETURN_THROWS();
	pixman_region32_clear(region);
}

void px_region32_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
