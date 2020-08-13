#pragma once
#include "php.h"
#include "php/php_dict.h"
#include "php_chinese_util.h"
#ifdef WITH_SWOOLE
#    include <coroutine_cxx_api.h>
using namespace swoole;
#endif
#include "dict.h"
#include "money.h"

using namespace std;
using namespace chinese_util;

ZEND_BEGIN_ARG_INFO_EX(arginfo_convert_chinese_to_money, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_convert_money_to_chinese, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

#ifdef WITH_SWOOLE
ZEND_BEGIN_ARG_INFO_EX(arginfo_swoole_convert_chinese_to_money, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_swoole_convert_money_to_chinese, 0, 0, 1)
ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()
#endif

PHP_FUNCTION(convert_chinese_to_money);
PHP_FUNCTION(convert_money_to_chinese);
#ifdef WITH_SWOOLE
PHP_FUNCTION(swoole_convert_chinese_to_money);
PHP_FUNCTION(swoole_convert_money_to_chinese);
#endif
