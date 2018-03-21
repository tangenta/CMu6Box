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
    Window* newwin(int rows, int cols, int org_y, int org_x);
    Window* newwin();
    void delwin(Window*);
signals:

public slots:

private:
    bool hasColors;
    std::list<Window*> winList;
};

#endif // NCCONTROLLER_H
