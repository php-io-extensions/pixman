#ifndef PHP_PIXMAN_H
#define PHP_PIXMAN_H

extern zend_module_entry pixman_module_entry;
#define phpext_pixman_ptr &pixman_module_entry

#define PHP_PIXMAN_VERSION "0.11.0"

/* pixman tag pixman-0.46.4. A newer library lands only by replacing lib/pixman/ from a published tag. */
#define PHP_PIXMAN_UPSTREAM_COMMIT "9cc163c9da0fb4da430641715313d95a6ec466d9"

#if defined(ZTS) && defined(COMPILE_DL_PIXMAN)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif
