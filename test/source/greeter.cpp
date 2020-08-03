#include <dict.h>
#include <doctest/doctest.h>
#include <pinyin.h>
#include <util.h>
#include <test_util.h>
#include <json.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chinese_util;

static inline void AssertPinyinResultVector(string excepted, const PinyinResultVector *result_vector)
{
    json data = json::object();
    if(result_vector->pinyin)
    {
        data["pinyin"] = json(*result_vector->pinyin);
    }
    if(result_vector->pinyin_first)
    {
        data["pinyin_first"] = json(*result_vector->pinyin_first);
    }
    if(result_vector->pinyin_sound)
    {
        data["pinyin_sound"] = json(*result_vector->pinyin_sound);
    }
    if(result_vector->pinyin_sound_number)
    {
        data["pinyin_sound_number"] = json(*result_vector->pinyin_sound_number);
    }
    CHECK_EQ(json::parse(excepted).dump(4), data.dump(4));
}

static inline void AssertPinyinResultString(string excepted, const PinyinResultString *result_string)
{
    json data = json::object();
    if(result_string->pinyin)
    {
        data["pinyin"] = json(*result_string->pinyin);
    }
    if(result_string->pinyin_first)
    {
        data["pinyin_first"] = json(*result_string->pinyin_first);
    }
    if(result_string->pinyin_sound)
    {
        data["pinyin_sound"] = json(*result_string->pinyin_sound);
    }
    if(result_string->pinyin_sound_number)
    {
        data["pinyin_sound_number"] = json(*result_string->pinyin_sound_number);
    }
    CHECK_EQ(json::parse(excepted).dump(4), data.dump(4));
}

static inline void AssertPinyinResultArray_C(string excepted, const PinyinResultArray_C *result)
{
    json data = json::object();
    if(result->pinyin.capacity > 0)
    {
        data["pinyin"] = json::array();
        int i; vec_str_t i1;
        vec_foreach(&result->pinyin, i1, i) {
            json json_array = json::array();
            int j; char* val;
            vec_foreach(&i1, val, j) {
                json_array.push_back(val);
            }
            data["pinyin"].push_back(json_array);
        }
    }
    if(result->pinyin_first.capacity > 0)
    {
        data["pinyin_first"] = json::array();
        int i; vec_str_t i1;
        vec_foreach(&result->pinyin_first, i1, i) {
            json json_array = json::array();
            int j; char* val;
            vec_foreach(&i1, val, j) {
                json_array.push_back(val);
            }
            data["pinyin_first"].push_back(json_array);
        }
    }
    if(result->pinyin_sound.capacity > 0)
    {
        data["pinyin_sound"] = json::array();
        int i; vec_str_t i1;
        vec_foreach(&result->pinyin_sound, i1, i) {
            json json_array = json::array();
            int j; char* val;
            vec_foreach(&i1, val, j) {
                json_array.push_back(val);
            }
            data["pinyin_sound"].push_back(json_array);
        }
    }
    if(result->pinyin_sound_number.capacity > 0)
    {
        data["pinyin_sound_number"] = json::array();
        int i; vec_str_t i1;
        vec_foreach(&result->pinyin_sound_number, i1, i) {
            json json_array = json::array();
            int j; char* val;
            vec_foreach(&i1, val, j) {
                json_array.push_back(val);
            }
            data["pinyin_sound_number"].push_back(json_array);
        }
    }
    CHECK_EQ(json::parse(excepted).dump(4), data.dump(4));
}

static inline void AssertPinyinResultString_C(string excepted, const PinyinResultString_C *result)
{
    json data = json::object();
    if(result->pinyin.capacity > 0)
    {
        data["pinyin"] = json::array();
        int i; char* item;
        vec_foreach(&result->pinyin, item, i) {
            data["pinyin"].push_back(item);
        }
    }
    if(result->pinyin_first.capacity > 0)
    {
        data["pinyin_first"] = json::array();
        int i; char* item;
        vec_foreach(&result->pinyin_first, item, i) {
            data["pinyin_first"].push_back(item);
        }
    }
    if(result->pinyin_sound.capacity > 0)
    {
        data["pinyin_sound"] = json::array();
        int i; char* item;
        vec_foreach(&result->pinyin_sound, item, i) {
            data["pinyin_sound"].push_back(item);
        }
    }
    if(result->pinyin_sound_number.capacity > 0)
    {
        data["pinyin_sound_number"] = json::array();
        int i; char* item;
        vec_foreach(&result->pinyin_sound_number, item, i) {
            data["pinyin_sound_number"].push_back(item);
        }
    }
    CHECK_EQ(json::parse(excepted).dump(4), data.dump(4));
}

