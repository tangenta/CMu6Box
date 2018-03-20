#ifndef TEXT_H
#define TEXT_H
#include "position.h"
#include "constants.h"
#include <string>

class Text {
public:
    Text() = delete;
    Text(std::string const& text, Position pos, int size,
         Color color, Font font, AlignMode mode);

    // getter
    int getRow() { return ipos.getRow(); }
    int getCol() { return ipos.getCol(); }
    std::string getText() { return itext; }
    int getSize() { return isize; }
    Color getColor() { return icolor; }
    Font getFont() { return ifont; }
    AlignMode getAlignMode() { return imode; }

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
    Color icolor;
    int isize;
    Font ifont;
    AlignMode imode;
};

#endif // TEXT_H
