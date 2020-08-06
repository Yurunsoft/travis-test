#include "php/php_chinese_util.h"

#include "php/php_dict.h"
#include "php/php_pinyin.h"
#include "php/php_st.h"

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(yurun_chinese) {
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(yurun_chinese) {
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(yurun_chinese) {
}
/* }}} */

static const zend_function_entry ext_functions[] = {
    ZEND_FE(init_chinese_dict, arginfo_init_chinese_dict)
        ZEND_FE(convert_to_simplified, arginfo_convert_to_simplified)
            ZEND_FE(convert_to_traditional, arginfo_convert_to_traditional)
#ifdef WITH_SWOOLE
                ZEND_FE(swoole_convert_to_simplified, arginfo_swoole_convert_to_simplified)
                    ZEND_FE(swoole_convert_to_traditional, arginfo_swoole_convert_to_traditional)
#endif
                        ZEND_FE(convert_to_pinyin_array, arginfo_convert_to_pinyin_array)
                            ZEND_FE(convert_to_pinyin_string, arginfo_convert_to_pinyin_string)
#ifdef WITH_SWOOLE
                                ZEND_FE(swoole_convert_to_pinyin_array, arginfo_swoole_convert_to_pinyin_array)
                                    ZEND_FE(swoole_convert_to_pinyin_string, arginfo_swoole_convert_to_pinyin_string)
#endif
                                        ZEND_FE_END};

zend_module_entry yurun_chinese_module_entry = {
    STANDARD_MODULE_HEADER,
    "yurun_chinese",
    ext_functions,
    PHP_MINIT(yurun_chinese),
    PHP_MSHUTDOWN(yurun_chinese),
    NULL,
    NULL,
    PHP_MINFO(yurun_chinese),
    "",
    STANDARD_MODULE_PROPERTIES};
extern "C" {
void init_chinese_util() {
    zend_register_module_ex(&yurun_chinese_module_entry);
}
}
