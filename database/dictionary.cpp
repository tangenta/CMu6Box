#include "dictionary.h"
#include "ncurse-wrap/exceptions.h"
#include <QFile>
#include <QString>
#include <QJsonObject>
Dictionary::Dictionary() {
    setLanguage(EN);
}

void Dictionary::setLanguage(Language lan) {
    QString langFile;
    switch (lan) {
    case EN:
        langFile = QString("./locale/en_US.json");
        break;
    case CN:
        langFile = QString("./locale/zh_CN.json");
        break;
    }
    QFile file(langFile);
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen()) {
        throw FatalError(std::string("unable to open locale file: ") +
                         langFile.toStdString());
    }
    QJsonParseError parseErr;
    jsonDoc = QJsonDocument::fromJson(file.readAll(), &parseErr);
    if (parseErr.error != QJsonParseError::NoError) {
        throw FatalError(parseErr.errorString().toStdString());
    }
}

std::string Dictionary::operator[](std::string const& str) {
    QString key(str.c_str());
    QJsonValue jsonValue = jsonDoc.object().value(key);
    if (jsonValue.type() == QJsonValue::Undefined) {
        return str;
    }
    QString ret(jsonValue.toString());
    if (ret.isEmpty()) {
        return str;
    }
    return ret.toStdString();
}

std::string Dictionary::operator [](const char* str) {
    std::string wrapper(str);
    return (*this)[wrapper];
}
