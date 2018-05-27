#include <QCoreApplication>
#include "nccontroller.h"

int main(int argc, char** argv) {
    QCoreApplication a(argc, argv);
    NCController nc;
    QCoreApplication::connect(&nc, SIGNAL(quitApp()), &a, SLOT(quit()));
    return a.exec();
}
