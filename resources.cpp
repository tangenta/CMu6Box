#include "resources.h"
#include <QDir>

Resources::Resources(QObject *parent) : QObject(parent)
{
    player.setPlaylist(&playlist);

    QDir dir;
    dir.cd("/home/gaufoo/Music/Songs");
    QStringList files = dir.entryList(QDir::Files);
    for (const QString &f : files) {
        contents.push_back(QUrl::fromLocalFile(dir.path()+"/"+f));
    }
    playlist.addMedia(contents);
    playlist.setPlaybackMode(QMediaPlaylist::Random);
    player.setVolume(40);
}
