#include "resources.h"
#include <QDir>

Resources::Resources(QObject *parent) : QObject(parent)
{
    player.setPlaylist(&playlist);

    QDir dir;
//    dir.cd("/home/gaufoo/Music/Songs");
    dir.cd("/home/tangenta/Music");
    QStringList files = dir.entryList((QStringList() << "*.mp3"), QDir::Files);
    for (const QString &f : files) {
        contents.push_back(QUrl::fromLocalFile(dir.path()+"/"+f));
    }
    playlist.addMedia(contents);
    playlist.setPlaybackMode(QMediaPlaylist::Random);

    player.setVolume(40);
}
