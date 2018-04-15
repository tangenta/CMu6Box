#include "nccontroller.h"
#include "ncurse-wrap/ncurses_wrapper.h"
#include <string>
#include "ncurse-wrap/exceptions.h"
#include "ncurse-wrap/util_window.h"
#include "user-interfaces/menu_win.h"

#ifndef DEFAULT_INTERVAL
#define DEFAULT_INTERVAL 10
#endif

NCController::NCController(QObject *parent)
    : QObject(parent) {
    Ncurses::initscr_s();
    if (Ncurses::has_color_s()) {
        Ncurses::start_color_s();
    }
    Ncurses::nodelay_s(Ncurses::getStdscr(), true);
    Ncurses::keypad_s(Ncurses::getStdscr(), true);
    Ncurses::set_escdelay_s(25);  // 原Esc键延迟为1000ms, 改为25ms    
    Ncurses::cbreak_s();
    Ncurses::refresh_s();
    currentWindow = new MenuWin;
    Ncurses::wrefresh_s(currentWindow->wp);
}

NCController::~NCController() {
//    Ncurses::nodelay_s(Ncurses::getStdscr(), false);
//    Ncurses::getch_s();
    delete currentWindow;
    Ncurses::endwin_s();
}

void NCController::exec() {
    Ncurses::noecho_s();
    
    int input;
    while ((input = Ncurses::getch_s()) == -1) {
        Ncurses::napms_s(DEFAULT_INTERVAL);
    }

    Window* nextWindow = currentWindow->handleInput(input);

    if (nextWindow == currentWindow) {            // 当前窗口
        Ncurses::wrefresh_s(currentWindow->wp);
        return exec();
    } else if (nextWindow) {                      // 新窗口
        changeCurrentWindow(nextWindow);
        Ncurses::wrefresh_s(currentWindow->wp);
        return exec();
    } else {                                      // 退出程序
        return;
    }
}

void NCController::changeCurrentWindow(Window * win) {
    delete currentWindow;
    currentWindow = win;
}
