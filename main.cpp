#include <QCoreApplication>
#include <QMediaPlayer>
#include <QFile>
#include "main_controller.h"

int main(int argc, char** argv) {
    QCoreApplication a(argc, argv);
    new MainController;  // weird
    return a.exec();
}
