#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include <QObject>
#include "nccontroller.h"
#include <QThread>

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
};

#endif // MAIN_CONTROLLER_H
