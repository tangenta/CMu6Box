#include "songlist_win.h"
#include "resources.h"
#include "../menu_win.h"
#include "dir_win.h"

static const Position _listNameP(4, 4);
static const Position _songsP(4, 20);

Songlist_win::Songlist_win(Resources* res) : Window(res) {
    _initMenus();
}

Songlist_win::~Songlist_win() {}

Window* Songlist_win::handleInput(int ch) {
    if (ch == NK::Down) {
        _listName.moveDown();
    } else if (ch == NK::Up) {
        _listName.moveUp();
    } else if (ch == NK::Esc) {
        return new MenuWin(resource);
    } else if (ch == NK::Enter) {
        if (_listName.getFocusCont() == "..") {
            return new Dir_win(resource);
        }
    }
    _fill_list(_listName.getFocus());
    return this;
}

void Songlist_win::update() {}

void Songlist_win::draw() {
    Window::draw(_listName, _listNameP);
    Window::draw(_songs, _songsP);
}

void Songlist_win::addSonglist(const QString &name, const QStringList &sl) {
    resource->songlistNames.push_front(name);
    resource->songlists.push_front(sl);
}

void Songlist_win::_initMenus() {
    _listName = NMenu(20, 20);
    _songs = NMenu(20, 20);
    _listName.setAttr(normal);
    _listName.setHighlight(highlight);
    _songs.setAttr(normal);
    _songs.setHighlight(normal);

    for (QString const& s : resource->songlistNames) {
        _listName.addItem(NText(s.toStdString()));
    }
    _fill_list(_listName.getFocus());
}

void Songlist_win::_fill_list(int offPos) {
    _songs.removeAll();
    int i = 0;
    for (QString const& s : resource->songlists.at(offPos)) {
        QUrl u(s);
        std::string n = u.fileName().toStdString();
        std::size_t p = n.find_last_of(".");
        n = n.substr(0, p);
        _songs.addItem(NText(std::to_string(++i) + ". " + n));
    }
}
