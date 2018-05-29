#include "util_ntext.h"
#include "ncurse-wrap/exceptions.h"
#include <algorithm>

NText::NText(): beginPoint(0), width(0) {}

NText::NText(std::string const& content, Attr const& attribute)
    : content(content), attribute(attribute), beginPoint(0), width(content.size()) {
    static std::string const invalidEscapeChars = "\a\n\b\f\r\t\v\e";
    for (auto i: content) {
        if (std::count(invalidEscapeChars.begin(),
                       invalidEscapeChars.end(), i) > 0) {
            throw InvalidError("MovingText()::multilines");
        }
    }
}


std::string NText::getContent() const {
    return content;
}

int NText::getBeginPoint() const {
    return beginPoint;
}

int NText::getHeight() const {
    return 1;
}

int NText::getWidth() const {
    return width;
}

void NText::setWidth(int wid) {
    beginPoint = 0;
    if (wid < 0) width = 0;
    else width = wid;
}

void NText::setAttr(const Attr &attr) {
    attribute = attr;
}

void NText::setBeginPoint(int index) {
    if (index < 0) {
        throw FatalError("NText::setBeginPoint()");
    }
    beginPoint = index;
}

Printer NText::toPrinter() const {
    int size = content.size();

    if (width > size) {  // fill with blank
        return Printer(1, Printee(content+std::string(width-size, ' '), attribute));
    }

    std::string::const_iterator endIter;
    if (beginPoint + width > size) {
        endIter = content.end();
    } else {
        endIter = content.begin() + beginPoint + width;
    }

    std::string displayStr(content.begin()+beginPoint, endIter);
    return Printer(1, Printee(displayStr, attribute));
}
