#include "dir_win.h"
#include "../menu_win.h"
#include "../../ncurse-wrap/util_nblock.h"
#include "../../ncurse-wrap/util_nborder.h"

static const Position _preP(5, 4);
static const Position _curP(2, 20);
static const Position _nextP(5, 60);

Dir_win::Dir_win(Resources* res, NMenu const& listnames, NMenu const& songlist, Op const& op)
    : Listedit_win(res, listnames, songlist), _op(op) {
    _initDir();
    _initMenus();
}

void Dir_win::_initDir() {
    _dir = QDir::home();
    _dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
}

void Dir_win::_initMenus() {
    // pre and next are smaller and thinner
    _pre = NMenu(10, 12);
    _cur = NMenu(24, 18);
    _next = NMenu(10, 12);
    _fill_pre();
    _fill_cur();
    _fill_next();
    _initMenuAttr();
}

Dir_win::~Dir_win() {}

Window* Dir_win::handleInput(int ch) {
    if (ch == NK::Up) {
        _cur.moveUp();
    } else if (ch == NK::Down) {
        _cur.moveDown();
    } else if (ch == NK::Right) {
        QString can = _dir.canonicalPath();
        if (_cur.getFocusCont() == "") {
            _dir.cd(can);
        } else if (_dir.cd(_cur.getFocusCont().c_str())) {
            _fill_pre();
            _fill_cur();
        }
        else {
            _dir.cd(can);
        }
    } else if (ch == NK::Left) {
        if (_dir.cdUp()) {
            _fill_cur();
            _fill_pre();
        }
    } else if (ch == NK::Esc) {
        return new Listname_win(resource, _listnames, _songlist);
    } else if (ch == NK::Enter) {

        if (_dir.cd(_cur.getFocusCont().c_str())) {

            // get all audio files
            QFileInfoList ls = _dir.entryInfoList((QStringList() << "*.mp3" << "*.flac"), QDir::Files);
            QStringList sl;
            for (const QFileInfo &fi : ls) {
                sl.push_back(fi.canonicalFilePath());
            }

            // match operation, add or replace
            switch (_op) {
            case Op::ADD_SONGLIST:
                Listname_win::addSonglist(_listnames.getFocusCont().c_str(), sl);
                break;
            case Op::REPLACE_SONGLIST:
                Listname_win::replaceSonglist(_listnames.getFocusCont().c_str(), sl);
                break;
            }

            Listname_win::_refreshMenus();
        }

        return new Listname_win(resource, _listnames, _songlist);
    }
    _fill_next();
    return this;
}

void Dir_win::update() {
    static int counter = 0;
    if (counter++ == 20) {
        counter = 0;
        _cur.update();
    }
}

void Dir_win::draw() {
    Window::draw(NText("PREVIOUS", normal), _preP + Position(-2, 2));
    Window::draw(NText("CURRENT", normal), _curP + Position(-1, 14));
    Window::draw(NText("NEXT", normal), _nextP + Position(-2, 4));
    _initMenuAttr();
    Window::draw(_pre, _preP);
    Window::draw(_next, _nextP);

    NBorder border(36, 20, ' ', '|', ' ', normal);
    NBlock<NMenu, NBorder> bl(_cur, border, true, true);
    Window::draw(bl, _curP);
}

void Dir_win::_fill_cur() {
    _cur.removeAll();
    QStringList ds = _dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    ds.append(_dir.entryList((QStringList() << "*.mp3" << "*.flac"), QDir::Files));
    for (const QString &f : ds) {
        _cur.addItem(NText(f.toStdString(), normal));
    }
}

void Dir_win::_fill_pre() {
    _pre.removeAll();
    QString can = _dir.canonicalPath();
    if (_dir.cdUp()) {
        QStringList ds = _dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        ds.append(_dir.entryList((QStringList() << "*.mp3" << "*.flac"), QDir::Files));
        for (const QString &f : ds) {
            _pre.addItem(NText(f.toStdString(), normal));
        }
    }
    _dir.cd(can);
}

void Dir_win::_fill_next() {
    _next.removeAll();
    QString can = _dir.canonicalPath();
    if (_dir.cd(_cur.getFocusCont().c_str())) {
        QStringList ds = _dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        ds.append(_dir.entryList((QStringList() << "*.mp3" << "*.flac"), QDir::Files));
        for (const QString &f : ds) {
            _next.addItem(NText(f.toStdString(), normal));
        }
    }
    _dir.cd(can);
}

void Dir_win::_initMenuAttr() {
    _pre.setAttr(normal);
    _pre.setHighlight(normal);
    _cur.setAttr(normal);
    _cur.setHighlight(highlight);
    _next.setAttr(normal);
    _next.setHighlight(normal);
}


