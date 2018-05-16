#ifndef UTIL_DIALOG_H
#define UTIL_DIALOG_H
#include <string>
#include "ncurses_wrapper.h"

class Dialog
{
public:
    Dialog();
    Dialog(std::string const& str, int width, int height, Attr const& attr = Attr());
    Printer toPrinter() const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    std::string content;
    int width;
    int height;
    Attr attr;
};

#endif // UTIL_DIALOG_H
