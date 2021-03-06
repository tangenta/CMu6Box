#include "listsongs_win.h"
#include "../menu_win.h"
#include "songedit_win.h"

Listsongs_win::Listsongs_win(Resources* res, NMenu const& listnames, NMenu const& songlist)
    : Listname_win(res, listnames, songlist) {
    _initMenusAttr();
}

Listsongs_win::~Listsongs_win() {}

Window* Listsongs_win::handleInput(int ch) {
    if (ch == NK::Down) {
        _songlist.moveDown();
    } else if (ch == NK::Up) {
        _songlist.moveUp();
    } else if (ch == NK::Left) {
        return new Listname_win(resource, _listnames, _songlist);
    } else if (ch == NK::Esc) {
        return new MenuWin(resource);
    } else if (ch == NK::Enter) {
        return new SongEditWin(resource, _listnames, _songlist);
    }
    return this;
}

void Listsongs_win::update() {
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        _songlist.update();
    }
}
void Listsongs_win::draw() {
    Listname_win::draw();

    // title
    static const Position LIST_NAME(4, 4);
    static const Position SONG_LIST(4, 20);
    Window::draw(NText(std::string("  ") + tl("SONGLIST"), normal), LIST_NAME + Position(-2, 1));
    Window::draw(NText(std::string("> ") + tl("CONTENT"), highlight), SONG_LIST + Position(-2, 12));
    Window::draw(NText(tl(std::string("available key")) + ": ← ↑ ↓ Enter Esc", normal), Position(23, 1));
}

void Listsongs_win::_initMenusAttr() {
    _songlist.setAttr(normal);
    _songlist.setHighlight(highlight);
}
