#include "pinyin.h"
#include "util.h"
#include <vector>
#include <map>

using namespace chinese_util;

struct ListItem{
    bool is_chinese;
    string character;
    const Character* character_info;
};

static void parseResult(Dict *dict, PinyinResult *result, const ListItem *item, const string & word_split)
{
    // if(item->is_chinese)
    // {
    //     // dict->GetPinyin(item->character)
    // }

    if(result->pinyin)
    {
        vector<string> origin_vector = *result->pinyin;
        vector<string> *tmp_vector;
        string pinyin_item;
        map<string, bool> exists_pinyins;
        for(int i = 0; i < item->character_info->pinyin.size(); ++i)
        {
            pinyin_item = dict->ConverToNoSoundPinyin(item->character_info->pinyin[i]);
            if(exists_pinyins[pinyin_item])
            {
                continue;
            }
            exists_pinyins[pinyin_item] = true;
            pinyin_item += word_split;
            if(0 == i)
            {
                tmp_vector = result->pinyin;
            }
            else
            {
                tmp_vector = new vector<string> (origin_vector);
            }
            for(string &result_item : *tmp_vector)
            {
                result_item += pinyin_item;
            }
            if(0 != i)
            {
                result->pinyin->insert(result->pinyin->end(), tmp_vector->begin(), tmp_vector->end());
                delete tmp_vector;
            }
        }
    }
}

PinyinResult Pinyin::convert(Dict *dict, const string & text, ConvertMode mode, const string & word_split, bool split_not_pinyin_char)
{
    PinyinResult result;

    // 初始化
    if(mode & ConvertMode::PINYIN)
    {
        result.pinyin = new vector<string>({""});
    }
    if(mode & ConvertMode::PINYIN_SOUND)
    {
        result.pinyin_sound = new vector<string>({""});
    }
    if(mode & ConvertMode::PINYIN_SOUND_NUMBER)
    {
        result.pinyin_sound_number = new vector<string>({""});
    }
    if(mode & ConvertMode::PINYIN_FIRST)
    {
        result.pinyin_first = new vector<string>({""});
    }

    // 分割字符
    vector<string> characters;
    split_character_utf8(text, characters);

    // vector<ListItem> list;
    string no_result_item;
    for(auto c : characters)
    {
        const Character* character = dict->GetCharacter(c);
        ListItem item;
        item.character = c;
        if(character)
        {
            if(split_not_pinyin_char && "" != no_result_item)
            {
                ListItem item2;
                item2.is_chinese = false;
                item2.character = no_result_item;
                // list.push_back(item2);
                parseResult(dict, &result, &item2, word_split);
                no_result_item.clear();
            }
            item.is_chinese = true;
            item.character_info = character;
        }
        else
        {
            if(split_not_pinyin_char)
            {
                no_result_item += c;
                continue;
            }
            item.is_chinese = false;
        }
        // list.push_back(item);
        parseResult(dict, &result, &item, word_split);
    }
    if(split_not_pinyin_char && "" != no_result_item)
    {
        ListItem item2;
        item2.is_chinese = false;
        item2.character = no_result_item;
        parseResult(dict, &result, &item2, word_split);
    }

    return result;
}
