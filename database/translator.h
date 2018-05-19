#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <QJsonObject>
#include <string>

class Translator {
public:
    Translator();
    Translator(std::string const& fileName);
    std::string operator()(std::string const& key);
    std::string operator()(const char* key);
    std::string getFilename();
private:
    std::string filename;
    QJsonObject doc;
};

#endif // TRANSLATOR_H
