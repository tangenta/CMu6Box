#include "resources.h"
#include <QDir>
#include <QJsonDocument>
using SCMap = std::pair<std::vector<QString>, std::vector<Color>>;

Resources::Resources(QObject *parent) : QObject(parent) {
    player.setPlaylist(&playlist);

    QDir dir;
    dir.cd("/home/gaufoo/Music/Songs");
//    dir.cd("/home/tangenta/Music");
    QStringList files = dir.entryList((QStringList() << "*.mp3" << "*.flac"), QDir::Files);
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
    QString langFileLocation = settingObj.value("language-file").toString();
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
    obj.insert("language-file",
               QJsonValue(QString(translator.getFilename().c_str())));
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
     Color(NC::Green, NC::Red),
     Color(NC::Red, NC::Green),
     Color(NC::Blue, NC::Yellow),
     Color(NC::Yellow, NC::Blue),
     Color(NC::Green, NC::Magenta),
     Color(NC::Red, NC::Cyan),
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
