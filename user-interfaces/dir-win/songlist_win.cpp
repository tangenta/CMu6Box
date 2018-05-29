#include "songlist_win.h"
#include "resources.h"
#include "../menu_win.h"
#include "dir_win.h"
#include "songs_win.h"
#include "../../ncurse-wrap/util_nblock.h"
#include "../../ncurse-wrap/util_nborder.h"

static const Position LIST_NAME(4, 4);
static const Position SONG_LIST(4, 20);
static const std::string DEFAULT{"*add list*"};

Songlist_win::Songlist_win(Resources* res) : Window(res) {
    _initMenus();
}

Songlist_win::Songlist_win(Resources* res, NMenu const& listnames, NMenu const& songlist)
    : Window(res), _listnames(listnames), _songlist(songlist) {
    _initMenusAttr();
}

Songlist_win::~Songlist_win() {}

Window* Songlist_win::handleInput(int ch) {
    if (ch == NK::Down) {
        _listnames.moveDown();
    } else if (ch == NK::Up) {
        _listnames.moveUp();
    } else if (ch == NK::Esc) {
        return new MenuWin(resource);
    } else if (ch == NK::Enter) {
        if (_listnames.getFocusCont() == DEFAULT) {

            // input name
            std::string n = getInput(LIST_NAME.getRow()-1, LIST_NAME.getCol(), 20);

            // if the name is reduplicated or empty, then help generate a new name
            auto i_b = resource->songlistNames.begin();
            auto i_e = resource->songlistNames.end();
            if (n.empty() || std::find(i_b, i_e, n.c_str()) != i_e) {
                int num = resource->songlistNames.length();
                for (;;) {
                    n = std::string("*untitled") + std::to_string(num++) + std::string("*");
                    auto it = std::find(i_b, i_e, n.c_str());
                    if (it == i_e) break;
                }
            }

            resource->songlistNames.push_front(n.c_str());
            resource->songlists.push_front({});

            _initMenus();
        } else {
            return new Listmenu_win(resource, _listnames, _songlist);
        }
    } else if (ch == NK::Right) {
        if (_listnames.getFocusCont() != DEFAULT) {
            return new Songs_win(resource, _listnames, _songlist);
        }
    }

    _fill_list(_listnames.getFocus());
    return this;
}

void Songlist_win::update() {
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        _listnames.update();
    }
}

void Songlist_win::draw() {
    Window::draw(_listnames, LIST_NAME);

    NBorder border(42, 20, ' ', '|', ' ', normal);
    NBlock<NMenu, NBorder> bl(_songlist, border);
    Window::draw(bl, SONG_LIST + Position(-1, 0));

    // title
    Window::draw(NText("> SONGLIST", highlight), LIST_NAME + Position(-2, 1));
    Window::draw(NText("  CONTENT", normal), SONG_LIST + Position(-2, 12));
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
    _songlist = NMenu(40, 18);
    _initMenusAttr();

    // add songlist names
    for (QString const& s : resource->songlistNames) {
        _listnames.addItem(NText(s.toStdString(), normal));
    }

    // songs of the songlins
    _fill_list(_listnames.getFocus());
}

void Songlist_win::_initMenusAttr() {
    _listnames.setAttr(normal);
    _listnames.setHighlight(highlight);
    _songlist.setAttr(normal);
    _songlist.setHighlight(normal);
}

void Songlist_win::_refreshMenus() {
    _listnames.removeAll();

    // add songlist names
    for (QString const& s : resource->songlistNames) {
        _listnames.addItem(NText(s.toStdString(), normal));
    }
    _initMenusAttr();

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
        _songlist.addItem(NText(std::to_string(++i) + ". " + n, normal));
    }
}
