#include "util_nborder.h"
#include "ncurse-wrap/exceptions.h"

NBorder::NBorder(): width(0), height(0), vertical(' '), horizontal(' '),
    corner(' '), attribute(Attr()) {}

NBorder::NBorder(char horizontal, char vertical, char corner, Attr const& attribute)
    : width(0), height(0), vertical(vertical), horizontal(horizontal), corner (corner),
      attribute(attribute) {}

NBorder::NBorder(int width, int height, char horizontal, char vertical, char corner,
                 Attr const& attribute)
    : width(width), height(height), vertical(vertical), horizontal(horizontal), corner (corner),
      attribute(attribute) {
    if (width < 0 || height < 0) {
        throw FatalError("NBorder::NBorder()");
    }
}

int NBorder::getWidth() const {
    return width;
}

int NBorder::getHeight() const {
    return height;
}

void NBorder::setAttr(Attr const& attr) {
    attribute = attr;
}

Printer NBorder::toPrinter() const {
    Printer printer;
    if (width <= 1 || height <= 1) {
        return printer;
    }
    std::string boundary(2, corner);    // "++"
    boundary.insert(1, std::string(width-2, horizontal));   // "+--...--+"
    std::string body(2, vertical);  // "||"
    body.insert(1, std::string(width-2,' '));   // "|  ...  |"

    printer.insert(printer.end(), Printee(boundary, attribute, Bias(1,0)));
    printer.insert(printer.end(), height-2, Printee(body, attribute, Bias(1,0)));
    printer.insert(printer.end(), Printee(boundary, attribute, Bias(-height+1, 0)));

    return printer;
}
