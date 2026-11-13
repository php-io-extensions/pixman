/*
 * Glyph caches (pixman-glyph.c). Keys are ints; glyph handles are ints the
 * binding records against their keys, and checks before pixman sees them.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/pixman_glyph_arginfo.h"

static void *key(zend_long k) { return (void *) (uintptr_t) k; }

/* After thaw pixman may have evicted glyphs: drop the handles that no longer look up to themselves. */
static void prune(px_glyph_cache_obj *c)
{
	zend_ulong addr;
	zval *keys;
	ZEND_HASH_FOREACH_NUM_KEY_VAL(&c->glyphs, addr, keys) {
		zend_long fk = Z_LVAL_P(zend_hash_index_find(Z_ARRVAL_P(keys), 0));
		zend_long gk = Z_LVAL_P(zend_hash_index_find(Z_ARRVAL_P(keys), 1));
		if (pixman_glyph_cache_lookup(c->cache, key(fk), key(gk)) != (const void *) (uintptr_t) addr) {
			zend_hash_index_del(&c->glyphs, addr);
		}
	} ZEND_HASH_FOREACH_END();
}

ZEND_FUNCTION(pixman_glyph_cache_create)
{
	ZEND_PARSE_PARAMETERS_NONE();
	pixman_glyph_cache_t *cache = pixman_glyph_cache_create();
	if (!cache) RETURN_NULL();
	object_init_ex(return_value, px_glyph_cache_ce);
	px_glyph_cache_from(Z_OBJ_P(return_value))->cache = cache;
}

ZEND_FUNCTION(pixman_glyph_cache_destroy)
{
	zval *c;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(c, px_glyph_cache_ce)
	ZEND_PARSE_PARAMETERS_END();
	px_glyph_cache_obj *o = px_glyph_cache_arg(c, 1);
	if (!o) RETURN_THROWS();
	px_glyph_cache_release(o);
}

ZEND_FUNCTION(pixman_glyph_cache_freeze)
{
	zval *c;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(c, px_glyph_cache_ce)
	ZEND_PARSE_PARAMETERS_END();
	px_glyph_cache_obj *o = px_glyph_cache_arg(c, 1);
	if (!o) RETURN_THROWS();
	pixman_glyph_cache_freeze(o->cache);
	o->frozen++;
}

ZEND_FUNCTION(pixman_glyph_cache_thaw)
{
	zval *c;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(c, px_glyph_cache_ce)
	ZEND_PARSE_PARAMETERS_END();
	px_glyph_cache_obj *o = px_glyph_cache_arg(c, 1);
	if (!o) RETURN_THROWS();
	if (o->frozen == 0) {
		/* pixman's thaw on an unfrozen cache drives freeze_count negative; inserts and destroy then fail for good. */
		zend_value_error("pixman_glyph_cache_thaw() called more times than pixman_glyph_cache_freeze()");
		RETURN_THROWS();
	}
	pixman_glyph_cache_thaw(o->cache);
	o->frozen--;
	prune(o);
}

ZEND_FUNCTION(pixman_glyph_cache_lookup)
{
	zval *c;
	zend_long fk, gk;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(c, px_glyph_cache_ce)
		Z_PARAM_LONG(fk)
		Z_PARAM_LONG(gk)
	ZEND_PARSE_PARAMETERS_END();
	px_glyph_cache_obj *o = px_glyph_cache_arg(c, 1);
	if (!o) RETURN_THROWS();
	RETURN_LONG((zend_long) (uintptr_t) pixman_glyph_cache_lookup(o->cache, key(fk), key(gk)));
}

ZEND_FUNCTION(pixman_glyph_cache_insert)
{
	zval *c, *i;
	zend_long fk, gk, ox, oy;
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(c, px_glyph_cache_ce)
		Z_PARAM_LONG(fk)
		Z_PARAM_LONG(gk)
		Z_PARAM_LONG(ox)
		Z_PARAM_LONG(oy)
		Z_PARAM_OBJECT_OF_CLASS(i, px_image_ce)
	ZEND_PARSE_PARAMETERS_END();
	px_glyph_cache_obj *o = px_glyph_cache_arg(c, 1);
	if (!o) RETURN_THROWS();
	pixman_image_t *image = px_image_arg(i, 6);
	if (!image || !px_check_range(ox, INT_MIN, INT_MAX, 4) || !px_check_range(oy, INT_MIN, INT_MAX, 5)) RETURN_THROWS();
	/* pixman does not check for an existing key; a second entry would shadow the first in lookups. */
	if (pixman_glyph_cache_lookup(o->cache, key(fk), key(gk))) {
		zend_value_error("A glyph with these keys is already cached; remove it first");
		RETURN_THROWS();
	}
	const void *glyph = pixman_glyph_cache_insert(o->cache, key(fk), key(gk), (int) ox, (int) oy, image);
	if (glyph) px_glyph_record(o, glyph, fk, gk);
	RETURN_LONG((zend_long) (uintptr_t) glyph);
}

ZEND_FUNCTION(pixman_glyph_cache_remove)
{
	zval *c;
	zend_long fk, gk;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(c, px_glyph_cache_ce)
		Z_PARAM_LONG(fk)
		Z_PARAM_LONG(gk)
	ZEND_PARSE_PARAMETERS_END();
	px_glyph_cache_obj *o = px_glyph_cache_arg(c, 1);
	if (!o) RETURN_THROWS();
	const void *glyph = pixman_glyph_cache_lookup(o->cache, key(fk), key(gk));
	pixman_glyph_cache_remove(o->cache, key(fk), key(gk));
	if (glyph) px_glyph_forget(o, glyph);
}

