#include "setting.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QTextStream>
#include "ncurse-wrap/exceptions.h"

QJsonDocument jsonFile2Doc(QString const& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw JsonOpenError(std::string("unable to open") + filename.toStdString());
    }
    QJsonParseError parseErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &parseErr);
    if (parseErr.error != QJsonParseError::NoError) {
        file.close();
        throw FatalError(parseErr.errorString().toStdString());
    }
    file.close();
    return jsonDoc;
}

QString getValueFromJsonDoc(QJsonDocument const& doc, QString const& key, QString const& defaultStr) {
    QString retStr(defaultStr);
    QJsonValue value = doc.object().value(key);
    if (value.type() == QJsonValue::Undefined) {
        return retStr;
    }
    retStr = value.toString();
    if (retStr.isNull()) {
        throw FatalError(key.toStdString() + " is not a string");
    }
    return retStr;
}

Setting::Setting() {}


void Setting::openSetting() {
    QJsonDocument jsonDoc = jsonFile2Doc("setting.json");
    QString lang = getValueFromJsonDoc(jsonDoc, "language", "english");
    if (lang == "english") {
        language = EN;
    } else if (lang == "chinese") {
        language = CN;
    } else {
        throw FatalError("unknown language");
    }

    QString themeStr = getValueFromJsonDoc(jsonDoc, "theme", "default");
    if (themeStr == "default") {
        theme = Attr(Color(NC::White, NC::Cyan)/*, Font({NF::Bold})*/);
    } else {
        throw FatalError("unknown theme");
    }
}

void Setting::saveCurrentSetting() {
    QFile file("setting.json");
    if (!file.open(QIODevice::WriteOnly)) {
        throw JsonOpenError("unable to open setting.json");
    }
    QString langStr;
    switch (language) {
    case EN:
        langStr = QString("english");
        break;
    case CN:
        langStr = QString("chinese");
        break;
    }
    QJsonObject jsonObj;
    jsonObj.insert(QString("language"),QJsonValue(langStr));
    jsonObj.insert(QString("theme"), QJsonValue("default"));
    QTextStream out(&file);
    out << QJsonDocument(jsonObj).toJson();
    file.close();
}

void Setting::loadLanguage(Language lan) {
    QString langFile;
    switch (lan) {
    case EN:
        langFile = QString("./locale/en_US.json");
        break;
    case CN:
        langFile = QString("./locale/zh_CN.json");
        break;
    }
    langDoc = jsonFile2Doc(langFile);
}

Attr Setting::getTheme() {
    return theme;
}

Setting::Language Setting::getLanguage() {
    return language;
}

std::string Setting::tr(const std::string & str) {
    QString key(str.c_str());
    return getValueFromJsonDoc(langDoc, key, key).toStdString();
}

std::string Setting::tr(const char* str) {
    QString key(str);
    return getValueFromJsonDoc(langDoc, key, key).toStdString();
}
