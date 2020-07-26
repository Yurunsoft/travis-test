#include <dict.h>
#include <doctest/doctest.h>

#include <string>

using namespace chinese_util;

TEST_CASE("Pinyin") {
    Dict dict;
    dict.LoadCharacterData("../../data/charsData.json");
    dict.LoadPinyinData("../../data/pinyinData.json");

    CHECK(true);
}
