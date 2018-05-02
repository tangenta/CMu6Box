#ifndef UTIL_NBORDER_H
#define UTIL_NBORDER_H

#include "ncurse-wrap/ncurses_wrapper.h"

class NBorder
{
public:
    NBorder();
    NBorder(char horizontal, char vertical, char corner, Attr const& attribute = Attr());
    NBorder(int width, int height, char horizontal = ' ',
            char vertical = ' ', char corner = ' ', Attr const& attribute = Attr());
    int getWidth() const;
    int getHeight() const;
    void setAttr(Attr const& attr);

    template <typename Entity>  // Entity must have defined getWidth() and getHeight()
    void fit(Entity const& entity) {
        int wid = entity.getWidth();
        int hight = entity.getHeight();
        if (wid < 0 || hight < 0) {
            throw FatalError("NBorder::fit()");
        }

        width = wid+2;
        height = hight+2;
    }

    Printer toPrinter() const;
private:
    int width;
    int height;
    char vertical;
    char horizontal;
    char corner;
    Attr attribute;
};

#endif // UTIL_NBORDER_H
