#include "main_controller.h"

MainController::MainController(QObject *parent) : QObject(parent) {
    nccontroller.moveToThread(&viewThread);
    connect(this, &MainController::startLoop, &nccontroller, &NCController::exec);
    viewThread.start();
    emit startLoop();
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/tangenta/Desktop/Myplayer/music/Sia - Chandelier.mp3"));
//    player->setMedia(QUrl::fromLocalFile("/home/gaufoo/Music/Linkin Park - Roads Untraveled.mp3"));
    player->setVolume(50);
    connect(&nccontroller, SIGNAL(play()), player, SLOT(play()));
    connect(&nccontroller, SIGNAL(pause()), player, SLOT(pause()));
    connect(&nccontroller, SIGNAL(setVolume(int)), player, SLOT(setVolume(int)));
}

MainController::~MainController() {
    viewThread.quit();
    viewThread.wait();
}
