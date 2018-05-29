#ifndef DIR_WIN_H
#define DIR_WIN_H
#include <QDir>
#include "../../ncurse-wrap/util_window.h"
#include "songlist_win.h"
#include "listmenu_win.h"

class Dir_win: public Listmenu_win {
public:
    Dir_win(Resources* res, NMenu const& listnames, NMenu const& songlist, Op const& op);
    ~Dir_win();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;

private:
    QDir _dir;
    void _initDir();

    NMenu _pre;
    NMenu _cur;
    NMenu _next;
    void _fill_pre();
    void _fill_cur();
    void _fill_next();

    void _initMenus();
    void _initMenuAttr();

    Op _op;
};

#endif // DIR_WIN_H
