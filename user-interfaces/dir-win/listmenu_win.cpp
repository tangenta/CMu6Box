#include "listmenu_win.h"
#include "resources.h"
#include "dir_win.h"
#include "../../ncurse-wrap/util_nblock.h"
#include "../../ncurse-wrap/util_nborder.h"

static const Position LIST_NAME(4, 4);

static const std::string OP1 = "add directory";
static const std::string OP2 = "replace directory";
static const std::string OP3 = "remove songlist";

Listmenu_win::Listmenu_win(Resources* res, NMenu const& listnames, NMenu const& songlist)
    : Songlist_win(res, listnames, songlist) {
    _initMenu();
}

Listmenu_win::~Listmenu_win() {}

Window* Listmenu_win::handleInput(int ch) {
    if (ch == NK::Down) {
        _menu.moveDown();
    } else if (ch == NK::Up) {
        _menu.moveUp();
    } else if (ch == NK::Enter) {
        if (_menu.getFocusCont() == OP1) {
            return new Dir_win(resource, _listnames, _songlist, Op::ADD_SONGLIST);
        } else if (_menu.getFocusCont() == OP2) {
            return new Dir_win(resource, _listnames, _songlist, Op::REPLACE_SONGLIST);
        } else if (_menu.getFocusCont() == OP3) {
            resource->songlistNames.removeAt(_listnames.getFocus());
            resource->songlists.removeAt(_listnames.getFocus());
            Songlist_win::_refreshMenus();
            return new Songlist_win(resource, _listnames, _songlist);
        }
    } else if (ch == NK::Esc) {
        return new Songlist_win(resource, _listnames, _songlist);
    }
    return this;
}

void Listmenu_win::update() {
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        _menu.update();
    }
}

void Listmenu_win::draw() {
    Songlist_win::draw();

    // 12 = !10! + 2, 6 = !4! + 2
    NBorder border(20, 6, '-', '|', '+');
    NBlock<NMenu, NBorder> bl(_menu, border);
    Window::draw(bl,
                 LIST_NAME + Position(_listnames.getFocus()-2, 12));
}

void Listmenu_win::_initMenu() {
    // TODO: prettify
    _menu = NMenu(18, 4);
    _menu.setAttr(normal);
    _menu.setHighlight(highlight);
    _menu.addItem(OP1);
    _menu.addItem(OP2);
    _menu.addItem(OP3);
}
