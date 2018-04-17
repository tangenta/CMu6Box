#ifndef UTIL_BORDER_H
#define UTIL_BORDER_H

#include "util_position.h"
#include "ncurses_wrapper.h"
#include "util_window.h"
#include <tuple>

class Border
{
public:
    Border(Position const& topLeft,
           int width,
           int height,
           Attr const& attr = Attr(),
           char horizontal = '-',
           char vertical = '|',
           char corner = '+')
        : position(topLeft), width(width), height(height), attribute(attr),
          horizontal(horizontal), vertical(vertical), corner(corner) {

        if (width < 0 || height < 0) {
            throw OutOfRangeError("Border()::overflow");
        }
    }

    void update();
    void draw(Window*);

    // public没什么不好的，相信我
    Position position;
    const int width;
    const int height;
    Attr attribute;
    const char horizontal;
    const char vertical;
    const char corner;
};

#endif // UTIL_BORDER_H
