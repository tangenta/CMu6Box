#include "main_controller.h"

MainController::MainController(QObject *parent) : QObject(parent) {
    nccontroller.moveToThread(&viewThread);
    connect(this, &MainController::startLoop, &nccontroller, &NCController::exec);
    viewThread.start();
    emit startLoop();
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/tangenta/Desktop/Myplayer/music/Taylor Swift - Enchanted.mp3"));
    player->setVolume(50);
}

MainController::~MainController() {
    viewThread.quit();
    viewThread.wait();
}
