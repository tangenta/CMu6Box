#ifndef SONGLIST_WIN_H
#define SONGLIST_WIN_H
#include "../../ncurse-wrap/util_window.h"

class Listname_win : public Window {
public:
    Listname_win(Resources* res);
    Listname_win(Resources* res, NMenu const& listnames, NMenu const& songlist);
    ~Listname_win();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;

    void addSonglist(QString const& name, QStringList const& sl);
    void replaceSonglist(QString const& name, QStringList const& sl);

protected:
    NMenu _listnames;
    NMenu _songlist;
    void _refreshMenus();

private:
    void _fill_list(int offPos);
    void _initMenus();
    void _initMenusAttr();
};

#endif // SONGLIST_WIN_H
