#include <dict.h>
#include <doctest/doctest.h>
#include <pinyin.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chinese_util;

TEST_CASE("Pinyin") {
    Dict dict;
    dict.LoadCharacterData("../../data/charsData.json");
    dict.LoadPinyinData("../../data/pinyinData.json");

    PinyinResult result = Pinyin::convert(&dict, "测试的", ConvertMode::PINYIN, " ");

    // CHECK_EQ(result, result);
    // std::vector<int> except_pinyin = {"ce shi "};
    // must be iterable—— std::vector<> would work as well

    // printf("result:%s\n", (*result.pinyin)[0].c_str());

    std::cout << "result:" << result.pinyin->size() << std::endl;
    std::cout << (*result.pinyin)[0].c_str() << std::endl;
    std::cout << (*result.pinyin)[1].c_str() << std::endl;

    CHECK(false);
}
