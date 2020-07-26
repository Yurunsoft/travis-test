
#pragma once
#include <string>
#include <vector>

using namespace std;

void split_string(const string &str, const string &pattern, vector<string> *result) {
    char *strc = new char[strlen(str.c_str()) + 1];
    strcpy(strc, str.c_str());
    char *tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL) {
        result->push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;
}

vector<string> split_string(const string &str, const string &pattern) {
    vector<string> resultVec;

    split_string(str, pattern, &resultVec);

    return resultVec;
}
