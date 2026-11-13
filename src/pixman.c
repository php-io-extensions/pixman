/*
 * pixman: 1:1 bindings of pixman 0.46.4. The library is compiled into this
 * extension. Function, struct and constant names stay the C names.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_pixman.h"

#include "ext/standard/info.h"

#include "pixman.h"
#include "runtime.h"
#include "../stubs/pixman_core_arginfo.h"

void px_transform_minit(void);
void px_region16_minit(void);
void px_region32_minit(void);
void px_region64f_minit(void);
void px_image_minit(void);
void px_glyph_minit(void);
void px_trap_minit(void);

ZEND_FUNCTION(pixman_version)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(pixman_version());
}

ZEND_FUNCTION(pixman_version_string)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_STRING(pixman_version_string());
}

static PHP_MINIT_FUNCTION(pixman)
{
#if defined(ZTS) && defined(COMPILE_DL_PIXMAN)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	px_runtime_minit(module_number);
	px_transform_minit();
	px_region16_minit();
	px_region32_minit();
	px_region64f_minit();
	px_image_minit();
	px_glyph_minit();
	px_trap_minit();
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(pixman)
{
	px_runtime_rshutdown();
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(pixman)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "pixman support", "enabled");
	php_info_print_table_row(2, "Version", PHP_PIXMAN_VERSION);
	php_info_print_table_row(2, "pixman version", pixman_version_string());
	php_info_print_table_row(2, "pixman commit", PHP_PIXMAN_UPSTREAM_COMMIT);
	php_info_print_table_end();
}

zend_module_entry pixman_module_entry = {
	STANDARD_MODULE_HEADER,
	"pixman",
	ext_functions,
	PHP_MINIT(pixman),
	NULL,
	NULL,
	PHP_RSHUTDOWN(pixman),
	PHP_MINFO(pixman),
	PHP_PIXMAN_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PIXMAN
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(pixman)
#endif
