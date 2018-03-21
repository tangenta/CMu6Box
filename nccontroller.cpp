#include "nccontroller.h"
#include "ncurse-wrap/ncurses_wrapper.h"
#include <string>
#include "ncurse-wrap/exceptions.h"
#include "ncurse-wrap/util_window.h"


NCController::NCController(QObject *parent)
    : QObject(parent) {
    Ncurses::initscr_s();
    if (Ncurses::has_color_s()) {
        Ncurses::start_color_s();
    }

    Ncurses::refresh_s();
}

NCController::~NCController() {
    Ncurses::getch_s();
    for (auto i: winList) {
        delwin(i);
    }
    Ncurses::endwin_s();
}

Window* NCController::newwin() {
    Window* ret = new Window();
    winList.push_back(ret);
    return ret;
}

Window* NCController::newwin(int rows, int cols, int org_y, int org_x) {
    Window* ret = new Window(rows, cols, org_y, org_x);
    winList.push_back(ret);
    return ret;
}

void NCController::delwin(Window* wp) {
    Ncurses::delwin_s(wp->wp);
    winList.remove(wp);
    delete wp;
}
