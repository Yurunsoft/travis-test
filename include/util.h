#pragma once

#include <string>
#include <cstring>
#include <vector>

using namespace std;

static void split_string(const string &str, const string &pattern, vector<string> *result) {
    char *strc = new char[strlen(str.c_str()) + 1];
    strcpy(strc, str.c_str());
    char *tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL) {
        result->push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;
}

static inline vector<string> split_string(const string &str, const string &pattern) {
    vector<string> resultVec;

    split_string(str, pattern, &resultVec);

    return resultVec;
}

static void split_character_utf8(const string & word, vector<string> & characters)
{
    size_t num = word.size();
    size_t i = 0;
    char temp;
    size_t size;
    while(i < num)
    {
        size = 1;
        if(word[i] & 0x80)
        {
            temp = word[i];
            temp <<= 1;
            do{
                temp <<= 1;
                ++size;
            }while(temp & 0x80);
        }
        characters.push_back(word.substr(i, size));
        i += size;
    }
}
