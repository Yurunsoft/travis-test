#pragma once
#include "php.h"
#include "php/php_dict.h"
#include "php_chinese_util.h"
#ifdef WITH_SWOOLE
#    include <coroutine_cxx_api.h>
using namespace swoole;
#endif
#include "dict.h"
#include "pinyin_split.h"

using namespace std;
using namespace chinese_util;

ZEND_BEGIN_ARG_INFO_EX(arginfo_split_pinyin_array, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_split_pinyin_string, 0, 0, 2)
ZEND_ARG_INFO(0, text)
ZEND_ARG_INFO(0, word_split)
ZEND_END_ARG_INFO()

#ifdef WITH_SWOOLE
ZEND_BEGIN_ARG_INFO_EX(arginfo_swoole_split_pinyin_array, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_swoole_split_pinyin_string, 0, 0, 2)
ZEND_ARG_INFO(0, text)
ZEND_ARG_INFO(0, word_split)
ZEND_END_ARG_INFO()
#endif

PHP_FUNCTION(split_pinyin_array);
PHP_FUNCTION(split_pinyin_string);
#ifdef WITH_SWOOLE
PHP_FUNCTION(swoole_split_pinyin_array);
PHP_FUNCTION(swoole_split_pinyin_string);
#endif
