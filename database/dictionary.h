#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <QJsonDocument>

class Dictionary {

public:
    enum Language { CN, EN };
    Dictionary();
    void setLanguage(Language lan);
    std::string operator[](std::string const& str);
    std::string operator[](const char* str);
private:
    QJsonDocument jsonDoc;
};

#endif // DICTIONARY_H
