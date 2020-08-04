#pragma once

#include <unistd.h>

#include <string>

using namespace std;

#ifndef MAX_SIZE
#    define MAX_SIZE 1024
#endif

static string get_dir() {
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
}