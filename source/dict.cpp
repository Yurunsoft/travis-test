#include "dict.h"

#include <json.h>

#include <fstream>

#include "util.h"

using namespace chinese_util;

Dict::~Dict() {
    ClearCharacters();
    ClearPinyins();
    ClearPinyinSplitInfos();
    if (shengmu) {
        delete[] shengmu;
    }
    if (yunmu) {
        delete[] yunmu;
    }
}

// 从文件加载汉字数据
void Dict::LoadCharacterData(string file_name) {
    ifstream fs(file_name);
    json json_data;
    fs >> json_data;
    ClearCharacters();
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
    ClearPinyins();
    for (auto &el : json_data["sound"].items()) {
        PinyinInfo *pinyin = new PinyinInfo;
        json value = el.value();
        pinyin->ab = value["ab"].get<string>();
        pinyin->tone = value["tone"].get<short>();
        string sound = el.key();
        pinyins[sound] = pinyin;
    }
    int num;
    // 声母
    num = json_data["split"]["shengmu"].size();
    if (shengmu) {
        delete[] shengmu;
    }
    shengmu = new string[num];
    for (int i = 0; i < num; ++i) {
        shengmu[i] = json_data["split"]["shengmu"][i].get<string>();
    }
    // 韵母
    num = json_data["split"]["yunmu"].size();
    if (yunmu) {
        delete[] yunmu;
    }
    yunmu = new string[num];
    for (int i = 0; i < num; ++i) {
        yunmu[i] = json_data["split"]["yunmu"][i].get<string>();
    }
    // 拼音分词
    function<void(unordered_map<string, PinyinSplitInfo *> *, json *)> parse_pinyin_fenci;
    parse_pinyin_fenci = [&parse_pinyin_fenci](unordered_map<string, PinyinSplitInfo *> *pinyinSplitInfos, json *json_data) {
        for (auto &el : json_data->items()) {
            string c = el.key();
            if ("py" == c) {
                continue;
            }
            json value = el.value();
            PinyinSplitInfo *pinyinSplitInfo = new PinyinSplitInfo;
            pinyinSplitInfo->is_pinyin = value["py"].is_boolean() ? value["py"].get<bool>() : false;
            unordered_map<string, PinyinSplitInfo *> *subPinyinSplitInfos
                = new unordered_map<string, PinyinSplitInfo *>;
            parse_pinyin_fenci(subPinyinSplitInfos, &value);
            if (!subPinyinSplitInfos->empty()) {
                pinyinSplitInfo->children = subPinyinSplitInfos;
            }
            (*pinyinSplitInfos)[c] = pinyinSplitInfo;
        }
    };
    ClearPinyinSplitInfos();
    parse_pinyin_fenci(&pinyinSplitInfos, &json_data["split"]["relation"]);
    fs.close();
}

// 获取汉字信息
const Character *Dict::GetCharacter(string string) { return characters[string]; }

// 获取拼音信息
const PinyinInfo *Dict::GetPinyin(string string) { return pinyins[string]; }

// 拼音转换
void Dict::ConvertPinyin(const string pinyin_sound, string & pinyin, string & pinyin_sound_number){
    pinyin = pinyin_sound;
    pinyin_sound_number = pinyin_sound;

    vector<string> characters;
    split_character_utf8(pinyin, characters);

    for (string tmp : characters) {
        if (pinyins[tmp]) {
            pinyin = pinyin.replace(pinyin.find(tmp), 2, pinyins[tmp]->ab);
            pinyin_sound_number = pinyin_sound_number.replace(pinyin_sound_number.find(tmp), 2, pinyins[tmp]->ab + pinyins[tmp]->tone);
            break;
        }
    }
}

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

void Dict::ClearCharacters() {
    for (auto i = characters.begin(); i != characters.end(); i++) {
        delete i->second;
    }
}

void Dict::ClearPinyins() {
    for (auto i = pinyins.begin(); i != pinyins.end(); i++) {
        delete i->second;
    }
}

void Dict::ClearPinyinSplitInfos() {
    for (auto i = pinyinSplitInfos.begin(); i != pinyinSplitInfos.end(); i++) {
        delete i->second;
    }
}

extern "C" {
    // 创建字典
    void* create_dict()
    {
        return new Dict;
    }

    // 关闭字典
    void close_dict(void* dict)
    {
        delete ((Dict*)dict);
    }

    // 从文件加载汉字数据
    void load_character_data(void* dict, const char* file_name)
    {
        ((Dict*)dict)->LoadCharacterData(file_name);
    }

    // 从文件加载拼音数据
    void load_pinyin_data(void* dict, const char* file_name)
    {
        ((Dict*)dict)->LoadPinyinData(file_name);
    }
}
