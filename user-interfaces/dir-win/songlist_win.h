#ifndef SONGLIST_WIN_H
#define SONGLIST_WIN_H
#include "../../ncurse-wrap/util_window.h"

class Songlist_win : public Window {
public:
    Songlist_win(Resources* res);
    ~Songlist_win();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;
    void addSonglist(QString const& name, QStringList const& sl);

private:
    NMenu _listName;
    NMenu _songs;
    void _initMenus();
    void _fill_list(int offPos);
};

#endif // SONGLIST_WIN_H
