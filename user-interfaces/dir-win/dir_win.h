#ifndef DIR_WIN_H
#define DIR_WIN_H
#include <QDir>
#include "../../ncurse-wrap/util_window.h"
#include "songlist_win.h"

class Dir_win: public Songlist_win {
public:
    Dir_win(Resources* res);
    ~Dir_win();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;

private:
    QDir _dir;
    NMenu _pre;
    NMenu _cur;
    NMenu _next;
    void _fill_pre();
    void _fill_cur();
    void _fill_next();
    void _initMenuAttr();
};

#endif // DIR_WIN_H
