#include "translator.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonParseError>
#include "../ncurse-wrap/exceptions.h"

Translator::Translator() {}

Translator::Translator(std::string const& fileName) {
    QFile file(QString(fileName.c_str()));
    if (!file.open(QIODevice::ReadOnly)) {
        throw FatalError("Translator::Translator");
    }
    QByteArray bytes(file.readAll());
    QJsonParseError parseErr;
    doc = QJsonDocument::fromJson(bytes, &parseErr).object();
    if (parseErr.error != QJsonParseError::NoError) {
        file.close();
        throw FatalError("Translator::Translator");
    }
    file.close();
}

std::string Translator::operator() (std::string const& key) {
    if (doc.isEmpty()) return key;
    QJsonValue value = doc.value(QString(key.c_str()));
    if (value.isUndefined()) {
        // key does not exist
        return key;
    }
    QString ret = value.toString();
    if (ret.isNull()) {
        // key is not string
        throw FatalError("Translator::operator()");
    }
    return ret.toStdString();
}

std::string Translator::operator ()(const char* key) {
    return (*this)(std::string(key));
}
