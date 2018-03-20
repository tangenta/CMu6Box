#include "fnccontroller.h"
#include <ncurses.h>
#include <string>
#include "exceptions.h"
#include "window.h"
#include "constants.h"

NCController::NCController() {

    if (initscr() == NULL) {
        throw FatalError("initscr()");
    }
    hasColors = has_colors() == TRUE ? true : false;
    if (hasColors) {
        start_color();
    }
    refresh();
}

NCController::~NCController() {
    getch();
    if (endwin() == ERR) {
        throw FatalError("endwin()");
    }
}

Window* NCController::newWin() {
    Window* ret = new Window();
    return ret;
}

Window* NCController::newWin(int rows, int cols, int org_y, int org_x) {
    Window* ret = new Window(rows, cols, org_y, org_x);
    return ret;
}

void NCController::delWin(Window *wp) {
    if (delwin(static_cast<WINDOW*>(wp->wp)) == ERR) {
        throw FatalError("delwin()");
    }
    delete wp;
}

