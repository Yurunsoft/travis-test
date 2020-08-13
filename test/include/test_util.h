#pragma once

#ifdef __APPLE__
#    include <mach-o/dyld.h>
#elif _WIN32
#    include <windows.h>
#else
#    include <unistd.h>
#endif

#include <string>

#include "dict.h"
#include "json.h"

using namespace std;
using namespace chinese_util;

#ifndef MAX_SIZE
#    define MAX_SIZE 1024
#endif

static string get_dir() {
#ifdef __APPLE__
    char path[1024];
    unsigned size = 1024;
    _NSGetExecutablePath(path, &size);
    path[size] = '\0';
    return path;
#elif _WIN32
    char szPath[1024] = {0};
    GetModuleFileName(NULL, szPath, sizeof(szPath) - 1);
    return szPath;
#else
    char current_absolute_path[MAX_SIZE];
    //获取当前程序绝对路径
    ssize_t cnt = readlink("/proc/self/exe", current_absolute_path, MAX_SIZE);
    if (cnt < 0 || cnt >= MAX_SIZE) {
        return nullptr;
    }
    //获取当前目录绝对路径，即去掉程序名
    ssize_t i;
    for (i = cnt - 1; i >= 0; --i) {
        if (current_absolute_path[i] == '/') {
            current_absolute_path[i + 1] = '\0';
            break;
        }
    }
    return current_absolute_path;
#endif
}

static inline Dict* get_dict() {
    Dict* dict = new Dict;
    const string dir = get_dir();
    cout << dir << endl;
    dict->LoadCharacterData(dir + "/../../data/charsData.json");
    dict->LoadPinyinData(dir + "/../../data/pinyinData.json");
    return dict;
}

template <class T>
static inline void CheckVectorString(const string excepted, vector<T>& vector) {
    CHECK_EQ(json::parse(excepted).dump(4), json(vector).dump(4));
}
