#ifndef UTIL_TEXT_H
#define UTIL_TEXT_H

#include "util_position.h"
#include "ncurses_wrapper.h"
#include "util_window.h"
#include <algorithm>

class Text {
public:
    Text(std::string const& cont,
         Position const& pos,
         int width,
         Attr const& attr)
        : content(cont), position(pos), attribute(attr), width(width), height(1) {

        if (width < 0) {
            throw OutOfRangeError("Text()::overflow");
        }
        static std::string const invalidEscapeChars = "\a\n\b\f\r\t\v\e";
        for (auto i: cont) {
            if (std::count(invalidEscapeChars.begin(),
                           invalidEscapeChars.end(), i) > 0) {
                throw InvalidError("MovingText()::multilines");
            }
        }
    }

    virtual ~Text() {}
    virtual void update() = 0;
    virtual void draw(Window*) = 0;

    std::string content;
    Position position;
    Attr attribute;
    const int width;
    const int height;
};

#endif // UTIL_TEXT_H
