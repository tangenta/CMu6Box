#include <QCoreApplication>
#include <QMediaPlayer>
#include <QFile>
#include "nccontroller.h"

int main(int argc, char** argv) {
    NCController nc;
    nc.exec();

    //QCoreApplication a(argc, argv);

//    Window* mywin = nc.newwin();
//    mywin->addText(Text("Hello world", Position(0, 0), 20,
//                        Color(NC::White), Font(NF::Bold), AlignMode::Center));
    //return a.exec();
}
