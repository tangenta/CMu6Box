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
    void update() override;
    void draw() override;

private:
    void drawVolume();
    void drawPlayingIcon();
    Border border;
    Border volumeBorder;
    int volume;
    bool playing;
    std::vector<std::string> playIcon = {" #    ",
                                         " ###  ",
                                         " #### ",
                                         " ###  ",
                                         " #    "};
    std::vector<std::string> pauseIcon ={" # # ",
                                         " # # ",
                                         " # # ",
                                         " # # ",
                                         " # # "};
};

#endif // PLAYING_WIN_H
