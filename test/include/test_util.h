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

#ifndef MAX_PATH
#    define MAX_PATH 1024
#endif

static string get_dir() {
    char current_absolute_path[MAX_PATH];
#ifdef __APPLE__
    uint32_t cnt = 0;
    int ret = _NSGetExecutablePath(current_absolute_path, &cnt);
    if (cnt == 0) {
        throw "_NSGetExecutablePath failed to give the buffer size";
    }
    ret = _NSGetExecutablePath(current_absolute_path, &cnt);
    if (ret != 0) {
        throw "_NSGetExecutablePath returned" + ret;
    }
#elif _WIN32
    ssize_t cnt = GetModuleFileName(NULL, current_absolute_path, sizeof(current_absolute_path) - 1);
#else
    //获取当前程序绝对路径
    ssize_t cnt = readlink("/proc/self/exe", current_absolute_path, MAX_PATH);
#endif
    if (cnt < 0 || cnt >= MAX_PATH) {
        return nullptr;
    }
    //获取当前目录绝对路径，即去掉程序名
    for (ssize_t i = cnt - 1; i >= 0; --i) {
#ifdef _WIN32
        if (current_absolute_path[i] == '\\') {
#else
        if (current_absolute_path[i] == '/') {
#endif
            current_absolute_path[i + 1] = '\0';
            break;
        }
    }
    return current_absolute_path;
}

static inline Dict* get_dict() {
    Dict* dict = new Dict;
    const string dir = get_dir();
    dict->LoadCharacterData(dir + "/../../data/charsData.json");
    dict->LoadPinyinData(dir + "/../../data/pinyinData.json");
    return dict;
}

template <class T>
static inline void CheckVectorString(const string excepted, vector<T>& vector) {
    CHECK_EQ(json::parse(excepted).dump(4), json(vector).dump(4));
}
