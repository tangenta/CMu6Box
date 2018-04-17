#ifndef UTIL_MENU_H
#define UTIL_MENU_H

#include <initializer_list>
#include <vector>
#include "util_position.h"
#include "util_window.h"
#include "util_rollingtext.h"

class Menu
{
public:
    Menu(std::initializer_list<std::string> strList,
         const Position &pos,
         int width,
         int height,
         const Attr &hl = Attr(Color(NC::Cyan), Font({NF::Bold})),
         const Attr &other = Attr());

    void up();
    void down();
    void draw(Window*);
    void update();

    // public没什么不好的，相信我
    Position position;
    const int width;
    const int height;
    const Attr highlight;
    const Attr other;

private:
    int focus;
    int item;

    const int itemLength;
    std::vector<RollingText> texts;

    // 整体向上向下移动，所以有可能会移出屏幕，但不显示
    void rollUp();
    void rollDown();
};

#endif // UTIL_MENU_H
