#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include <QObject>
#include "nccontroller.h"
#include <QThread>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>

class MainController : public QObject {
    Q_OBJECT
public:
    explicit MainController(QObject *parent = 0);
    ~MainController();
signals:
    void startLoop();
public slots:
private:
    NCController nccontroller;
    QThread viewThread;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    QDir dir;
};

#endif // MAIN_CONTROLLER_H
