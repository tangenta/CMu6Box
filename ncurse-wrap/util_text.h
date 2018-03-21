#ifndef UTIL_TEXT_H
#define UTIL_TEXT_H

#include "uitl_position.h"
#include "ncurses_wrapper.h"
#include <string>

class Text {
public:
    Text() = delete;
    Text(std::string const& text, Position pos, int size,
         Color color, Font font, AlignMode mode);

    // getter
    int getRow() const { return ipos.getRow(); }
    int getCol() const { return ipos.getCol(); }
    std::string getText() const { return itext; }
    int getSize() const { return isize; }
    Color getColor() const { return icolor; }
    Font getFont() const { return ifont; }
    AlignMode getAlignMode() const { return imode; }

    // setter
    void setRow(int r) { ipos = Position(r, ipos.getCol()); }
    void setCol(int c) { ipos = Position(ipos.getRow(), c); }
    void setText(std::string const str) {
        if (str.size() > static_cast<size_t>(isize)) {
            throw OutOfRangeError("setText()");
        }
        itext.assign(str);
    }
    void setSize(int size) {
        if (itext.size() > static_cast<size_t>(isize)) {
            throw OutOfRangeError("setSize");
        }
        isize = size;
    }

    void setColor(Color c) { icolor = c; }
    void setFont(Font f) { ifont = f; }
    void setAlignMode(AlignMode am) { imode = am; }

private:
    std::string itext;
    Position ipos;
    int isize;
    Color icolor;
    Font ifont;
    AlignMode imode;
};

#endif // TEXT_H
