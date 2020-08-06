#pragma once
#include "php.h"
#include "php/php_dict.h"
#ifdef WITH_SWOOLE
#    include <coroutine_cxx_api.h>
using namespace swoole;
#endif
#include "dict.h"
#include "pinyin.h"

using namespace std;
using namespace chinese_util;

ZEND_BEGIN_ARG_INFO_EX(arginfo_convert_to_pinyin_array, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_ARG_INFO(0, mode)
ZEND_ARG_INFO(0, split_not_pinyin_char)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_convert_to_pinyin_string, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_ARG_INFO(0, mode)
ZEND_ARG_INFO(0, split_not_pinyin_char)
ZEND_ARG_INFO(0, word_split)
ZEND_END_ARG_INFO()

#ifdef WITH_SWOOLE
ZEND_BEGIN_ARG_INFO_EX(arginfo_swoole_convert_to_pinyin_array, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_ARG_INFO(0, mode)
ZEND_ARG_INFO(0, split_not_pinyin_char)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_swoole_convert_to_pinyin_string, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_ARG_INFO(0, mode)
ZEND_ARG_INFO(0, split_not_pinyin_char)
ZEND_ARG_INFO(0, word_split)
ZEND_END_ARG_INFO()
#endif

PHP_FUNCTION(convert_to_pinyin_array);
PHP_FUNCTION(convert_to_pinyin_string);
#ifdef WITH_SWOOLE
PHP_FUNCTION(swoole_convert_to_pinyin_array);
PHP_FUNCTION(swoole_convert_to_pinyin_string);
#endif
