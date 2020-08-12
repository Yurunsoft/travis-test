#include "number.h"

using namespace chinese_util;

static inline string parse_integer(const string number, bool ten_min)
{

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
        result += NUMBER_MAP_BY_NUMBER[item[0]];
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
    }
    string integer_part = parse_integer(integer_str, ten_min);
    if(0 == integer_part.length())
    {
        integer_part = NUMBER_MAP_BY_NUMBER['0'];
    }
    string decimal_part = parse_decimal(decimal_part);
    return pom + integer_part + decimal_part;
}
