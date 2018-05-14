#include "setting.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QTextStream>
#include "ncurse-wrap/exceptions.h"
Setting::Setting() {
    openSetting();
}

Setting::~Setting() {
    saveCurrentSetting();
}

void Setting::openSetting() {
    QFile file("setting.json");
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen()) {
        throw FatalError("unable to open setting.json");
    }
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &error);
    if (error.error != QJsonParseError::NoError) {
        throw FatalError(error.errorString().toStdString());
    }
    QString lang = jsonDoc.object().value(QString("language")).toString(QString("english"));
    if (lang == "english") {
        language = Dictionary::EN;
    } else if (lang == "chinese") {
        language = Dictionary::CN;
    } else {
        throw FatalError("unknown language");
    }

    QString themeStr = jsonDoc.object().value(QString("theme")).toString(QString("default"));
    if (themeStr == "default") {
        theme = Attr(Color(NC::White, NC::Cyan)/*, Font({NF::Bold})*/);
    } else {
        throw FatalError("unknown theme");
    }
}

void Setting::saveCurrentSetting() {
    QFile file("setting.json");
    file.open(QIODevice::WriteOnly);
    if (!file.isOpen()) {
        throw FatalError("unable to open setting.json");
    }
    QJsonObject jsonObj;
    QString langStr;
    switch (language) {
    case Dictionary::EN:
        langStr = QString("english");
        break;
    case Dictionary::CN:
        langStr = QString("chinese");
        break;
    }
    jsonObj.insert(QString("language"),QJsonValue(langStr));
    jsonObj.insert(QString("theme"), QJsonValue("default"));
    QTextStream out(&file);
    out << QJsonDocument(jsonObj).toJson();
}

Attr Setting::getTheme() {
    return theme;
}

Dictionary::Language Setting::getLanguage() {
    return language;
}
