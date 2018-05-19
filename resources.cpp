#include "resources.h"
#include <QDir>
#include <QJsonDocument>

Resources::Resources(QObject *parent) : QObject(parent) {
    player.setPlaylist(&playlist);

    QDir dir;
//    dir.cd("/home/gaufoo/Music/Songs");
    dir.cd("/home/tangenta/Music");
    QStringList files = dir.entryList((QStringList() << "*.mp3" << "*.flat"), QDir::Files);
    for (const QString &f : files) {
        contents.push_back(QUrl::fromLocalFile(dir.path()+"/"+f));
    }
    playlist.addMedia(contents);
    playlist.setPlaybackMode(QMediaPlaylist::Random);
    player.setVolume(40);


    try {
        readSetting("setting.json");
    } catch (Exception const&) {  // fallback to default
        translator = Translator();
        themeColor = QString("Black");
    }
}


void Resources::readSetting(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw FatalError("Resources::readSetting()");
    }

    QJsonParseError parseErr;
    QJsonObject settingObj = QJsonDocument::fromJson(file.readAll(), &parseErr).object();
    file.close();

    if (parseErr.error != QJsonParseError::NoError) {
        throw JsonOpenError("Resources::readSetting()");
    }
    QString langFileLocation = settingObj.value("language-file-location").toString();
    QString colorStr = settingObj.value("theme").toString();
    translator = Translator(langFileLocation.toStdString());
    themeColor = colorStr;

}

void Resources::writeSetting(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw FatalError("Resource::writeSetting()");
    }
    QTextStream out(&file);
    QJsonObject obj;
    obj.insert("language-file-location",
               QJsonValue(QString(translator.getFilename().c_str())));
    obj.insert("theme", QJsonValue(themeColor));
    QJsonDocument doc(obj);
    out << doc.toJson();
    file.close();
}
