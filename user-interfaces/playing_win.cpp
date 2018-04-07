#include "playing_win.h"
#include "menu_win.h"

PlayingWin::PlayingWin()
{
    const int width = 40;
    const int height = 10;
    addBlock(Position(this->getRows() / 2 - height / 2, this->getCols() / 2 - width / 2), 
             Position(this->getRows() / 2 + height / 2, this->getCols() / 2 + width / 2), 
             {"Hello Kitty", "Peppa Pig", "Super Man"}, 
             Color(NC::White), 
             Font({NF::Bold}));
}

Window* PlayingWin::handleInput(int ch) {
    if (ch == NK::Esc) {
        return new MenuWin;
    } else {
        return this;
    }
}
