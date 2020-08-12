#include "php/php_chinese_util.h"

#include "php/php_dict.h"
#include "php/php_pinyin.h"
#include "php/php_st.h"
#include "php/php_pinyin_split.h"

// clang-format off
const zend_function_entry ext_functions[] = {
    PHP_FE(init_chinese_dict, arginfo_init_chinese_dict)
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
    ZEND_FE(split_pinyin_array, arginfo_split_pinyin_array)
    ZEND_FE(split_pinyin_string, arginfo_split_pinyin_string)
#ifdef WITH_SWOOLE
    ZEND_FE(swoole_split_pinyin_array, arginfo_swoole_split_pinyin_array)
    ZEND_FE(swoole_split_pinyin_string, arginfo_swoole_split_pinyin_string)
#endif
    PHP_FE_END
};
// clang-format on

extern "C" {
void init_chinese_util() {
    zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
}
