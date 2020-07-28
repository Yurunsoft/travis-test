#pragma once

#include <string>
#include <vector>
#include <dict.h>

using namespace std;

namespace chinese_util {

    // 转换模式
    enum ConvertMode{
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
    };

    // 拼音结果
    struct PinyinResult {
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
            static PinyinResult convert(Dict *dict, const string & text, ConvertMode mode, const string & word_split, bool split_not_pinyin_char = true);
    };

}
