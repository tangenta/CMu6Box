#include "nccontroller.h"
#include "ncurse-wrap/ncurses_wrapper.h"
#include <string>
#include "ncurse-wrap/exceptions.h"
#include "ncurse-wrap/util_window.h"
#include "user-interfaces/menu_win.h"

#ifndef DEFAULT_INTERVAL
#define DEFAULT_INTERVAL 20
#endif

NCController::NCController(QObject *parent)
    : QObject(parent), currentWindow(nullptr) {
    // initialize the view
    Ncurses::initscr_s();
    if (Ncurses::has_color_s()) {
        Ncurses::start_color_s();
    }
    Ncurses::nodelay_s(Ncurses::getStdscr(), true);
    Ncurses::keypad_s(Ncurses::getStdscr(), true);
    Ncurses::set_escdelay_s(25);  // 原Esc键延迟为1000ms, 改为25ms    
    Ncurses::cbreak_s();
    Ncurses::refresh_s();
    resource = new Resources;
    changeCurrentWindow(new MenuWin(resource));
    Ncurses::wrefresh_s(currentWindow->wp);


    // move resource to other thread
    this->moveToThread(&playerThread);
    playerThread.start();

    connect(this, SIGNAL(startLoop()), this, SLOT(exec()));
    emit startLoop();

}

NCController::~NCController() {
    playerThread.quit();
    playerThread.wait();
    delete currentWindow;
    Ncurses::endwin_s();
    resource->writeSetting("setting.json");
    resource->writeSonglist("songlist.json");
//    resource->playlist.save(QUrl("playlist"));
}

void NCController::exec() {
    while (1) {
        Ncurses::noecho_s();
        int input;
        while ((input = Ncurses::getch_s()) == -1) {
            Ncurses::napms_s(DEFAULT_INTERVAL);
            currentWindow->clearScreen();
            currentWindow->draw();
            Ncurses::wrefresh_s(currentWindow->wp);
            currentWindow->update();
        }

        Window* nextWindow = currentWindow->handleInput(input);

        if (nextWindow == currentWindow) {            // 当前窗口
            continue;
        } else if (nextWindow) {                      // 新窗口
            changeCurrentWindow(nextWindow);
            continue;
        } else {                                      // 退出程序
            emit quitApp();
            break;
        }
    }
}


void NCController::changeCurrentWindow(Window * win) {
    if (currentWindow) {
        delete currentWindow;
    }
    currentWindow = win;
}
