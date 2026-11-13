/*
 * The binding's shared machinery: value-struct tables and their one converter,
 * the handle objects (images, regions, glyph caches), and argument checks.
 */

#ifndef PIXMAN_RUNTIME_H
#define PIXMAN_RUNTIME_H

#include "php.h"
#include "pixman.h"

/* ---- value structs ---------------------------------------------------- */

typedef enum {
	PX_I16, PX_U16, PX_I32, PX_U32, PX_F64, PX_BOOL,
	PX_STRUCT,     /* nested value struct: .sub */
	PX_I32_ARR,    /* int32_t[n] */
	PX_U32_ARR,    /* uint32_t[n] */
	PX_F64_ARR,    /* double[n] */
	PX_I32_MAT3,   /* int32_t[3][3] */
	PX_F64_MAT3,   /* double[3][3] */
	PX_BYTES,      /* uint8_t[n] as a string of exactly n bytes */
	PX_PTR         /* const void * as an int */
} px_kind;

typedef struct px_struct px_struct;

typedef struct {
	const char *name;
	px_kind kind;
	size_t offset;
	uint32_t n;
	const px_struct *sub;
} px_field;

struct px_struct {
	const char *name;
	size_t size;
	const px_field *fields;
	uint32_t count;
	zend_class_entry **ce;
};

extern const px_struct px_color, px_point_fixed, px_line_fixed, px_vector, px_transform,
	px_f_vector, px_f_transform, px_box16, px_box32, px_box64f, px_rectangle16,
	px_gradient_stop, px_indexed, px_glyph, px_edge, px_trapezoid, px_triangle,
	px_span_fix, px_trap;

/* Fills `out` from the object's properties; false (ValueError thrown) on a bad value. */
bool px_struct_read(const px_struct *def, zend_object *obj, void *out);
/* Writes `in` into the object's properties (nested objects are written in place). */
void px_struct_write(const px_struct *def, zend_object *obj, const void *in);
/* A new instance holding `in`. */
void px_struct_new(const px_struct *def, const void *in, zval *out);
/* The constructor every value-struct class shares: argument i is field i. */
void px_struct_construct(const px_struct *def, INTERNAL_FUNCTION_PARAMETERS);
/* `count` elements of `arr` (each an instance of def's class) into `out` (count * def->size bytes). */
bool px_struct_array_read(const px_struct *def, HashTable *arr, zend_long count, void *out, uint32_t arg_num);
/* count may not be negative or exceed the array: ValueError naming the argument. */
bool px_check_count(zend_long count, HashTable *arr, uint32_t arg_num);

/* ---- handle objects --------------------------------------------------- */

typedef struct {
	pixman_image_t *image; /* NULL once released */
	zend_object std;
} px_image_obj;

typedef struct {
	pixman_region16_t region;
	bool initialised;
	zend_object std;
} px_region16_obj;

typedef struct {
	pixman_region32_t region;
	bool initialised;
	zend_object std;
} px_region32_obj;

typedef struct {
	pixman_region64f_t region;
	bool initialised;
	zend_object std;
} px_region64f_obj;

typedef struct {
	pixman_glyph_cache_t *cache; /* NULL once destroyed */
	zend_long frozen;            /* freezes not yet thawed: pixman refuses to destroy a frozen cache */
	HashTable glyphs;            /* glyph handle -> [font_key, glyph_key] */
	zend_object std;
} px_glyph_cache_obj;

extern zend_class_entry *px_image_ce, *px_region16_ce, *px_region32_ce, *px_region64f_ce, *px_glyph_cache_ce;

static inline px_image_obj *px_image_from(zend_object *o) { return (px_image_obj *) ((char *) o - XtOffsetOf(px_image_obj, std)); }
static inline px_region16_obj *px_region16_from(zend_object *o) { return (px_region16_obj *) ((char *) o - XtOffsetOf(px_region16_obj, std)); }
static inline px_region32_obj *px_region32_from(zend_object *o) { return (px_region32_obj *) ((char *) o - XtOffsetOf(px_region32_obj, std)); }
static inline px_region64f_obj *px_region64f_from(zend_object *o) { return (px_region64f_obj *) ((char *) o - XtOffsetOf(px_region64f_obj, std)); }
static inline px_glyph_cache_obj *px_glyph_cache_from(zend_object *o) { return (px_glyph_cache_obj *) ((char *) o - XtOffsetOf(px_glyph_cache_obj, std)); }

/* The live pixman image of an argument, or NULL with ValueError thrown (released). A null zval gives NULL without error. */
pixman_image_t *px_image_arg(zval *zv, uint32_t arg_num);
/* A new pixman_image object taking over one reference to `image` (NULL image: null). */
void px_image_wrap(pixman_image_t *image, zval *out);
/* Every image the binding creates goes through here: installs the binding's destroy function. */
pixman_image_t *px_image_adopt(pixman_image_t *image, void *bits);

/* Initialised regions only: NULL with ValueError thrown otherwise. */
pixman_region16_t *px_region16_arg(zval *zv, uint32_t arg_num);
pixman_region32_t *px_region32_arg(zval *zv, uint32_t arg_num);
pixman_region64f_t *px_region64f_arg(zval *zv, uint32_t arg_num);
/* The storage of a region an init function is about to initialise: released first if it was initialised. */
pixman_region16_t *px_region16_for_init(zval *zv);
pixman_region32_t *px_region32_for_init(zval *zv);
pixman_region64f_t *px_region64f_for_init(zval *zv);

/* A live glyph cache, or NULL with ValueError thrown. */
px_glyph_cache_obj *px_glyph_cache_arg(zval *zv, uint32_t arg_num);
/* Thaws what is still frozen, then destroys the cache. */
void px_glyph_cache_release(px_glyph_cache_obj *o);
/* Glyphs checked against the cache (each handle still looks up to itself); out holds count entries. */
bool px_glyphs_read(px_glyph_cache_obj *cache, HashTable *arr, zend_long count, pixman_glyph_t *out, uint32_t arg_num);
void px_glyph_record(px_glyph_cache_obj *cache, const void *glyph, zend_long font_key, zend_long glyph_key);
void px_glyph_forget(px_glyph_cache_obj *cache, const void *glyph);

/* ---- image records: what the binding keeps per pixman image ------------ */

typedef struct {
	void *bits;                 /* the copy of caller bits, or NULL */
	pixman_indexed_t *indexed;  /* the copy given to pixman_image_set_indexed */
	zval destroy_fn, destroy_data, read_fn, write_fn;
	pixman_image_t *image;
} px_image_rec;

px_image_rec *px_image_rec_of(pixman_image_t *image);
void px_accessors_set(pixman_image_t *image, px_image_rec *rec);

/* ---- argument checks -------------------------------------------------- */

bool px_check_range(zend_long v, zend_long min, zend_long max, uint32_t arg_num);

void px_runtime_minit(int module_number);
void px_runtime_rshutdown(void);

#endif
