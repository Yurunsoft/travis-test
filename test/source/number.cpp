#include <dict.h>
#include <doctest/doctest.h>
#include <json.h>
#include <number.h>
#include <test_util.h>
#include <util.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chinese_util;

TEST_CASE("ToNumber") {
    CHECK_EQ(5, Number::ToNumber<long>("五"));
    CHECK_EQ(12, Number::ToNumber<long>("一十二"));
    CHECK_EQ(12, Number::ToNumber<long>("十二"));
    CHECK_EQ(-5, Number::ToNumber<long>("负五"));
    CHECK_EQ(3.1415, Number::ToNumber<double>("三点一四一五"));
}

TEST_CASE("ToChinese") {
    CHECK_EQ("三点一四一五", Number::ToChinese(3.1415));
}
