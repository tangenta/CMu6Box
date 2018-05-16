#include "test2_win.h"
#include "user-interfaces/menu_win.h"

static std::initializer_list<std::string> menuList = {
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

Test2Win::Test2Win(Resources* res): Window(res), focus(0), subMenu(nullptr) {
    NText play("play"), songList("song list"), setting("setting");
    NBorder border(15, 10, '-', '|', '+');

    playBlock = Test2Block(play, border, true, true);
    songListBlock = Test2Block(songList, border, true, true);
    settingBlock = Test2Block(setting, border, true, true);
}

NMenu* Test2Win::initRollingMenu() {
    NMenu* menu = new NMenu(30, 10);
    menu->setHighlight(Attr(Color(NC::Cyan), Font({NF::Bold})));
    for (auto& i: menuList) {
        menu->addItem(NText(i));
    }
    return menu;
}

/* ============ window's input handlers ============== */

Window* Test2Win::handleInput(int ch) {
    return (subMenu == nullptr) ? mainInputHandler(ch) : subInputHandler(ch);
}

Window* Test2Win::mainInputHandler(int ch) {
    if (ch == NK::Left) {
        focus = (focus == 0) ? 2 : focus-1;
    } else if (ch == NK::Right) {
        focus = (focus == 2) ? 0 : focus+1;
    } else if (ch == NK::Esc) {
        return new MenuWin(resource);
    } else if (ch == NK::Enter) {
        subMenu = initRollingMenu();
    }
    return this;
}

Window* Test2Win::subInputHandler(int ch) {
    if (ch == NK::Up) {
        subMenu->moveUp();
    } else if (ch == NK::Down) {
        subMenu->moveDown();
    } else if (ch == NK::Esc) {
        delete subMenu;
        clearScreen();
        subMenu = nullptr;
    }
    return this;
}


void Test2Win::update() {
    playBlock.setAttr(defaultAttr);
    songListBlock.setAttr(defaultAttr);
    settingBlock.setAttr(defaultAttr);
    Test2Block* blockToChange;
    switch (focus) {
    case 0: blockToChange = &playBlock; break;
    case 1: blockToChange = &songListBlock; break;
    case 2: blockToChange = &settingBlock; break;
    default: throw FatalError("Test2Win::update()");
    }
    blockToChange->setAttr(Attr(Color(NC::Cyan), Font({NF::Bold})));

    if (!subMenu) return;
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        subMenu->update();
    }

}

void Test2Win::draw() {
    Window::draw(playBlock, Position(5, 5));
    Window::draw(songListBlock, Position(5, 25));
    Window::draw(settingBlock, Position(5, 45));
    if (subMenu) {
        NBorder border(NBorder('-', '|', '+'));
        border.fit(*subMenu);
        Window::draw(Test2Menu(*subMenu, border), Position(5, 5));
    }
}
