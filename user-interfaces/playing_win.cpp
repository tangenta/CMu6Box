#include "playing_win.h"
#include "menu_win.h"
#include "../ncurse-wrap/util_rollingtext.h"
#include "../ncurse-wrap/util_statictext.h"
#include "../ncurse-wrap/util_border.h"
#include "../ncurse-wrap/ncurses_wrapper.h"
#include "../ncurse-wrap/util_menu.h"
#include <algorithm>
#include <string>
#include "../main_controller.h"

extern MainController* mainController;

PlayingWin::PlayingWin(QObject* parent)
    : text(std::make_shared<StaticText>("play", Position(11,1),
                      80, Attr(), AlignMode::Center)), playing(false) {
    MainController::connect(this, SIGNAL(play()),
                            mainController->player, SLOT(play()));
    MainController::connect(this, SIGNAL(pause()),
                            mainController->player, SLOT(pause()));
}

PlayingWin::~PlayingWin() {}

Window* PlayingWin::handleInput(int ch) {
    if (ch == NK::Enter) {
        std::string displayStr(playing ? "pause" : "play");
        playing = !playing;
        text->content = displayStr;
        if (playing) {
            emit play();
        } else {
            emit pause();
        }
        return this;
    } else if (ch == NK::Esc) {
        return new MenuWin;
    } else {
        return this;
    }
}

void PlayingWin::update() {
    text->update();
}

void PlayingWin::draw() {
    text->draw(this);
}
