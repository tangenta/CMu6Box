#ifndef NCCONTROLLER_H
#define NCCONTROLLER_H

#include <QObject>
#include "ncurse-wrap/util_window.h"
#include "ncurse-wrap/ncurses_wrapper.h"

class NCController : public QObject {
    Q_OBJECT
public:
    explicit NCController(QObject *parent = 0);
    NCController(NCController const&) = delete;
    NCController(NCController&&) = delete;
    NCController& operator=(NCController const&) = delete;
    NCController& operator=(NCController&&) = delete;
    ~NCController();

    // main loop
    void exec();
signals:

public slots:
    void changeCurrentWindow(Window*);

private:
    Window* currentWindow;
};

#endif // NCCONTROLLER_H
