#ifndef NCCONTROLLER_H
#define NCCONTROLLER_H

#include <QObject>
#include "ncurse-wrap/util_window.h"
#include "ncurse-wrap/ncurses_wrapper.h"
#include <list>

class NCController : public QObject {
    Q_OBJECT
public:
    explicit NCController(QObject *parent = 0);
    NCController(NCController const&) = delete;
    NCController(NCController&&) = delete;
    NCController& operator=(NCController const&) = delete;
    NCController& operator=(NCController&&) = delete;
    ~NCController();
    // windows control
    Window* newwin(int rows, int cols, int org_y, int org_x);
    Window* newwin();
    void delwin(Window*);

    // main loop
    void exec();
signals:

public slots:

private:
    void parseInput(int ch);
    bool hasColors;
    std::list<Window*> winList;
};

#endif // NCCONTROLLER_H
