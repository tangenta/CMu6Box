#include <QCoreApplication>
#include <QMediaPlayer>
#include <QFile>
#include "nccontroller.h"

int main(int argc, char** argv) {
    NCController nc;
//    nc.exec();

    //QCoreApplication a(argc, argv);

    Window* mywin = nc.newwin();
    mywin->addText("Hello world", Position(0, 0),
                        Color(NC::White), Font({NF::Bold}), AlignMode::Center, 20);
    mywin->addText("second line", Position(1, 0), Color(NC::Cyan),
                   Font({NF::Normal}), AlignMode::Right, 20);
    //return a.exec();
}
