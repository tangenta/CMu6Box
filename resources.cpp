#include "resources.h"

Resources::Resources(QObject *parent) : QObject(parent)
{
    player.setMedia(QUrl::fromLocalFile("/home/tangenta/Desktop/Myplayer/music/Sia - Chandelier.mp3"));
    player.setVolume(40);
}
