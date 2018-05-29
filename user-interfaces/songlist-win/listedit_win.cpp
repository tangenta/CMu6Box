#include "listedit_win.h"
#include "resources.h"
#include "dir_win.h"
#include "../../ncurse-wrap/util_nblock.h"
#include "../../ncurse-wrap/util_nborder.h"

static const Position LIST_NAME(4, 4);

static const std::string OP0 = "add to playinglist";
static const std::string OP1 = "replace playinglist";
static const std::string OP2 = "add directory";
static const std::string OP3 = "replace directory";
static const std::string OP4 = "rename list";
static const std::string OP5 = "remove songlist";

Listedit_win::Listedit_win(Resources* res, NMenu const& listnames, NMenu const& songlist)
    : Listname_win(res, listnames, songlist) {
    _initMenu();
}

Listedit_win::~Listedit_win() {}

Window* Listedit_win::handleInput(int ch) {
    if (ch == NK::Down) {
        _menu.moveDown();
    } else if (ch == NK::Up) {
        _menu.moveUp();
    } else if (ch == NK::Enter) {
        if (_menu.getFocusCont() == OP0) {
            resource->playingList.append(resource->songlists[_listnames.getFocus()]);
            // remove duplicates
            resource->playingList.removeDuplicates();

            // refresh playinglist
            resource->refreshPlayinglist();
            return new Listname_win(resource, _listnames, _songlist);

        } else if (_menu.getFocusCont() == OP1) {
            resource->playingList.clear();
            resource->playingList.append(resource->songlists[_listnames.getFocus()]);
            // remove duplicates
            resource->playingList.removeDuplicates();

            // refresh playinglist
            resource->refreshPlayinglist();
            return new Listname_win(resource, _listnames, _songlist);

        } else if (_menu.getFocusCont() == OP2) {
            return new Dir_win(resource, _listnames, _songlist, Op::ADD_SONGLIST);

        } else if (_menu.getFocusCont() == OP3) {
            return new Dir_win(resource, _listnames, _songlist, Op::REPLACE_SONGLIST);

        } else if (_menu.getFocusCont() == OP4) {
            // input name
            std::string n = getInput(LIST_NAME.getRow()-1, LIST_NAME.getCol(), 20);

            // if the name is not reduplicated or empty, then rename
            if (!n.empty() && !resource->songlistNames.contains(n.c_str())) {
                resource->songlistNames.replace(_listnames.getFocus(), n.c_str());
                Listname_win::_refreshMenus();
            }
            return new Listname_win(resource, _listnames, _songlist);

        } else if (_menu.getFocusCont() == OP5) {
            resource->songlistNames.removeAt(_listnames.getFocus());
            resource->songlists.removeAt(_listnames.getFocus());
            Listname_win::_refreshMenus();
            return new Listname_win(resource, _listnames, _songlist);

        }
    } else if (ch == NK::Esc) {
        return new Listname_win(resource, _listnames, _songlist);
    }
    return this;
}

void Listedit_win::update() {
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        _menu.update();
    }
}

void Listedit_win::draw() {
    Listname_win::draw();

    // 12 = !10! + 2, 6 = !4! + 2
    NBorder border(20, 6, '-', '|', '+', normal);
    NBlock<NMenu, NBorder> bl(_menu, border);
    Window::draw(bl,
                 LIST_NAME + Position(_listnames.getFocus()-2, 12));
}

void Listedit_win::_initMenu() {
    // TODO: prettify
    _menu = NMenu(18, 4);
    _menu.setAttr(normal);
    _menu.setHighlight(highlight);

    _menu.addItem(NText(OP0, normal));
    _menu.addItem(NText(OP1, normal));
    _menu.addItem(NText(OP2, normal));
    _menu.addItem(NText(OP3, normal));
    _menu.addItem(NText(OP4, normal));
    _menu.addItem(NText(OP5, normal));
}
