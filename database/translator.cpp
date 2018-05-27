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
