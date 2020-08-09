#include "php/php_dict.h"

void close_chinese_dict()
{
    if(yurun_chinese_globals.dict)
    {
        delete yurun_chinese_globals.dict;
        yurun_chinese_globals.dict = nullptr;
    }
}

PHP_FUNCTION(init_chinese_dict) {
    char *chars_data_file, *pinyin_data_file;
    size_t chars_data_file_len, pinyin_data_file_len;
    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_STRING(chars_data_file, chars_data_file_len)
    Z_PARAM_STRING(pinyin_data_file, pinyin_data_file_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);
    yurun_chinese_globals.dict = new Dict;
    yurun_chinese_globals.dict->LoadCharacterData(chars_data_file);
    yurun_chinese_globals.dict->LoadPinyinData(pinyin_data_file);
}
