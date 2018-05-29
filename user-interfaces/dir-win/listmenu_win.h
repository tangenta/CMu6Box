#ifndef LISTMENU_WIN_H
#define LISTMENU_WIN_H

#include "songlist_win.h"

class Listmenu_win : public Songlist_win {
public:
    Listmenu_win(Resources* res, NMenu const& listnames, NMenu const& songlist);
    ~Listmenu_win();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;

protected:
    enum class Op {
      ADD_SONGLIST,
      REPLACE_SONGLIST
    };

private:
    void _initMenu();
    NMenu _menu;
};

#endif // LISTMENU_WIN_H
