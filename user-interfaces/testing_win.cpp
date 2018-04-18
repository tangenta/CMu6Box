#include "testing_win.h"
#include "menu_win.h"
#include "../ncurse-wrap/util_rollingtext.h"
#include "../ncurse-wrap/util_statictext.h"
#include "../ncurse-wrap/util_border.h"
#include "../ncurse-wrap/ncurses_wrapper.h"
#include "../ncurse-wrap/util_menu.h"
#include <algorithm>
#include <string>

TestingWin::TestingWin() {
    subwin = 0;
    initSubwin0();
    initSubwin1();
}


Window* TestingWin::handleInput(int ch) {
    switch (subwin) {
    case 0:
        return handleInputSubwin0(ch);
        break;
    case 1:
        return handleInputSubwin1(ch);
        break;
    default:
        return this;
        break;
    }
}

void TestingWin::update() {
    // 如果子窗口不用显示，就不需要动了
    switch (subwin) {
    case 0:
        updateSubwin0();
        break;
    case 1:
        updateSubwin0();
        updateSubwin1();
        break;
    }
}
void TestingWin::draw() {
    // 如果子窗口不用显示，就不需要渲染了
    this->clearScreen();
    switch (subwin) {
    case 0:
        drawSubwin0();
        break;
    case 1:
        drawSubwin0();
        drawSubwin1();
        break;
    }
}

// 0号子窗口的子函数
void TestingWin::initSubwin0() {
    focusSubwin0 = 0;

    auto list = {
        Block<Border, StaticText>(Border(Position(5, 5), 15, 10),
                                  StaticText(std::string("HP"), Position(9, 6), 13, Attr(), AlignMode::Center)),
        Block<Border, StaticText>(Border(Position(5, 25), 15, 10),
                                  StaticText(std::string("Apple"), Position(9, 26), 13, Attr(), AlignMode::Center)),
        Block<Border, StaticText>(Border(Position(5, 45), 15, 10),
                                  StaticText(std::string("Alienware"), Position(9, 46), 13, Attr(), AlignMode::Center))
    };
    objSubwin0 = std::make_shared<std::vector<Block<Border, StaticText>>>(list);
}

Window* TestingWin::handleInputSubwin0(int ch) {
    if (ch == NK::Left) {
        if (--focusSubwin0 < 0) focusSubwin0 += 3;
        return this;

    } else if (ch == NK::Right) {
        focusSubwin0 = (focusSubwin0 + 1) % 3;
        return this;

    } else if (ch == NK::Esc) {
        return new MenuWin;

    } else if (ch == NK::Enter) {
        subwin = 1;
        return this;

    } else {
        return this;
    }
}

void TestingWin::drawSubwin0() {
    static Attr hl = Attr(Color(NC::Cyan), Font({NF::Bold}));
    static Attr other = Attr();

    for (int i = 0; i < objSubwin0->size(); ++i) {
        if (i == focusSubwin0) {
            objSubwin0->at(i).content.attribute = hl;
            objSubwin0->at(i).border.attribute = hl;
            objSubwin0->at(i).draw(this);
        } else {
            objSubwin0->at(i).content.attribute = other;
            objSubwin0->at(i).border.attribute = other;
            objSubwin0->at(i).draw(this);
        }
    }
}

void TestingWin::updateSubwin0() {}














// 1号子窗口的子函数
void TestingWin::initSubwin1() {
    focusSubwin1 = 0;

    std::initializer_list<std::string> menuList = {
                     "1. Despacito",
                     "2. Shape of You",
                     "3. Swish Swish",
                     "4. John Wayne",
                     "5. 24K Magic",
                     "6. Naughty Girl",
                     "7. Side to Side",
                     "8. Keep On Moving",
                     "9. Luis Fonsi & Daddy Yankee - Despacito",
                     "10. Ed Sheeran - Shape of You",
                     "11. Katy Perry ft. Nicki Minaj - Swish Swish",
                     "12. Lady Gaga - John Wayne",
                     "13. Bruno Mars - 24K Magic",
                     "14. Beyonce - Naughty Girl",
                     "15. Ariana Grande ft. Nicki Minaj - Side to Side",
                     "16. Michelle Delamor - Keep On Moving"
    };

    objSubwin1 = std::make_shared<Block<Border, Block<Border, Menu>>>(
                Border(Position(1, 49), 30, 22),
                Block<Border, Menu>(Border(Position(2, 50), 28, 20, Attr(), '#', '#', '#'),
                                    Menu(menuList, Position(4, 52), 24, 14))
                );
}

Window* TestingWin::handleInputSubwin1(int ch) {
    if (ch == NK::Down) {
        if (focusSubwin1 < 15) {
            focusSubwin1++;
            objSubwin1->content.content.down();
        }
        return this;

    } else if (ch == NK::Up) {
        if (focusSubwin1 > 0) {
            focusSubwin1--;
            objSubwin1->content.content.up();
        }
        return this;

    } else if (ch == NK::Esc) {
        subwin = 0;
        return this;

    } else {
        return this;
    }
}

void TestingWin::updateSubwin1() {
    // menu刷新速率和帧率差20倍
    static int count = 0;
    count = (count + 1) % 20;
    if (count == 0)
        objSubwin1->update();
}

void TestingWin::drawSubwin1() {
    this->fillBlank(Position(3, 51), Position(20, 76));
    objSubwin1->draw(this);
}
