#ifndef PLAYING_WIN_H
#define PLAYING_WIN_H
#include "../ncurse-wrap/util_window.h"
#include "../ncurse-wrap/util_rollingtext.h"
#include "../ncurse-wrap/util_statictext.h"
#include "../ncurse-wrap/util_border.h"
#include "../ncurse-wrap/util_text.h"
#include "../ncurse-wrap/util_menu.h"
#include "../ncurse-wrap/block.h"
#include <vector>
#include <memory>
#include <QObject>

class PlayingWin: public Window {
    Q_OBJECT
public:
    PlayingWin();
    ~PlayingWin();
    Window* handleInput(int ch) override;
    void connector(NCController*) override;
    void update() override;
    void draw() override;
signals:
    void play();
    void pause();
private:
    std::shared_ptr<StaticText> text;
    bool playing;
};

#endif // PLAYING_WIN_H