TEST_CASE("Pinyin") {
    Dict dict;
    string dir = get_dir();
    dict.LoadCharacterData(dir + "/../../data/charsData.json");
    dict.LoadPinyinData(dir + "/../../data/pinyinData.json");

    PinyinResultVector result_vector = Pinyin::convert(&dict, "测试的ab", ConvertMode::ALL, false);

    AssertPinyinResultVector(R"JSON({"pinyin":[["ce","shi","di","ab"],["ce","shi","de","ab"]],"pinyin_first":[["c","s","d","a"]],"pinyin_sound":[["cè","shì","dí","ab"],["cè","shì","dì","ab"],["cè","shì","de","ab"]],"pinyin_sound_number":[["ce4","shi4","di2","ab"],["ce4","shi4","di4","ab"],["ce4","shi4","de0","ab"]]})JSON", &result_vector);

    result_vector = Pinyin::convert(&dict, "测试的ab", ConvertMode::ALL, true);

    AssertPinyinResultVector(R"JSON({"pinyin":[["ce","shi","di","a","b"],["ce","shi","de","a","b"]],"pinyin_first":[["c","s","d","a","b"]],"pinyin_sound":[["cè","shì","dí","a","b"],["cè","shì","dì","a","b"],["cè","shì","de","a","b"]],"pinyin_sound_number":[["ce4","shi4","di2","a","b"],["ce4","shi4","di4","a","b"],["ce4","shi4","de0","a","b"]]})JSON", &result_vector);

    PinyinResultString result_string = Pinyin::convert(&dict, "测试的ab", ConvertMode::ALL, false, " ");
    
    AssertPinyinResultString(R"JSON({"pinyin":["ce shi di ab","ce shi de ab"],"pinyin_first":["c s d a"],"pinyin_sound":["cè shì dí ab","cè shì dì ab","cè shì de ab"],"pinyin_sound_number":["ce4 shi4 di2 ab","ce4 shi4 di4 ab","ce4 shi4 de0 ab"]})JSON", &result_string);

    result_string = Pinyin::convert(&dict, "测试的ab", ConvertMode::ALL, true, " ");
    
    AssertPinyinResultString(R"JSON({"pinyin":["ce shi di a b","ce shi de a b"],"pinyin_first":["c s d a b"],"pinyin_sound":["cè shì dí a b","cè shì dì a b","cè shì de a b"],"pinyin_sound_number":["ce4 shi4 di2 a b","ce4 shi4 di4 a b","ce4 shi4 de0 a b"]})JSON", &result_string);
}

TEST_CASE("PinyinC") {
    void* dict = create_dict();
    string dir = get_dir();
    load_character_data(dict, (dir + "/../../data/charsData.json").c_str());
    load_pinyin_data(dict, (dir + "/../../data/pinyinData.json").c_str());

    PinyinResultArray_C* result_array = new PinyinResultArray_C;
    convert_to_pinyin_array(result_array, dict, "测试的ab", ConvertMode::ALL, 0);
    AssertPinyinResultArray_C(R"JSON({"pinyin":[["ce","shi","di","ab"],["ce","shi","de","ab"]],"pinyin_first":[["c","s","d","a"]],"pinyin_sound":[["cè","shì","dí","ab"],["cè","shì","dì","ab"],["cè","shì","de","ab"]],"pinyin_sound_number":[["ce4","shi4","di2","ab"],["ce4","shi4","di4","ab"],["ce4","shi4","de0","ab"]]})JSON", result_array);
    delete result_array;


    PinyinResultString_C* result_string = new PinyinResultString_C;
    convert_to_pinyin_string(result_string, dict, "测试的ab", ConvertMode::ALL, 0, " ");
    AssertPinyinResultString_C(R"JSON({"pinyin":["ce shi di ab","ce shi de ab"],"pinyin_first":["c s d a"],"pinyin_sound":["cè shì dí ab","cè shì dì ab","cè shì de ab"],"pinyin_sound_number":["ce4 shi4 di2 ab","ce4 shi4 di4 ab","ce4 shi4 de0 ab"]})JSON", result_string);
    delete result_string;

    close_dict(dict);

}
