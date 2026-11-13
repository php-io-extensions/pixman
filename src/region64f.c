/*
 * pixman_region64f_* (pixman-region64f.c). A region object is C storage: init*
 * initialises it (releasing it first if it was), fini releases it.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/pixman_region64f_arginfo.h"

/* Width and height are C `unsigned int`. */
static bool ext(zend_long v, uint32_t arg) { return px_check_range(v, 0, UINT32_MAX, arg); }
static bool pos(zend_long v, uint32_t arg) { return px_check_range(v, INT_MIN, INT_MAX, arg); }

ZEND_FUNCTION(pixman_region64f_init)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_init(px_region64f_for_init(r));
}

ZEND_FUNCTION(pixman_region64f_init_rect)
{
	zval *r;
	zend_long x, y, w, h;
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	if (!pos(x, 2) || !pos(y, 3) || !ext(w, 4) || !ext(h, 5)) RETURN_THROWS();
	pixman_region64f_init_rect(px_region64f_for_init(r), (int) x, (int) y, (unsigned int) w, (unsigned int) h);
}

ZEND_FUNCTION(pixman_region64f_init_rects)
{
	zval *r;
	HashTable *boxes;
	zend_long count;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_ARRAY_HT(boxes)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();
	if (!px_check_count(count, boxes, 3)) RETURN_THROWS();
	pixman_box64f_t *b = safe_emalloc(count ? count : 1, sizeof(*b), 0);
	if (!px_struct_array_read(&px_box64f, boxes, count, b, 2)) {
		efree(b);
		RETURN_THROWS();
	}
	pixman_bool_t ok = pixman_region64f_init_rects(px_region64f_for_init(r), b, (int) count);
	efree(b);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_region64f_init_with_extents)
{
	zval *r, *e;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(e, *px_box64f.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_box64f_t b;
	if (!px_struct_read(&px_box64f, Z_OBJ_P(e), &b)) RETURN_THROWS();
	pixman_region64f_init_with_extents(px_region64f_for_init(r), &b);
}

ZEND_FUNCTION(pixman_region64f_init_from_image)
{
	zval *r, *i;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *image = px_image_arg(i, 2);
	if (!image) RETURN_THROWS();
	pixman_region64f_t *region = px_region64f_for_init(r);
	/* pixman returns before initialising when the image is not a1 bits: start from an empty region. */
	pixman_region64f_init(region);
	pixman_region64f_init_from_image(region, image);
}

ZEND_FUNCTION(pixman_region64f_fini)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region) RETURN_THROWS();
	pixman_region64f_fini(region);
	px_region64f_from(Z_OBJ_P(r))->initialised = false;
}

ZEND_FUNCTION(pixman_region64f_translate)
{
	zval *r;
	zend_long x, y;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region || !pos(x, 2) || !pos(y, 3)) RETURN_THROWS();
	pixman_region64f_translate(region, (int) x, (int) y);
}

ZEND_FUNCTION(pixman_region64f_copy)
{
	zval *d, *s;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(d, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(s, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *dest = px_region64f_arg(d, 1), *source = dest ? px_region64f_arg(s, 2) : NULL;
	if (!source) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_copy(dest, source));
}

ZEND_FUNCTION(pixman_region64f_intersect)
{
	zval *n, *a, *b;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(n, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(a, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *nr = px_region64f_arg(n, 1), *ra = nr ? px_region64f_arg(a, 2) : NULL, *rb = ra ? px_region64f_arg(b, 3) : NULL;
	if (!rb) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_intersect(nr, ra, rb));
}

ZEND_FUNCTION(pixman_region64f_union)
{
	zval *n, *a, *b;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(n, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(a, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *nr = px_region64f_arg(n, 1), *ra = nr ? px_region64f_arg(a, 2) : NULL, *rb = ra ? px_region64f_arg(b, 3) : NULL;
	if (!rb) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_union(nr, ra, rb));
}

ZEND_FUNCTION(pixman_region64f_intersect_rect)
{
	zval *d, *s;
	zend_long x, y, w, h;
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(d, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(s, px_region64f_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *dest = px_region64f_arg(d, 1), *source = dest ? px_region64f_arg(s, 2) : NULL;
	if (!source || !pos(x, 3) || !pos(y, 4) || !ext(w, 5) || !ext(h, 6)) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_intersect_rect(dest, source, (int) x, (int) y, (unsigned int) w, (unsigned int) h));
}

ZEND_FUNCTION(pixman_region64f_union_rect)
{
	zval *d, *s;
	zend_long x, y, w, h;
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(d, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(s, px_region64f_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *dest = px_region64f_arg(d, 1), *source = dest ? px_region64f_arg(s, 2) : NULL;
	if (!source || !pos(x, 3) || !pos(y, 4) || !ext(w, 5) || !ext(h, 6)) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_union_rect(dest, source, (int) x, (int) y, (unsigned int) w, (unsigned int) h));
}

ZEND_FUNCTION(pixman_region64f_subtract)
{
	zval *d, *m, *s;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(d, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(m, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(s, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *rd = px_region64f_arg(d, 1), *rm = rd ? px_region64f_arg(m, 2) : NULL, *rs = rm ? px_region64f_arg(s, 3) : NULL;
	if (!rs) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_subtract(rd, rm, rs));
}

ZEND_FUNCTION(pixman_region64f_inverse)
{
	zval *n, *a, *b;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(n, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(a, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_box64f.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *nr = px_region64f_arg(n, 1), *ra = nr ? px_region64f_arg(a, 2) : NULL;
	pixman_box64f_t box;
	if (!ra || !px_struct_read(&px_box64f, Z_OBJ_P(b), &box)) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_inverse(nr, ra, &box));
}

ZEND_FUNCTION(pixman_region64f_contains_point)
{
	zval *r, *b;
	zend_long x, y;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(b, *px_box64f.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region || !pos(x, 2) || !pos(y, 3)) RETURN_THROWS();
	pixman_box64f_t box = {0};
	pixman_bool_t in = pixman_region64f_contains_point(region, (int) x, (int) y, b ? &box : NULL);
	if (b && in) px_struct_write(&px_box64f, Z_OBJ_P(b), &box);
	RETURN_BOOL(in);
}

ZEND_FUNCTION(pixman_region64f_contains_rectangle)
{
	zval *r, *b;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_box64f.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	pixman_box64f_t box;
	if (!region || !px_struct_read(&px_box64f, Z_OBJ_P(b), &box)) RETURN_THROWS();
	RETURN_LONG(pixman_region64f_contains_rectangle(region, &box));
}

ZEND_FUNCTION(pixman_region64f_empty)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_empty(region));
}

ZEND_FUNCTION(pixman_region64f_not_empty)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_not_empty(region));
}

ZEND_FUNCTION(pixman_region64f_extents)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region) RETURN_THROWS();
	px_struct_new(&px_box64f, pixman_region64f_extents(region), return_value);
}

ZEND_FUNCTION(pixman_region64f_n_rects)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region) RETURN_THROWS();
	RETURN_LONG(pixman_region64f_n_rects(region));
}

