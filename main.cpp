#include <QCoreApplication>
#include <QMediaPlayer>
#include <QFile>
#include "nccontroller.h"

int main(int argc, char** argv) {
    NCController nc;
    //QCoreApplication a(argc, argv);

    Window* mywin = nc.newWin();
    mywin->addText(Text("Hello world", Position(0, 0), 20,
                        Color(NC::Blue), Font(NF::Bold), AlignMode::Center));
    //return a.exec();
}
