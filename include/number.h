#pragma once

#include <array>
#include <cmath>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "util.h"

using namespace std;

namespace chinese_util {
    unordered_map<char, string> NUMBER_MAP_BY_NUMBER = {
        {'0', "零"},
        {'1', "一"},
        {'2', "二"},
        {'3', "三"},
        {'4', "四"},
        {'5', "五"},
        {'6', "六"},
        {'7', "七"},
        {'8', "八"},
        {'9', "九"},
        {'-', "负"},
        {'.', "点"}};
    unordered_map<string, char> NUMBER_MAP_BY_CHARACTER = {
        {"零", '0'},
        {"一", '1'},
        {"二", '2'},
        {"三", '3'},
        {"四", '4'},
        {"五", '5'},
        {"六", '6'},
        {"七", '7'},
        {"八", '8'},
        {"九", '9'},
        {"负", '-'},
        {"点", '.'}};
    array<string, 7> UNIT_MAP = {
        "十",
        "百",
        "千",
        "万",
        "亿",
        "兆",
        "京"};

    class Number {
        public:
        // 中文口语化数字转数字
        template <typename T>
        static T ToNumber(const string text) {
            vector<string> characters;
            split_character_utf8(text, characters);
            T number = 0, part_number = 0, last_num = 0;
            short pom = 1;
            bool is_decimal = false;
            string decimal;
            for (size_t i = 0; i < characters.size(); ++i) {
                string character = characters[i];
                if (0 == i && NUMBER_MAP_BY_NUMBER['-'] == character) {
                    pom = -1;
                    continue;
                }
                if (NUMBER_MAP_BY_NUMBER['.'] == character) {
                    is_decimal = true;
                    continue;
                }
                if (stl_isset(NUMBER_MAP_BY_CHARACTER, character)) {
                    if (is_decimal) {
                        decimal.append(1, NUMBER_MAP_BY_CHARACTER[character]);
                    } else {
                        last_num = NUMBER_MAP_BY_CHARACTER[character] - '0';
                    }
                } else {
                    auto key = array_search(UNIT_MAP, character);
                    if (-1 == key) {
                        throw sprintf("%s is not a valied chinese number text", character.c_str());
                    }

                    if (0 == key && 0 == last_num) {
                        last_num = 1;
                    }

                    T t_number;
                    if (key >= 3) {
                        part_number += last_num;
                        number += part_number * pow(10, ((key - 3) * 4) + 4);
                        part_number = 0;
                    } else {
                        part_number += last_num * pow(10, key + 1);
                    }

                    last_num = 0;
                }
            }
            double integer = (number + part_number + last_num) * pom;
            if (is_decimal) {
                integer += atof(decimal.c_str()) / pow(10, decimal.length());
            }
            return (T)integer;
        }
        // 数字转为中文口语化数字
        static string ToChinese(const string text, bool ten_min = false);
        // 数字转为中文口语化数字
        static string ToChinese(const char* text, bool ten_min = false);
        // 数字转为中文口语化数字
        template <typename T>
        static string ToChinese(const T text, bool ten_min = false) {
            return ToChinese(to_string(text), ten_min);
        }
    };
}  // namespace chinese_util
