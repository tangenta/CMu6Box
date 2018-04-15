#include "playing_win.h"
#include "menu_win.h"

PlayingWin::PlayingWin()
{
//    const int width = 40;
//    const int height = 10;
//    addBlock(Position(this->getRows() / 2 - height / 2, this->getCols() / 2 - width / 2),
//             Position(this->getRows() / 2 + height / 2, this->getCols() / 2 + width / 2),
//             {"Hello Kitty", "Peppa Pig", "Super Man"},
//             Color(NC::White),
//             Font({NF::Bold}));

    updateWin0();

    subwinNo = 0;
    focus0 = 0;
    focus1 = 0;
    focus2 = 0;
}

Window* PlayingWin::handleInput(int ch) {
    switch (subwinNo) {
    case 0:
        return win0(ch);
    case 1:
        return win1(ch);
    case 2:
        return win2(ch);
    default:
        return this;
    }
}

Window* PlayingWin::win0(int ch) {
    if (ch == NK::Esc) {
        return new MenuWin;

    } else if(ch == NK::Left) {
        if (--focus0 < 0) focus0 += 3;
        updateWin0();
        return this;

    } else if (ch == NK::Right) {
        focus0 = (focus0+1) % 3;
        updateWin0();
        return this;

    } else if (ch == NK::Enter) {
        subwinNo = 1;
        updateWin1();
        return this;

    } else {
        return this;
    }
}

Window* PlayingWin::win1(int ch) {
    if (ch == NK::Esc) {
        Ncurses::werase_s(this->wp);

        subwinNo = 0;
        updateWin0();
        return this;

    } else if(ch == NK::Left) {
        if (--focus1 < 0) focus1 += 3;
        updateWin1();
        return this;

    } else if (ch == NK::Right) {
        focus1 = (focus1+1) % 3;
        updateWin1();
        return this;

    } else if (ch == NK::Enter) {
        subwinNo = 2;
        updateWin2();
        return this;

    } else {
        return this;
    }
}

Window* PlayingWin::win2(int ch) {
    if (ch == NK::Esc) {
        Ncurses::werase_s(this->wp);

        updateWin0();
        subwinNo = 1;
        updateWin1();
        return this;

    } else if(ch == NK::Up) {
        if (--focus2 < 0) focus2 += 3;
        updateWin2();
        return this;

    } else if (ch == NK::Down) {
        focus2 = (focus2+1) % 3;
        updateWin2();
        return this;

    } else {
        return this;
    }
}

void PlayingWin::updateWin0() {
    Color playColor(NC::White);
    Color songListColor(NC::White);
    Color settingColor(NC::White);
    switch (focus0) {
    case 0: playColor = Color(NC::Cyan); break;
    case 1: songListColor = Color(NC::Cyan); break;
    case 2: settingColor = Color(NC::Cyan); break;
    }

    fillBlank(Position(5, 5), Position(15, 60));

    addBlock(Position(5, 5), Position(15,20), {"HP"}, playColor, Font({NF::Bold}));
    addBlock(Position(5, 25), Position(15,40), {"Apple"}, songListColor, Font({NF::Bold}));
    addBlock(Position(5, 45), Position(15,60), {"Alienware"}, settingColor, Font({NF::Bold}));
}

void PlayingWin::updateWin1() {
    Color playColor(NC::White);
    Color songListColor(NC::White);
    Color settingColor(NC::White);
    switch (focus1) {
    case 0: playColor = Color(NC::Cyan); break;
    case 1: songListColor = Color(NC::Cyan); break;
    case 2: settingColor = Color(NC::Cyan); break;
    }

    addBorder(Position(7, 7), Position(19, 64), Color(), '~', '*', '*');
    fillBlank(Position(8, 8), Position(18, 63));

    addBlock(Position(8, 8), Position(18,23), {"New balance"}, playColor, Font({NF::Bold}));
    addBlock(Position(8, 28), Position(18,43), {"Nike"}, songListColor, Font({NF::Bold}));
    addBlock(Position(8, 48), Position(18,63), {"Bilibili"}, settingColor, Font({NF::Bold}));
}

void PlayingWin::updateWin2() {
    Color playColor(NC::White);
    Color songListColor(NC::White);
    Color settingColor(NC::White);
    switch (focus2) {
    case 0: playColor = Color(NC::Cyan); break;
    case 1: songListColor = Color(NC::Cyan); break;
    case 2: settingColor = Color(NC::Cyan); break;
    }

    addBorder(Position(5, 47), Position(15, 76), Color(), '~', '*', '*');
    fillBlank(Position(6, 48), Position(14, 75));

    addBlock(Position(6, 48), Position(8,75), {"Doggggggg"}, playColor, Font({NF::Bold}));
    addBlock(Position(9, 48), Position(11,75), {"kangaroooo"}, songListColor, Font({NF::Bold}));
    addBlock(Position(12, 48), Position(14,75), {"Tangentaaa"}, settingColor, Font({NF::Bold}));
}
