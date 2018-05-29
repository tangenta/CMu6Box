#include "songlist_win.h"
#include "resources.h"
#include "../menu_win.h"
#include "dir_win.h"

static const Position LIST_NAME(4, 4);
static const Position SONG_LIST(4, 20);

Songlist_win::Songlist_win(Resources* res) : Window(res) {
    _initMenus();
}

Songlist_win::Songlist_win(Resources* res, NMenu const& listnames, NMenu const& songlist)
    : Window(res), _listnames(listnames), _songlist(songlist) {}

Songlist_win::~Songlist_win() {}

Window* Songlist_win::handleInput(int ch) {
    if (ch == NK::Down) {
        _listnames.moveDown();
    } else if (ch == NK::Up) {
        _listnames.moveUp();
    } else if (ch == NK::Esc) {
        return new MenuWin(resource);
    } else if (ch == NK::Enter) {
        if (_listnames.getFocusCont() == "..") {
            // add new songlist
            std::string n{"*untitled*"};
            n.insert(9, std::to_string(resource->songlistNames.length()));
            resource->songlistNames.push_front(n.c_str());
            resource->songlists.push_front({});

            _initMenus();
        } else {
            return new Listmenu_win(resource, _listnames, _songlist);
        }
    }
    _fill_list(_listnames.getFocus());
    return this;
}

void Songlist_win::update() {}

void Songlist_win::draw() {
    Window::draw(_listnames, LIST_NAME);
    Window::draw(_songlist, SONG_LIST);
}

void Songlist_win::addSonglist(const QString &name, const QStringList &sl) {
    int idx = resource->songlistNames.indexOf(name);

    if (idx == -1) { // not exists
        resource->songlistNames.push_front(name);
        resource->songlists.push_front(sl);
    } else { // exist
        resource->songlists[idx].append(sl);
    }

    // remove duplicates
    resource->songlists[idx].removeDuplicates();
}

void Songlist_win::replaceSonglist(const QString &name, const QStringList &sl) {
    int idx = resource->songlistNames.indexOf(name);

    if (idx == -1) { // not exists
        resource->songlistNames.push_front(name);
        resource->songlists.push_front(sl);
    } else { // exist
        resource->songlists[idx] = sl;
    }

    // remove duplicates
    resource->songlists[idx].removeDuplicates();
}

void Songlist_win::_initMenus() {
    // TODO: prettify
    _listnames = NMenu(14, 18);
    _songlist = NMenu(20, 18);
    _listnames.setAttr(normal);
    _listnames.setHighlight(highlight);
    _songlist.setAttr(normal);
    _songlist.setHighlight(normal);

    // add songlist names
    for (QString const& s : resource->songlistNames) {
        _listnames.addItem(NText(s.toStdString()));
    }

    // songs of the songlins
    _fill_list(_listnames.getFocus());
}

void Songlist_win::_refreshMenus() {
    _listnames.removeAll();

    // add songlist names
    for (QString const& s : resource->songlistNames) {
        _listnames.addItem(NText(s.toStdString()));
    }

    // songs of the songlins
    _fill_list(_listnames.getFocus());
}

void Songlist_win::_fill_list(int offPos) {
    _songlist.removeAll();
    int i = 0;
    for (QString const& s : resource->songlists.at(offPos)) {
        QUrl u(s);

        // remove suffix and prefix
        std::string n = u.fileName().toStdString();
        std::size_t p = n.find_last_of(".");
        n = n.substr(0, p);
        _songlist.addItem(NText(std::to_string(++i) + ". " + n));
    }
}
