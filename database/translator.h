#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <QJsonObject>
#include <string>
#include <map>

class Translator {
public:
    Translator();
    Translator(std::string const& languageName);
    std::string operator()(std::string const& key);
    std::string operator()(const char* key);
    bool isEnglish();
private:
    std::map<std::string, std::string> const* dictionary;
};

#endif // TRANSLATOR_H
