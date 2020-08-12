#include "number.h"

using namespace chinese_util;

static inline string parse_integer(const string number, bool ten_min)
{
    const auto number_length = number.length();
    // 同 % 4
    const auto first_items = number_length & 3;
    string left_str = number.substr(first_items);
    vector<string> split4;
    if(left_str.length() > 0)
    {
        str_split(left_str, 4, split4);
    }
    if(first_items > 0)
    {
        split4.insert(split4.begin(), number.substr(0, first_items));
    }
    const auto split4_count = split4.size();

    short unit_index = ((number_length - 1) / 4) >> 0;
    if(0 == unit_index)
    {
        unit_index = -1;
    }
    else
    {
        unit_index += 2;
    }

    string result;
    for(size_t i = 0; i < split4_count; ++i)
    {
        const auto item = split4[i];
        const auto index = unit_index - i;
        const auto length = item.length();
        string item_result;
        bool has0 = false;
        for(size_t j = 0; j < length; ++j)
        {
            if('0' == item[j])
            {
                has0 = true;
            }
            else
            {
                if(has0)
                {
                    item_result += NUMBER_MAP_BY_NUMBER['0'];
                    has0 = false;
                }
                if(!(ten_min && 2 == length && 0 == j && '1' == item[j]))
                {
                    item_result += NUMBER_MAP_BY_NUMBER[item[j]];
                }
                if('0' != item[j])
                {
                    const auto unit_index = length - j - 2;
                    item_result += (unit_index < UNIT_MAP.size() ? UNIT_MAP[unit_index] : "");
                }
            }
        }
        if(0 != item_result.length())
        {
            result += item_result + ((i != split4_count - 1 && index < UNIT_MAP.size()) ? UNIT_MAP[index] : "");
        }
    }
    return result;
}

static inline string parse_decimal(const string number)
{
    if(0 == number.length())
    {
        return "";
    }
    string result = NUMBER_MAP_BY_NUMBER['.'];
    for(auto item : number)
    {
        result += NUMBER_MAP_BY_NUMBER[item];
    }
    return result;
}

string Number::ToChinese(const string text, bool ten_min) {
    if(!is_digital(text))
    {
        throw sprintf("%s is not a valied number", text.c_str());
    }
    vector<string> split_result;
    split_string(text, ".", split_result);
    string integer_str, decimal_str;
    long tmp_integer;
    size_t integer, decimal;
    string pom;
    if(split_result.size() > 0)
    {
        integer_str = split_result[0];
        std::istringstream iss(integer_str);
        iss >> tmp_integer;
    }
    if(split_result.size() > 1)
    {
        decimal_str = split_result[1];
        std::istringstream iss(decimal_str);
        iss >> decimal;
    }
    if(tmp_integer < 0)
    {
        pom = NUMBER_MAP_BY_NUMBER['-'];
        integer = abs(tmp_integer);
        integer_str = integer_str.substr(1);
    }
    string integer_part = parse_integer(integer_str, ten_min);
    if(0 == integer_part.length())
    {
        integer_part = NUMBER_MAP_BY_NUMBER['0'];
    }
    string decimal_part = parse_decimal(decimal_str);
    return pom + integer_part + decimal_part;
}

string Number::ToChinese(const char* text, bool ten_min) {
    return ToChinese(string(text), ten_min);
}