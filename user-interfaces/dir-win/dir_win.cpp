#include "dir_win.h"
#include "../menu_win.h"

static int _col = 4;
static int _row = 4;
static int _width = 20;
static int _height = 18;

static const Position _preP(_row, _col);
static const Position _curP(_row, _col + _width + 4);
static const Position _nextP(_row, _col + _width * 2 + 8);

Dir_win::Dir_win(Resources* res) : Songlist_win(res) {
    _dir = QDir::home();
    _dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    _pre = NMenu(_width, _height);
    _cur = NMenu(_width, _height);
    _next = NMenu(_width, _height);
    _fill_pre();
    _fill_cur();
    _fill_next();
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
            _pre = _cur;
            _fill_cur();
        }
        else {
            _dir.cd(can);
        }
    } else if (ch == NK::Left) {
        if (_dir.cdUp()) {
            _cur = _pre;
            _fill_pre();
        }
    } else if (ch == NK::Esc) {
        return new Songlist_win(resource);

    } else if (ch == NK::Enter) {
        if (_dir.cd(_cur.getFocusCont().c_str())) {
            QFileInfoList ls = _dir.entryInfoList((QStringList() << "*.mp3" << "*.flac"), QDir::Files);
            QStringList sl;
            for (const QFileInfo &fi : ls) {
                sl.push_back(fi.canonicalFilePath());
            }
            this->Songlist_win::addSonglist("list1", sl);
        }

        return new Songlist_win(resource);
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
    Window::draw(NText("PREVIOUS"), _preP + Position(-2, (_width - 8) / 2));
    Window::draw(NText("CURRENT"), _curP + Position(-2, (_width - 7) / 2));
    Window::draw(NText("NEXT"), _nextP + Position(-2, (_width - 4) / 2));
    _initMenuAttr();
    Window::draw(_pre, _preP);
    Window::draw(_cur, _curP);
    Window::draw(_next, _nextP);
}

void Dir_win::_fill_cur() {
    _cur.removeAll();
    QStringList ds = _dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    ds.append(_dir.entryList((QStringList() << "*.mp3" << "*.flac"), QDir::Files));
    for (const QString &f : ds) {
        _cur.addItem(NText(f.toStdString()));
    }
}

void Dir_win::_fill_pre() {
    _pre.removeAll();
    QString can = _dir.canonicalPath();
    if (_dir.cdUp()) {
        QStringList ds = _dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        ds.append(_dir.entryList((QStringList() << "*.mp3" << "*.flac"), QDir::Files));
        for (const QString &f : ds) {
            _pre.addItem(NText(f.toStdString()));
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
            _next.addItem(NText(f.toStdString()));
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


