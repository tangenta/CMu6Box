#ifndef NCCONTROLLER_H
#define NCCONTROLLER_H

#include <QObject>
#include "ncurse-wrap/window.h"
#include "ncurse-wrap/constants.h"

class NCController : public QObject {
    Q_OBJECT
public:
    explicit NCController(QObject *parent = 0);
    NCController(NCController const&) = delete;
    NCController(NCController&&) = delete;
    NCController& operator=(NCController const&) = delete;
    NCController& operator=(NCController&&) = delete;
    ~NCController();
    Window* newWin(int rows, int cols, int org_y, int org_x);
    Window* newWin();
    void delWin(Window*);
signals:

public slots:

private:
    bool hasColors;
};

#endif // NCCONTROLLER_H