ZEND_FUNCTION(pixman_region64f_rectangles)
{
	zval *r, *n;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_ZVAL(n)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region) RETURN_THROWS();
	int count = 0;
	pixman_box64f_t *boxes = pixman_region64f_rectangles(region, &count);
	array_init_size(return_value, (uint32_t) count);
	for (int i = 0; i < count; i++) {
		zval b;
		px_struct_new(&px_box64f, &boxes[i], &b);
		add_next_index_zval(return_value, &b);
	}
	ZEND_TRY_ASSIGN_REF_LONG(n, count);
}

ZEND_FUNCTION(pixman_region64f_equal)
{
	zval *a, *b;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(a, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *ra = px_region64f_arg(a, 1), *rb = ra ? px_region64f_arg(b, 2) : NULL;
	if (!rb) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_equal(ra, rb));
}

ZEND_FUNCTION(pixman_region64f_selfcheck)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_selfcheck(region));
}

ZEND_FUNCTION(pixman_region64f_reset)
{
	zval *r, *b;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_box64f.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	pixman_box64f_t box;
	if (!region || !px_struct_read(&px_box64f, Z_OBJ_P(b), &box)) RETURN_THROWS();
	pixman_region64f_reset(region, &box);
}

ZEND_FUNCTION(pixman_region64f_clear)
{
	zval *r;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region) RETURN_THROWS();
	pixman_region64f_clear(region);
}

ZEND_FUNCTION(pixman_region64f_init_rectf)
{
	zval *r;
	double x, y, w, h;
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
		Z_PARAM_DOUBLE(w)
		Z_PARAM_DOUBLE(h)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_init_rectf(px_region64f_for_init(r), x, y, w, h);
}

ZEND_FUNCTION(pixman_region64f_translatef)
{
	zval *r;
	double x, y;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region) RETURN_THROWS();
	pixman_region64f_translatef(region, x, y);
}

ZEND_FUNCTION(pixman_region64f_intersect_rectf)
{
	zval *d, *s;
	double x, y, w, h;
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(d, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(s, px_region64f_ce)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
		Z_PARAM_DOUBLE(w)
		Z_PARAM_DOUBLE(h)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *dest = px_region64f_arg(d, 1), *source = dest ? px_region64f_arg(s, 2) : NULL;
	if (!source) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_intersect_rectf(dest, source, x, y, w, h));
}

ZEND_FUNCTION(pixman_region64f_union_rectf)
{
	zval *d, *s;
	double x, y, w, h;
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(d, px_region64f_ce)
		Z_PARAM_OBJECT_OF_CLASS(s, px_region64f_ce)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
		Z_PARAM_DOUBLE(w)
		Z_PARAM_DOUBLE(h)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *dest = px_region64f_arg(d, 1), *source = dest ? px_region64f_arg(s, 2) : NULL;
	if (!source) RETURN_THROWS();
	RETURN_BOOL(pixman_region64f_union_rectf(dest, source, x, y, w, h));
}

ZEND_FUNCTION(pixman_region64f_contains_pointf)
{
	zval *r, *b;
	double x, y;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(r, px_region64f_ce)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(b, *px_box64f.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_region64f_t *region = px_region64f_arg(r, 1);
	if (!region) RETURN_THROWS();
	pixman_box64f_t box = {0};
	pixman_bool_t in = pixman_region64f_contains_pointf(region, x, y, b ? &box : NULL);
	if (b && in) px_struct_write(&px_box64f, Z_OBJ_P(b), &box);
	RETURN_BOOL(in);
}

void px_region64f_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
