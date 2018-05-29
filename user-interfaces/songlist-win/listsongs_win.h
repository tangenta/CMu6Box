#ifndef SONGS_WIN_H
#define SONGS_WIN_H
#include "listname_win.h"

class Listsongs_win : public Listname_win {
public:
    Listsongs_win(Resources* res, NMenu const& listnames, NMenu const& songlist);
    ~Listsongs_win();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;

private:
    void _initMenusAttr();
};

#endif // SONGS_WIN_H
