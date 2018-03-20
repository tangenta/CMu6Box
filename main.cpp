#include <QCoreApplication>
#include <QMediaPlayer>
#include <QFile>
// #include "test.h"
#include "nccontroller.h"
//#include <QTimer>

int main(int argc, char** argv) {

    QCoreApplication a(argc, argv);
////    QTimer *timer = new QTimer;
//    Test t;
////    QCoreApplication::connect(timer, SIGNAL(timeout()), &t, SLOT(update()));
////    timer->start(100);
//    t.coutStr("hello world!!! asddfjasognartj");
//    QMediaPlayer* player;
//    player = new QMediaPlayer;
//    player->setMedia(QUrl::fromLocalFile("/home/tangenta/Desktop/Myplayer/Avril Lavigne - TiK ToK.mp3"));
////    player->setMedia(QUrl::fromLocalFile("/home/tangenta/Downloads/Telegram Desktop/7!! - オレンジ.flac"));
//    player->setVolume(30);
//    player->play();
//    QKeyEvent* keyeve = new QKeyEvent(QEvent::KeyPress, Qt::Key_M, Qt::NoModifier, QString("asdfs"));
//    a.postEvent(&t, keyeve);
    return a.exec();
}