static pixman_glyph_t *glyphs_arg(px_glyph_cache_obj *o, HashTable *arr, zend_long n, uint32_t arg_arr, uint32_t arg_n)
{
	if (!px_check_count(n, arr, arg_n)) return NULL;
	pixman_glyph_t *g = safe_emalloc(n ? n : 1, sizeof(*g), 0);
	if (!px_glyphs_read(o, arr, n, g, arg_arr)) {
		efree(g);
		return NULL;
	}
	return g;
}

ZEND_FUNCTION(pixman_glyph_get_extents)
{
	zval *c, *e;
	zend_long n;
	HashTable *arr;
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(c, px_glyph_cache_ce)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT(arr)
		Z_PARAM_OBJECT_OF_CLASS(e, *px_box32.ce)
	ZEND_PARSE_PARAMETERS_END();
	px_glyph_cache_obj *o = px_glyph_cache_arg(c, 1);
	if (!o) RETURN_THROWS();
	pixman_glyph_t *g = glyphs_arg(o, arr, n, 3, 2);
	if (!g) RETURN_THROWS();
	pixman_box32_t box = {0};
	pixman_glyph_get_extents(o->cache, (int) n, g, &box);
	efree(g);
	px_struct_write(&px_box32, Z_OBJ_P(e), &box);
}

ZEND_FUNCTION(pixman_glyph_get_mask_format)
{
	zval *c;
	zend_long n;
	HashTable *arr;
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(c, px_glyph_cache_ce)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT(arr)
	ZEND_PARSE_PARAMETERS_END();
	px_glyph_cache_obj *o = px_glyph_cache_arg(c, 1);
	if (!o) RETURN_THROWS();
	pixman_glyph_t *g = glyphs_arg(o, arr, n, 3, 2);
	if (!g) RETURN_THROWS();
	pixman_format_code_t f = pixman_glyph_get_mask_format(o->cache, (int) n, g);
	efree(g);
	RETURN_LONG(f);
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

static bool i32(zend_long v, uint32_t arg) { return px_check_range(v, INT32_MIN, INT32_MAX, arg); }

ZEND_FUNCTION(pixman_composite_glyphs)
{
	zend_long op, mf, sx, sy, mx, my, dx, dy, w, h, n;
	zval *s, *d, *c;
	HashTable *arr;
	ZEND_PARSE_PARAMETERS_START(15, 15)
		Z_PARAM_LONG(op)
		Z_PARAM_OBJECT_OF_CLASS(s, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(d, px_image_ce)
		Z_PARAM_LONG(mf)
		Z_PARAM_LONG(sx)
		Z_PARAM_LONG(sy)
		Z_PARAM_LONG(mx)
		Z_PARAM_LONG(my)
		Z_PARAM_LONG(dx)
		Z_PARAM_LONG(dy)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_OBJECT_OF_CLASS(c, px_glyph_cache_ce)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT(arr)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *src = px_image_arg(s, 2);
	pixman_image_t *dest = src ? px_image_arg(d, 3) : NULL;
	px_glyph_cache_obj *o = dest ? px_glyph_cache_arg(c, 13) : NULL;
	if (!o || !op_ok(op) || !pixman_format_supported_destination((pixman_format_code_t) mf)
			|| !i32(sx, 5) || !i32(sy, 6) || !i32(mx, 7) || !i32(my, 8) || !i32(dx, 9) || !i32(dy, 10) || !i32(w, 11) || !i32(h, 12)) {
		if (!EG(exception)) zend_argument_value_error(4, "must be a PIXMAN_* format pixman can write");
		RETURN_THROWS();
	}
	pixman_glyph_t *g = glyphs_arg(o, arr, n, 15, 14);
	if (!g) RETURN_THROWS();
	pixman_composite_glyphs((pixman_op_t) op, src, dest, (pixman_format_code_t) mf, (int32_t) sx, (int32_t) sy, (int32_t) mx, (int32_t) my,
		(int32_t) dx, (int32_t) dy, (int32_t) w, (int32_t) h, o->cache, (int) n, g);
	efree(g);
}

ZEND_FUNCTION(pixman_composite_glyphs_no_mask)
{
	zend_long op, sx, sy, dx, dy, n;
	zval *s, *d, *c;
	HashTable *arr;
	ZEND_PARSE_PARAMETERS_START(10, 10)
		Z_PARAM_LONG(op)
		Z_PARAM_OBJECT_OF_CLASS(s, px_image_ce)
		Z_PARAM_OBJECT_OF_CLASS(d, px_image_ce)
		Z_PARAM_LONG(sx)
		Z_PARAM_LONG(sy)
		Z_PARAM_LONG(dx)
		Z_PARAM_LONG(dy)
		Z_PARAM_OBJECT_OF_CLASS(c, px_glyph_cache_ce)
		Z_PARAM_LONG(n)
		Z_PARAM_ARRAY_HT(arr)
	ZEND_PARSE_PARAMETERS_END();
	pixman_image_t *src = px_image_arg(s, 2);
	pixman_image_t *dest = src ? px_image_arg(d, 3) : NULL;
	px_glyph_cache_obj *o = dest ? px_glyph_cache_arg(c, 8) : NULL;
	if (!o || !op_ok(op) || !i32(sx, 4) || !i32(sy, 5) || !i32(dx, 6) || !i32(dy, 7)) RETURN_THROWS();
	pixman_glyph_t *g = glyphs_arg(o, arr, n, 10, 9);
	if (!g) RETURN_THROWS();
	pixman_composite_glyphs_no_mask((pixman_op_t) op, src, dest, (int32_t) sx, (int32_t) sy, (int32_t) dx, (int32_t) dy, o->cache, (int) n, g);
	efree(g);
}

void px_glyph_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
