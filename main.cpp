#include <QCoreApplication>
#include <QMediaPlayer>
#include <QFile>
#include "main_controller.h"

//MainController* mainController;

int main(int argc, char** argv) {
    QCoreApplication a(argc, argv);
    new MainController;  // weird
    return a.exec();
}
