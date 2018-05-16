#ifndef NCCONTROLLER_H
#define NCCONTROLLER_H

#include <QObject>
#include "ncurse-wrap/util_window.h"
#include "ncurse-wrap/ncurses_wrapper.h"
#include "resources.h"
#include <QThread>

class NCController : public QObject {
    Q_OBJECT
public:
    explicit NCController(QObject *parent = 0);
    NCController(NCController const&) = delete;
    NCController(NCController&&) = delete;
    NCController& operator=(NCController const&) = delete;
    NCController& operator=(NCController&&) = delete;
    ~NCController();

    void changeCurrentWindow(Window*);
signals:
    void startLoop();
    void quitApp();
public slots:
    // main loop
    void exec();
private:
    Window* currentWindow;
    QThread playerThread;
<<<<<<< HEAD
    Resources resource;
=======
//    QThread resourceThread;
    Resources* resource;
>>>>>>> b24434edc2156e94af81f68446c529b37843af10
};

#endif // NCCONTROLLER_H
