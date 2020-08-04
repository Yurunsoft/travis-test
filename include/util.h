#pragma once

#include <cstring>
#include <string>
#include <vector>

using namespace std;

static void split_string(const string str, const string pattern, vector<string> *result) {
    char *strc = new char[str.length() + 1];
    strcpy(strc, str.c_str());
    const char *patternChars = pattern.c_str();
    char *tmpStr = strtok(strc, patternChars);
    while (tmpStr != NULL) {
        result->push_back(string(tmpStr));
        tmpStr = strtok(NULL, patternChars);
    }

    delete[] strc;
}

static inline vector<string> split_string(const string str, const string pattern) {
    vector<string> resultVec;

    split_string(str, pattern, &resultVec);

    return resultVec;
}

static void split_character_utf8(const string word, vector<string> &characters) {
    size_t num = word.size();
    size_t i = 0;
    char temp;
    size_t size;
    while (i < num) {
        size = 1;
        if (word[i] & 0x80) {
            temp = word[i] << 1;
            do {
                temp <<= 1;
                ++size;
            } while (temp & 0x80);
        }
        characters.push_back(word.substr(i, size));
        i += size;
    }
}

template <class T>
static std::string join(T &val, const std::string delim) {
    std::string str;
    typename T::iterator it;
    const typename T::iterator itlast = val.end() - 1;
    for (it = val.begin(); it != val.end(); it++) {
        str += *it;
        if (it != itlast) {
            str += delim;
        }
    }
    return str;
}

static string operator+(string &content, int number) {
    string temp;
    char t = 0;
    while (true) {
        t = number % 10 + '0';
        temp += t;
        number /= 10;
        if (0 == number) {
            return content + temp;
        }
    }
}
//由于+=会调用+号，所以 += 必须写在 + 号重载后面
static string &operator+=(string &content, int number) {
    return content = content + number;
}

// 将 string 转为 const char*
static inline const char *str_cc(const string str) {
    char *c = new char[str.length() + 1];
    strcpy(c, str.c_str());
    return c;
}

// 将 string 转为 char*
static inline char *str_c(const string str) {
    char *c = new char[str.length() + 1];
    strcpy(c, str.c_str());
    return c;
}

// 将 string 转为 char*
static inline void str_c(char *&result, const string str) {
    result = new char[str.length() + 1];
    strcpy(result, str.c_str());
}
