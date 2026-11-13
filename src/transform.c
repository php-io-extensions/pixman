/*
 * Fixed-point and floating-point transforms (pixman-matrix.c). A struct pixman
 * writes is written back into the object passed in.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/pixman_transform_arginfo.h"

static bool rd_t(zval *zv, pixman_transform_t *t) { return px_struct_read(&px_transform, Z_OBJ_P(zv), t); }
static void wr_t(zval *zv, const pixman_transform_t *t) { px_struct_write(&px_transform, Z_OBJ_P(zv), t); }
static bool rd_ft(zval *zv, pixman_f_transform_t *t) { return px_struct_read(&px_f_transform, Z_OBJ_P(zv), t); }
static void wr_ft(zval *zv, const pixman_f_transform_t *t) { px_struct_write(&px_f_transform, Z_OBJ_P(zv), t); }

/* A fixed-point argument: pixman_fixed_t is int32_t. */
static bool fx(zend_long v, uint32_t arg) { return px_check_range(v, INT32_MIN, INT32_MAX, arg); }

ZEND_FUNCTION(pixman_transform_init_identity)
{
	zval *m;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t t;
	pixman_transform_init_identity(&t);
	wr_t(m, &t);
}

ZEND_FUNCTION(pixman_transform_point_3d)
{
	zval *m, *v;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(v, *px_vector.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t t;
	pixman_vector_t vec;
	if (!rd_t(m, &t) || !px_struct_read(&px_vector, Z_OBJ_P(v), &vec)) RETURN_THROWS();
	pixman_bool_t ok = pixman_transform_point_3d(&t, &vec);
	px_struct_write(&px_vector, Z_OBJ_P(v), &vec);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_transform_point)
{
	zval *m, *v;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(v, *px_vector.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t t;
	pixman_vector_t vec;
	if (!rd_t(m, &t) || !px_struct_read(&px_vector, Z_OBJ_P(v), &vec)) RETURN_THROWS();
	pixman_bool_t ok = pixman_transform_point(&t, &vec);
	px_struct_write(&px_vector, Z_OBJ_P(v), &vec);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_transform_multiply)
{
	zval *d, *l, *r;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(d, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(l, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(r, *px_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t dt, lt, rt;
	if (!rd_t(d, &dt) || !rd_t(l, &lt) || !rd_t(r, &rt)) RETURN_THROWS();
	pixman_bool_t ok = pixman_transform_multiply(&dt, &lt, &rt);
	wr_t(d, &dt);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_transform_init_scale)
{
	zval *m;
	zend_long sx, sy;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
		Z_PARAM_LONG(sx)
		Z_PARAM_LONG(sy)
	ZEND_PARSE_PARAMETERS_END();
	if (!fx(sx, 2) || !fx(sy, 3)) RETURN_THROWS();
	pixman_transform_t t;
	pixman_transform_init_scale(&t, (pixman_fixed_t) sx, (pixman_fixed_t) sy);
	wr_t(m, &t);
}

/* forward and reverse are optional in pixman: either may be null. */
static bool rd_pair(zval *f, zval *r, pixman_transform_t *ft, pixman_transform_t *rt)
{
	return (!f || rd_t(f, ft)) && (!r || rd_t(r, rt));
}

static void wr_pair(zval *f, zval *r, const pixman_transform_t *ft, const pixman_transform_t *rt)
{
	if (f) wr_t(f, ft);
	if (r) wr_t(r, rt);
}

ZEND_FUNCTION(pixman_transform_scale)
{
	zval *f, *r;
	zend_long sx, sy;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(f, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(r, *px_transform.ce)
		Z_PARAM_LONG(sx)
		Z_PARAM_LONG(sy)
	ZEND_PARSE_PARAMETERS_END();
	if (!fx(sx, 3) || !fx(sy, 4)) RETURN_THROWS();
	pixman_transform_t ft, rt;
	if (!rd_pair(f, r, &ft, &rt)) RETURN_THROWS();
	pixman_bool_t ok = pixman_transform_scale(f ? &ft : NULL, r ? &rt : NULL, (pixman_fixed_t) sx, (pixman_fixed_t) sy);
	wr_pair(f, r, &ft, &rt);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_transform_init_rotate)
{
	zval *m;
	zend_long c, s;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
		Z_PARAM_LONG(c)
		Z_PARAM_LONG(s)
	ZEND_PARSE_PARAMETERS_END();
	if (!fx(c, 2) || !fx(s, 3)) RETURN_THROWS();
	pixman_transform_t t;
	pixman_transform_init_rotate(&t, (pixman_fixed_t) c, (pixman_fixed_t) s);
	wr_t(m, &t);
}

ZEND_FUNCTION(pixman_transform_rotate)
{
	zval *f, *r;
	zend_long c, s;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(f, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(r, *px_transform.ce)
		Z_PARAM_LONG(c)
		Z_PARAM_LONG(s)
	ZEND_PARSE_PARAMETERS_END();
	if (!fx(c, 3) || !fx(s, 4)) RETURN_THROWS();
	pixman_transform_t ft, rt;
	if (!rd_pair(f, r, &ft, &rt)) RETURN_THROWS();
	pixman_bool_t ok = pixman_transform_rotate(f ? &ft : NULL, r ? &rt : NULL, (pixman_fixed_t) c, (pixman_fixed_t) s);
	wr_pair(f, r, &ft, &rt);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_transform_init_translate)
{
	zval *m;
	zend_long tx, ty;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
		Z_PARAM_LONG(tx)
		Z_PARAM_LONG(ty)
	ZEND_PARSE_PARAMETERS_END();
	if (!fx(tx, 2) || !fx(ty, 3)) RETURN_THROWS();
	pixman_transform_t t;
	pixman_transform_init_translate(&t, (pixman_fixed_t) tx, (pixman_fixed_t) ty);
	wr_t(m, &t);
}

ZEND_FUNCTION(pixman_transform_translate)
{
	zval *f, *r;
	zend_long tx, ty;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(f, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(r, *px_transform.ce)
		Z_PARAM_LONG(tx)
		Z_PARAM_LONG(ty)
	ZEND_PARSE_PARAMETERS_END();
	if (!fx(tx, 3) || !fx(ty, 4)) RETURN_THROWS();
	pixman_transform_t ft, rt;
	if (!rd_pair(f, r, &ft, &rt)) RETURN_THROWS();
	pixman_bool_t ok = pixman_transform_translate(f ? &ft : NULL, r ? &rt : NULL, (pixman_fixed_t) tx, (pixman_fixed_t) ty);
	wr_pair(f, r, &ft, &rt);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_transform_bounds)
{
	zval *m, *b;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_box16.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t t;
	pixman_box16_t box;
	if (!rd_t(m, &t) || !px_struct_read(&px_box16, Z_OBJ_P(b), &box)) RETURN_THROWS();
	pixman_bool_t ok = pixman_transform_bounds(&t, &box);
	px_struct_write(&px_box16, Z_OBJ_P(b), &box);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_transform_invert)
{
	zval *d, *s;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(d, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(s, *px_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t dt, st;
	if (!rd_t(d, &dt) || !rd_t(s, &st)) RETURN_THROWS();
	pixman_bool_t ok = pixman_transform_invert(&dt, &st);
	wr_t(d, &dt);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_transform_is_identity)
{
	zval *m;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t t;
	if (!rd_t(m, &t)) RETURN_THROWS();
	RETURN_BOOL(pixman_transform_is_identity(&t));
}

ZEND_FUNCTION(pixman_transform_is_scale)
{
	zval *m;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t t;
	if (!rd_t(m, &t)) RETURN_THROWS();
	RETURN_BOOL(pixman_transform_is_scale(&t));
}

ZEND_FUNCTION(pixman_transform_is_int_translate)
{
	zval *m;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t t;
	if (!rd_t(m, &t)) RETURN_THROWS();
	RETURN_BOOL(pixman_transform_is_int_translate(&t));
}

ZEND_FUNCTION(pixman_transform_is_inverse)
{
	zval *a, *b;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(a, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t at, bt;
	if (!rd_t(a, &at) || !rd_t(b, &bt)) RETURN_THROWS();
	RETURN_BOOL(pixman_transform_is_inverse(&at, &bt));
}

ZEND_FUNCTION(pixman_transform_from_pixman_f_transform)
{
	zval *m, *fm;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(fm, *px_f_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t t;
	pixman_f_transform_t ft;
	if (!rd_t(m, &t) || !rd_ft(fm, &ft)) RETURN_THROWS();
	pixman_bool_t ok = pixman_transform_from_pixman_f_transform(&t, &ft);
	wr_t(m, &t);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_f_transform_from_pixman_transform)
{
	zval *fm, *m;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(fm, *px_f_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_transform_t t;
	pixman_f_transform_t ft;
	if (!rd_ft(fm, &ft) || !rd_t(m, &t)) RETURN_THROWS();
	pixman_f_transform_from_pixman_transform(&ft, &t);
	wr_ft(fm, &ft);
}

ZEND_FUNCTION(pixman_f_transform_invert)
{
	zval *d, *s;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(d, *px_f_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(s, *px_f_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t dt, st;
	if (!rd_ft(d, &dt) || !rd_ft(s, &st)) RETURN_THROWS();
	pixman_bool_t ok = pixman_f_transform_invert(&dt, &st);
	wr_ft(d, &dt);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_f_transform_point)
{
	zval *m, *v;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_f_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(v, *px_f_vector.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t t;
	pixman_f_vector_t vec;
	if (!rd_ft(m, &t) || !px_struct_read(&px_f_vector, Z_OBJ_P(v), &vec)) RETURN_THROWS();
	pixman_bool_t ok = pixman_f_transform_point(&t, &vec);
	px_struct_write(&px_f_vector, Z_OBJ_P(v), &vec);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_f_transform_point_3d)
{
	zval *m, *v;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_f_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(v, *px_f_vector.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t t;
	pixman_f_vector_t vec;
	if (!rd_ft(m, &t) || !px_struct_read(&px_f_vector, Z_OBJ_P(v), &vec)) RETURN_THROWS();
	pixman_f_transform_point_3d(&t, &vec);
	px_struct_write(&px_f_vector, Z_OBJ_P(v), &vec);
}

ZEND_FUNCTION(pixman_f_transform_multiply)
{
	zval *d, *l, *r;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(d, *px_f_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(l, *px_f_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(r, *px_f_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t dt, lt, rt;
	if (!rd_ft(d, &dt) || !rd_ft(l, &lt) || !rd_ft(r, &rt)) RETURN_THROWS();
	pixman_f_transform_multiply(&dt, &lt, &rt);
	wr_ft(d, &dt);
}

ZEND_FUNCTION(pixman_f_transform_init_scale)
{
	zval *m;
	double sx, sy;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_f_transform.ce)
		Z_PARAM_DOUBLE(sx)
		Z_PARAM_DOUBLE(sy)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t t;
	pixman_f_transform_init_scale(&t, sx, sy);
	wr_ft(m, &t);
}

static bool rd_fpair(zval *f, zval *r, pixman_f_transform_t *ft, pixman_f_transform_t *rt)
{
	return (!f || rd_ft(f, ft)) && (!r || rd_ft(r, rt));
}

static void wr_fpair(zval *f, zval *r, const pixman_f_transform_t *ft, const pixman_f_transform_t *rt)
{
	if (f) wr_ft(f, ft);
	if (r) wr_ft(r, rt);
}

ZEND_FUNCTION(pixman_f_transform_scale)
{
	zval *f, *r;
	double sx, sy;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(f, *px_f_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(r, *px_f_transform.ce)
		Z_PARAM_DOUBLE(sx)
		Z_PARAM_DOUBLE(sy)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t ft, rt;
	if (!rd_fpair(f, r, &ft, &rt)) RETURN_THROWS();
	pixman_bool_t ok = pixman_f_transform_scale(f ? &ft : NULL, r ? &rt : NULL, sx, sy);
	wr_fpair(f, r, &ft, &rt);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_f_transform_init_rotate)
{
	zval *m;
	double c, s;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_f_transform.ce)
		Z_PARAM_DOUBLE(c)
		Z_PARAM_DOUBLE(s)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t t;
	pixman_f_transform_init_rotate(&t, c, s);
	wr_ft(m, &t);
}

ZEND_FUNCTION(pixman_f_transform_rotate)
{
	zval *f, *r;
	double c, s;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(f, *px_f_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(r, *px_f_transform.ce)
		Z_PARAM_DOUBLE(c)
		Z_PARAM_DOUBLE(s)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t ft, rt;
	if (!rd_fpair(f, r, &ft, &rt)) RETURN_THROWS();
	pixman_bool_t ok = pixman_f_transform_rotate(f ? &ft : NULL, r ? &rt : NULL, c, s);
	wr_fpair(f, r, &ft, &rt);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_f_transform_init_translate)
{
	zval *m;
	double tx, ty;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_f_transform.ce)
		Z_PARAM_DOUBLE(tx)
		Z_PARAM_DOUBLE(ty)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t t;
	pixman_f_transform_init_translate(&t, tx, ty);
	wr_ft(m, &t);
}

ZEND_FUNCTION(pixman_f_transform_translate)
{
	zval *f, *r;
	double tx, ty;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(f, *px_f_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(r, *px_f_transform.ce)
		Z_PARAM_DOUBLE(tx)
		Z_PARAM_DOUBLE(ty)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t ft, rt;
	if (!rd_fpair(f, r, &ft, &rt)) RETURN_THROWS();
	pixman_bool_t ok = pixman_f_transform_translate(f ? &ft : NULL, r ? &rt : NULL, tx, ty);
	wr_fpair(f, r, &ft, &rt);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_f_transform_bounds)
{
	zval *m, *b;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_f_transform.ce)
		Z_PARAM_OBJECT_OF_CLASS(b, *px_box16.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t t;
	pixman_box16_t box;
	if (!rd_ft(m, &t) || !px_struct_read(&px_box16, Z_OBJ_P(b), &box)) RETURN_THROWS();
	pixman_bool_t ok = pixman_f_transform_bounds(&t, &box);
	px_struct_write(&px_box16, Z_OBJ_P(b), &box);
	RETURN_BOOL(ok);
}

ZEND_FUNCTION(pixman_f_transform_init_identity)
{
	zval *m;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(m, *px_f_transform.ce)
	ZEND_PARSE_PARAMETERS_END();
	pixman_f_transform_t t;
	pixman_f_transform_init_identity(&t);
	wr_ft(m, &t);
}

void px_transform_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
