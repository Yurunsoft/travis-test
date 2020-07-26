#include "dict.h"

#include <json.h>
#include <util.h>

#include <fstream>

using namespace chinese_util;

// 从文件加载汉字数据
void Dict::LoadCharacterData(string file_name) {
    ifstream fs(file_name);
    json json_data;
    fs >> json_data;
    for (auto &el : json_data.items()) {
        Character *character = new Character;
        json value = el.value();
        if (value.size() < 5) {
            throw "Wrong data format";
        }
        split_string(value[0], ",", &character->pinyin);
        split_string(value[1], ",", &character->sc);
        split_string(value[2], ",", &character->tc);
        character->is_sc = 1 == value[3];
        character->is_tc = 1 == value[4];
        string character_string = el.key();
        characters[character_string] = character;
    }
    fs.close();
}

// 从文件加载拼音数据
void Dict::LoadPinyinData(string file_name) {
    ifstream fs(file_name);
    json json_data;
    fs >> json_data;
    // 读音
    for (auto &el : json_data["sound"].items()) {
        Pinyin *pinyin = new Pinyin;
        json value = el.value();
        pinyin->ab = value["ab"];
        pinyin->tone = value["tone"];
        string sound = el.key();
        pinyins[sound] = pinyin;
    }
    int num;
    // 声母
    num = json_data["split"]["shengmu"].size();
    shengmu = new string[num];
    while (num--) {
        shengmu[num] = json_data["split"]["shengmu"][num];
    }
    // 韵母
    num = json_data["split"]["yunmu"].size();
    yunmu = new string[num];
    while (num--) {
        yunmu[num] = json_data["split"]["yunmu"][num];
    }
    // 拼音分词
    function<void(unordered_map<string, PinyinSplitInfo *> *, json *)> parse_pinyin_fenci;
    parse_pinyin_fenci
        = [&parse_pinyin_fenci](unordered_map<string, PinyinSplitInfo *> *pinyinSplitInfos, json *json_data) {
              for (auto &el : json_data->items()) {
                  string c = el.key();
                  if ("py" == c) {
                      continue;
                  }
                  json value = el.value();
                  PinyinSplitInfo *pinyinSplitInfo = new PinyinSplitInfo;
                  pinyinSplitInfo->is_pinyin = value["py"].is_boolean() ? (bool)value["py"] : false;
                  unordered_map<string, PinyinSplitInfo *> *subPinyinSplitInfos
                      = new unordered_map<string, PinyinSplitInfo *>;
                  parse_pinyin_fenci(subPinyinSplitInfos, &value);
                  if (!subPinyinSplitInfos->empty()) {
                      pinyinSplitInfo->children = subPinyinSplitInfos;
                  }
                  (*pinyinSplitInfos)[c] = pinyinSplitInfo;
              }
          };
    parse_pinyin_fenci(&pinyinSplitInfos, &json_data["split"]["relation"]);
    fs.close();
}

// 获取汉字信息
Character Dict::GetCharacter(string string) { return *characters[string]; }

// 获取拼音信息
Pinyin Dict::GetPinyin(string string) { return *pinyins[string]; }

// 是否是声母
bool Dict::IsShengmu(string string) {
    for (short i = 0; i < shengmu_count; ++i) {
        if (string == shengmu[i]) {
            return true;
        }
    }
    return false;
}

// 是否是韵母
bool Dict::IsYunmu(string string) {
    for (short i = 0; i < yunmu_count; ++i) {
        if (string == yunmu[i]) {
            return true;
        }
    }
    return false;
}
