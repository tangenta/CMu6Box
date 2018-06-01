#include "translator.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonParseError>
#include "../ncurse-wrap/exceptions.h"

static const std::map<std::string, std::string> cn = {
    {"Play", "播放"},
    {"Song List", "歌单"},
    {"Setting", "设置"},
    {"default", "默认"},
    {"language", "语言"},
    {"about", "关于"},
    {"theme", "主题"},
    {"Mode", "模式"},
    {"Current Item Once", "单曲播放"},
    {"Current Item In Loop", "单曲循环"},
    {"Sequential", "顺序播放"},
    {"Loop", "列表循环"},
    {"Random", "随机播放"},
    {"add to playinglist", "添加至播放列表"},
    {"replace playinglist", "置换播放列表"},
    {"add directory", "按文件夹添加"},
    {"replace directory", "按文件夹置换"},
    {"rename list", "重命名歌单"},
    {"remove songlist", "移除歌单"},
    {"*add list*", "*添加歌单*"},
    {"Sort list", "排序"},
    {"Remove song", "移除歌曲"},
    {"Move to..", "移动到.."},
    {"Song information", "歌曲信息"},
    {"SONGLIST", "歌单"},
    {"CONTENT", "内容"},
};

Translator::Translator() {}

Translator::Translator(std::string const& languageName) {
    if (languageName == "Chinese") {
        dictionary = &cn;       // Chinese
    } else {
        dictionary = nullptr;   // Chinglish or unknown language
    }
}

std::string Translator::operator() (std::string const& key) {
    if (!dictionary) return key;
    std::string ret;
    try {
        ret = dictionary->at(key);
        return ret;
    } catch (std::out_of_range const&) {
        // no such element exist
    }
    return key;
}

std::string Translator::operator ()(const char* key) {
    return (*this)(std::string(key));
}

bool Translator::isEnglish() {
    return !dictionary;
}
