
#pragma once

#include <vec.h>

#include "pinyin.h"

#ifdef WITH_SWOOLE
#    include <coroutine_cxx_api.h>
#endif

typedef vec_t(vec_str_t) vec_vec_str_t;

// 转换模式
typedef enum {
    // 转换为全拼
    PINYIN = 1,
    // 转换为带声调读音的拼音
    PINYIN_SOUND = 2,
    // 转换为带声调读音的拼音，但声调表示为数字
    PINYIN_SOUND_NUMBER = 4,
    // 转换为拼音首字母
    PINYIN_FIRST = 8,
    // 转换为上面支持的所有类型
    ALL = 15,
} ConvertMode;

// 拼音结果
typedef struct {
    // 拼音
    vec_str_t pinyin;
    // 带声调读音的拼音
    vec_str_t pinyin_sound;
    // 带声调读音的拼音，但声调表示为数字
    vec_str_t pinyin_sound_number;
    // 转换为拼音首字母
    vec_str_t pinyin_first;
} PinyinResultString_C;

// 拼音结果
typedef struct {
    // 拼音
    vec_vec_str_t pinyin;
    // 带声调读音的拼音
    vec_vec_str_t pinyin_sound;
    // 带声调读音的拼音，但声调表示为数字
    vec_vec_str_t pinyin_sound_number;
    // 转换为拼音首字母
    vec_vec_str_t pinyin_first;
} PinyinResultArray_C;

extern "C" {
// 转换汉字到拼音数组
void convert_to_pinyin_array(PinyinResultArray_C* result, void* dict, const char* text, ConvertMode mode, short split_not_pinyin_char);

// 转换汉字到拼音字符串数组
void convert_to_pinyin_string(PinyinResultString_C* result, void* dict, const char* text, ConvertMode mode, short split_not_pinyin_char, const char* word_split);

// 释放拼音数组结果
void free_pinyin_result_array(PinyinResultArray_C* result);

// 释放字符串数组结果
void free_pinyin_result_string(PinyinResultString_C* result);

#ifdef WITH_SWOOLE
// 转换汉字到拼音数组
void swoole_convert_to_pinyin_array(PinyinResultArray_C* result, void* dict, const char* text, ConvertMode mode, short split_not_pinyin_char);
#endif
}
