#pragma once

#include <dict.h>

#include <iostream>
#include <string>
#include <vector>

#include "pinyin_c.h"

using namespace std;

namespace chinese_util {

    // 拼音结果
    class PinyinResultVector {
        public:
        ~PinyinResultVector() {
            if (pinyin) {
                delete pinyin;
                pinyin = nullptr;
            }
            if (pinyin_sound) {
                delete pinyin_sound;
                pinyin_sound = nullptr;
            }
            if (pinyin_sound_number) {
                delete pinyin_sound_number;
                pinyin_sound_number = nullptr;
            }
            if (pinyin_first) {
                delete pinyin_first;
                pinyin_first = nullptr;
            }
        };
        // 拼音
        vector<vector<string>> *pinyin = nullptr;
        // 带声调读音的拼音
        vector<vector<string>> *pinyin_sound = nullptr;
        // 带声调读音的拼音，但声调表示为数字
        vector<vector<string>> *pinyin_sound_number = nullptr;
        // 转换为拼音首字母
        vector<vector<string>> *pinyin_first = nullptr;
    };

    // 拼音结果
    class PinyinResultString {
        public:
        ~PinyinResultString() {
            if (pinyin) {
                delete pinyin;
                pinyin = nullptr;
            }
            if (pinyin_sound) {
                delete pinyin_sound;
                pinyin_sound = nullptr;
            }
            if (pinyin_sound_number) {
                delete pinyin_sound_number;
                pinyin_sound_number = nullptr;
            }
            if (pinyin_first) {
                delete pinyin_first;
                pinyin_first = nullptr;
            }
        };
        // 拼音
        vector<string> *pinyin = nullptr;
        // 带声调读音的拼音
        vector<string> *pinyin_sound = nullptr;
        // 带声调读音的拼音，但声调表示为数字
        vector<string> *pinyin_sound_number = nullptr;
        // 转换为拼音首字母
        vector<string> *pinyin_first = nullptr;
    };

    // 拼音处理类
    class Pinyin {
        public:
        // 把字符串转为拼音结果
        static PinyinResultString *convert(Dict *dict, const string text, ConvertMode mode, bool split_not_pinyin_char, const string word_split);
        static PinyinResultVector *convert(Dict *dict, const string text, ConvertMode mode, bool split_not_pinyin_char);
    };

}  // namespace chinese_util
