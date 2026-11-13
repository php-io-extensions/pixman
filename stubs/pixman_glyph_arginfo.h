/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 23bce488848d4163a2d3d2a23fe59784cd216db0 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_pixman_glyph_cache_create, 0, 0, pixman_glyph_cache, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_glyph_cache_destroy, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, cache, pixman_glyph_cache, 0)
ZEND_END_ARG_INFO()

#define arginfo_pixman_glyph_cache_freeze arginfo_pixman_glyph_cache_destroy

#define arginfo_pixman_glyph_cache_thaw arginfo_pixman_glyph_cache_destroy

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_glyph_cache_lookup, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, cache, pixman_glyph_cache, 0)
	ZEND_ARG_TYPE_INFO(0, font_key, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, glyph_key, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_glyph_cache_insert, 0, 6, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, cache, pixman_glyph_cache, 0)
	ZEND_ARG_TYPE_INFO(0, font_key, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, glyph_key, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, origin_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, origin_y, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, glyph_image, pixman_image, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_glyph_cache_remove, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, cache, pixman_glyph_cache, 0)
	ZEND_ARG_TYPE_INFO(0, font_key, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, glyph_key, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_glyph_get_extents, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, cache, pixman_glyph_cache, 0)
	ZEND_ARG_TYPE_INFO(0, n_glyphs, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, glyphs, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, extents, pixman_box32, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_glyph_get_mask_format, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, cache, pixman_glyph_cache, 0)
	ZEND_ARG_TYPE_INFO(0, n_glyphs, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, glyphs, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_composite_glyphs, 0, 15, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, src, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, dest, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, mask_format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mask_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mask_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dest_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dest_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, cache, pixman_glyph_cache, 0)
	ZEND_ARG_TYPE_INFO(0, n_glyphs, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, glyphs, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_composite_glyphs_no_mask, 0, 10, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, src, pixman_image, 0)
	ZEND_ARG_OBJ_INFO(0, dest, pixman_image, 0)
	ZEND_ARG_TYPE_INFO(0, src_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src_y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dest_x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dest_y, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, cache, pixman_glyph_cache, 0)
	ZEND_ARG_TYPE_INFO(0, n_glyphs, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, glyphs, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(pixman_glyph_cache_create);
ZEND_FUNCTION(pixman_glyph_cache_destroy);
ZEND_FUNCTION(pixman_glyph_cache_freeze);
ZEND_FUNCTION(pixman_glyph_cache_thaw);
ZEND_FUNCTION(pixman_glyph_cache_lookup);
ZEND_FUNCTION(pixman_glyph_cache_insert);
ZEND_FUNCTION(pixman_glyph_cache_remove);
ZEND_FUNCTION(pixman_glyph_get_extents);
ZEND_FUNCTION(pixman_glyph_get_mask_format);
ZEND_FUNCTION(pixman_composite_glyphs);
ZEND_FUNCTION(pixman_composite_glyphs_no_mask);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(pixman_glyph_cache_create, arginfo_pixman_glyph_cache_create)
	ZEND_FE(pixman_glyph_cache_destroy, arginfo_pixman_glyph_cache_destroy)
	ZEND_FE(pixman_glyph_cache_freeze, arginfo_pixman_glyph_cache_freeze)
	ZEND_FE(pixman_glyph_cache_thaw, arginfo_pixman_glyph_cache_thaw)
	ZEND_FE(pixman_glyph_cache_lookup, arginfo_pixman_glyph_cache_lookup)
	ZEND_FE(pixman_glyph_cache_insert, arginfo_pixman_glyph_cache_insert)
	ZEND_FE(pixman_glyph_cache_remove, arginfo_pixman_glyph_cache_remove)
	ZEND_FE(pixman_glyph_get_extents, arginfo_pixman_glyph_get_extents)
	ZEND_FE(pixman_glyph_get_mask_format, arginfo_pixman_glyph_get_mask_format)
	ZEND_FE(pixman_composite_glyphs, arginfo_pixman_composite_glyphs)
	ZEND_FE(pixman_composite_glyphs_no_mask, arginfo_pixman_composite_glyphs_no_mask)
	ZEND_FE_END
};
