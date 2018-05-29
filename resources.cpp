#include "resources.h"
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
using SCMap = std::pair<std::vector<QString>, std::vector<Color>>;

Resources::Resources(QObject *parent) : QObject(parent) {
    player.setPlaylist(&playlist);

    playlist.setPlaybackMode(QMediaPlaylist::Random);
    player.setVolume(40);


    try {
        readSetting("setting.json");
    } catch (Exception const&) {  // fallback to default
        translator = Translator();
        themeColor = QString("Black");
    }

    try {
        readSonglist("songlist.json");
    } catch (Exception const&) {

    }
    songlistNames.push_back("*add list*");
    songlists.push_back({});

    try {
        readPlayinglist("playinglist.json");
    } catch (Exception const&) {

    }
    refreshPlayinglist();
}

void Resources::refreshPlayinglist() {
    QList<QMediaContent> pl;
    for (const QString &f : playingList) {
        pl.push_back(QUrl::fromLocalFile(f));
    }
    playlist.clear();
    playlist.addMedia(pl);
}

void Resources::readPlayinglist(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw FatalError("Resources::readSonglist()");
    }

    QJsonParseError parseErr;
    QJsonObject playinglistObj = QJsonDocument::fromJson(file.readAll(), &parseErr).object();
    file.close();

    if (parseErr.error != QJsonParseError::NoError) {
        throw JsonOpenError("Resources::readSonglist()");
    }

    QJsonArray playinglistAry = playinglistObj.value("playinglist").toArray();

    for (const QJsonValue& v : playinglistAry) {
        playingList.push_back(v.toString());
    }
}

void Resources::writePlayinglist(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw FatalError("Resource::writeSonglist()");
    }
    QTextStream out(&file);
    QJsonObject obj;

    obj.insert("playinglist", QJsonArray::fromStringList(playingList));

    QJsonDocument doc(obj);
    out << doc.toJson();
    file.close();
}

void Resources::readSonglist(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw FatalError("Resources::readSonglist()");
    }

    QJsonParseError parseErr;
    QJsonObject songlistObj = QJsonDocument::fromJson(file.readAll(), &parseErr).object();
    file.close();

    if (parseErr.error != QJsonParseError::NoError) {
        throw JsonOpenError("Resources::readSonglist()");
    }
    QStringList names = songlistObj.keys();
    for (const QString &n : names) {
        songlistNames.push_back(n);
    }

    for (const QString &n : songlistNames) {
        QJsonArray ary = songlistObj[n].toArray();
        songlists.push_back({});
        for (const QJsonValue& v : ary) {
            songlists.back().push_back(v.toString());
        }
    }
}

void Resources::writeSonglist(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw FatalError("Resource::writeSonglist()");
    }
    QTextStream out(&file);
    QJsonObject obj;
    // -1 : remove "*add list*"
    for (int i = 0; i < songlistNames.size()-1; i++) {
        obj.insert(songlistNames.at(i), QJsonArray::fromStringList(songlists.at(i)));
    }

    QJsonDocument doc(obj);
    out << doc.toJson();
    file.close();
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
    QString colorStr = settingObj.value("theme").toString();
    themeColor = colorStr;

}

void Resources::writeSetting(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw FatalError("Resource::writeSetting()");
    }
    QTextStream out(&file);
    QJsonObject obj;
    obj.insert("theme", QJsonValue(themeColor));
    QJsonDocument doc(obj);
    out << doc.toJson();
    file.close();
}

Color Resources::parseColor(QString const& colorStr) {
    static SCMap scmap = std::make_pair<std::vector<QString>, std::vector<Color>>(
    {"Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White"},
    {Color(NC::White, NC::Black),
     Color(NC::White, NC::Red),
     Color(NC::White, NC::Green),
     Color(NC::White, NC::Yellow),
     Color(NC::White, NC::Blue),
     Color(NC::White, NC::Magenta),
     Color(NC::White, NC::Cyan),
     Color(NC::Black, NC::White)});
    auto& keys = scmap.first;
    auto& values = scmap.second;
    if (keys.size() != values.size()) {
        throw FatalError("Resources::parseColor()");
    }
    auto iter = std::find(keys.begin(), keys.end(), colorStr);
    if (iter == keys.end()) {
        throw FatalError("Resources::parseColor()");
    }
    auto diff = iter-keys.begin();
    return *(values.begin()+diff);
}

Color Resources::parseHighlight(const QString &colorStr) {
    static SCMap highlightmap = std::make_pair<std::vector<QString>, std::vector<Color>>(
    {"Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White"},
    {Color(NC::Cyan, NC::Black),
     Color(NC::Black, NC::Red),
     Color(NC::Yellow, NC::Green),
     Color(NC::Cyan, NC::Yellow),
     Color(NC::Yellow, NC::Blue),
     Color(NC::Yellow, NC::Magenta),
     Color(NC::Yellow, NC::Cyan),
     Color(NC::White, NC::White)});
    auto& keys = highlightmap.first;
    auto& values = highlightmap.second;
    if (keys.size() != values.size()) {
        throw FatalError("Resources::parseColor()");
    }
    auto iter = std::find(keys.begin(), keys.end(), colorStr);
    if (iter == keys.end()) {
        throw FatalError("Resources::parseColor()");
    }
    auto diff = iter-keys.begin();
    return *(values.begin()+diff);
}
