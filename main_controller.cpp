#include "main_controller.h"

MainController::MainController(QObject *parent) : QObject(parent) {
    nccontroller.moveToThread(&viewThread);
    connect(this, &MainController::startLoop, &nccontroller, &NCController::exec);
    viewThread.start();
    emit startLoop();
    playlist = new QMediaPlaylist;
    player = new QMediaPlayer;
    player->setPlaylist(playlist);

    dir.cd("/home/gaufoo/Music/Songs");
    QStringList files = dir.entryList(QDir::Files);
    QList<QMediaContent> content;
    for (const QString &f : files) {
        content.push_back(QUrl::fromLocalFile(dir.path()+"/"+f));
    }
    playlist->addMedia(content);
    playlist->shuffle();

    player->setVolume(50);
    connect(&nccontroller, SIGNAL(play()), player, SLOT(play()));
    connect(&nccontroller, SIGNAL(pause()), player, SLOT(pause()));
    connect(&nccontroller, SIGNAL(setVolume(int)), player, SLOT(setVolume(int)));
    // next two lines can not work, dunno why
    connect(&nccontroller, SIGNAL(next()), playlist, SLOT(next()));
    connect(&nccontroller, SIGNAL(previous()), playlist, SLOT(previous()));
}

MainController::~MainController() {
    viewThread.quit();
    viewThread.wait();
}
