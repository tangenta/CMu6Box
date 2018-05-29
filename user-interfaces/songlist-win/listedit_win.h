#ifndef LISTMENU_WIN_H
#define LISTMENU_WIN_H

#include "listname_win.h"

class Listedit_win : public Listname_win {
public:
    Listedit_win(Resources* res, NMenu const& listnames, NMenu const& songlist);
    ~Listedit_win();
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
