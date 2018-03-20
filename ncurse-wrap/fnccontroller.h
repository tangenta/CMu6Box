#ifndef FNCCONTROLLER_H
#define FNCCONTROLLER_H

#include "window.h"

class NCController {
public:
    NCController();
    NCController(NCController const&) = delete;
    NCController(NCController&&) = delete;
    NCController& operator=(NCController const&) = delete;
    NCController& operator=(NCController&&) = delete;
    ~NCController();
    Window* newWin(int rows, int cols, int org_y, int org_x);
    Window* newWin();
    void delWin(Window*);

private:
    bool hasColors;
};

#endif // NCCONTROLLER_H
