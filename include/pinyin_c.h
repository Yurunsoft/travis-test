
#pragma once

#include "pinyin.h"
#include <vec.h>

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
    // 拼音数量
    int pinyin_count;
    // 带声调读音的拼音
    vec_str_t pinyin_sound;
    // 带声调读音的拼音数量
    int pinyin_sound_count;
    // 带声调读音的拼音，但声调表示为数字
    vec_str_t pinyin_sound_number;
    // 带声调读音的拼音，但声调表示为数字数量
    int pinyin_sound_number_count;
    // 转换为拼音首字母
    vec_str_t pinyin_first;
    // 转换为拼音首字母数量
    int pinyin_first_count;
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
}
