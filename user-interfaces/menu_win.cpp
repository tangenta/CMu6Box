#include "menu_win.h"
#include "../ncurse-wrap/ncurses_wrapper.h"
#include "playing_win.h"
#include "setting_win.h"
#include "testing_win.h"
#include "test2_win.h"
#include "../resources.h"
#include "../ncurse-wrap/util_dialog.h"
#include <QFile>
#include <QTextStream>

MenuWin::MenuWin(Resources* res) : Window(res), focus(0), msg(nullptr) {
    try {
        resource->setting.openSetting();
    } catch (JsonOpenError const& e) {
        // setting.json is not found
        QFile file("setting.json");
        if (!file.open(QIODevice::WriteOnly)) {
            throw FatalError("unable to create setting.json");
        }
        QTextStream out(&file);
        out << "{\"theme\":\"default\",\n\"language\":\"english\"}";
        file.close();
        Dialog dialog = Dialog("setting.json is not found in current"
                               " directory, creating one...", 20, 5);
        NBorder bord('-', '|', '+');
        bord.fit(dialog);
        msg = new NBlock<Dialog, NBorder>(dialog, bord);
    }

    try {
        resource->setting.loadLanguage(resource->setting.getLanguage());
    } catch (JsonOpenError const& e) {
        // depress complaint with missing "./locale/xxx.json"
    }

    setBackground(resource->setting.getTheme());
}

MenuWin::~MenuWin() {
    if (msg) {
        delete msg;
        msg = nullptr;
    }
}

Window* MenuWin::handleInput(int ch) {
    if (msg) return msgHandleInput(ch);
    if (ch == NK::Left) {
        if (--focus < 0)
            focus += 3;
        return this;

    } else if (ch == NK::Right) {
        focus = (focus + 1) % 3;
        return this;    

    } else if (ch == NK::Enter) {
        if (focus == 0) {
            return new PlayingWin(resource);
        } else if (focus == 2) {
            return new SettingWin(resource);
        } else {
            return this;
        }

    } else if (ch == NK::Esc) {
        return nullptr;

    } else {
        return this;
    }

    
}

void MenuWin::update() {}

void MenuWin::draw() {
    std::vector<NText> vec = {NText("Play"), NText("Song List"), NText("Setting")};
    std::vector<Position> pos = {Position(5, 5), Position(5, 30), Position(5, 55)};
    NBorder border(20, 10, '-', '|', '+');
    for (int i = 0; i != static_cast<int>(vec.size()); ++i) {
        NBlock<NText, NBorder> block(vec[i], border, true, true);
        Attr attr = i == focus ? Attr(Color(NC::Cyan), Font({NF::Bold})) :
                                 Attr(Color(NC::White), Font({NF::Bold}));
        block.setAttr(attr);
        Window::draw(block, pos[i]);
    }
    if (msg) Window::draw(*msg, Position(16, 29));
}

Window* MenuWin::msgHandleInput(int ch) {
    if (ch == NK::Enter || ch == NK::Esc) {
        delete msg;
        msg = nullptr;
        clearScreen();
    }
    return this;
}
