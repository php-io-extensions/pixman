/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: cb1e7e81a0297ffec1001e745d45eb517fd11cbc */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_version, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_pixman_version_string, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(pixman_version);
ZEND_FUNCTION(pixman_version_string);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(pixman_version, arginfo_pixman_version)
	ZEND_FE(pixman_version_string, arginfo_pixman_version_string)
	ZEND_FE_END
};
