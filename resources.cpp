#include "resources.h"
#include <QMediaPlaylist>

Resources::Resources(QObject *parent) : QObject(parent)
{
    //player.setMedia(QUrl::fromLocalFile("/home/tangenta/Desktop/Myplayer/music/Sia - Chandelier.mp3"));
    player.setPlaylist(new QMediaPlaylist);
    player.playlist()->addMedia(QUrl::fromLocalFile("/home/tangenta/Desktop/Myplayer/music/Sia - Chandelier.mp3"));
    player.setVolume(40);
}
