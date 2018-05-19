#include <QCoreApplication>
#include "nccontroller.h"

int main(int argc, char** argv) {
    QCoreApplication a(argc, argv);
    NCController* nc = new NCController;  // weird
    QCoreApplication::connect(nc, SIGNAL(quitApp()), nc, SLOT(cleanUp()));
    QCoreApplication::connect(nc, SIGNAL(quitApp()), &a, SLOT(quit()));
    return a.exec();
}
