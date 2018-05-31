#include "util_dialog.h"
#include <QStringList>

Dialog::Dialog(): width(0), height(0), frame(0) {
    initializePrinter();
}

Dialog::Dialog(std::string const& str, int width, int height, Attr const& attr) :
    content(str), width(width), height(height), normal(attr), highlight(attr), frame(0) {
    isOK = true;
    cancelAttr = attr;
    okAttr = highlight;
    initializePrinter();
}

Printer Dialog::toPrinter() const {
    if (height < 2 || width < 5) return Printer();
    Printer result = printer;
    int printerSize = printer.size();
    if (height <= printerSize) {    // overflow
        for (int i = 0; i != frame; ++i) {
            result.pop_front();
        }
        int counter = height-1; // the last line is reserved for "cancel" and "ok"
        auto positionToCut = result.begin();
        for (; positionToCut != result.end() && counter != 0; ++positionToCut, --counter);/*empty*/
        result.erase(positionToCut, result.end());
        result.push_back(Printee("", normal, Bias(0, 2)));
    } else {
        // move to the last line
        result.push_back(Printee("", normal, Bias(height-printerSize-1, 2)));
    }
    result.push_back(Printee("Cancel", cancelAttr, Bias(0, width-8)));
    result.push_back(Printee("OK", okAttr));
    return result;
}

void Dialog::setHighlight(Attr const& attr) {
    highlight = attr;
    focusOk();
}

void Dialog::focusCancel() {
    cancelAttr = highlight;
    okAttr = normal;
    isOK = false;
}

void Dialog::focusOk() {
    cancelAttr = normal;
    okAttr = highlight;
    isOK = true;
}

void Dialog::shiftFocus() {
    if (isOK == true) {
        focusCancel();
    } else {
        focusOk();
    }
}

void Dialog::moveUp() {
    if (frame > 0) frame--;
}

void Dialog::moveDown() {
    int totalSize = printer.size();
    if (frame < totalSize-height) frame++;
}

void Dialog::initializePrinter() {
    // split content by '\n'
    QStringList list = QString(content.c_str()).split(QChar('\n'));
    for (auto const& i: list) {
        std::string obj = i.toStdString();
        // switch to next line automatically
        while (static_cast<int>(obj.size()) > width) {
            printer.push_back(Printee(std::string(obj.begin(), obj.begin()+width),
                                      normal, Bias(1, 0)));
            obj.erase(obj.begin(), obj.begin()+width);
        }
        printer.push_back(Printee(obj, normal, Bias(1,0)));
    }
}

Dialog::Attitude Dialog::handleInput(int ch) {
    if (ch == NK::Down) {
        moveDown();
        return Attitude::HESITATE;
    } else if (ch == NK::Up) {
        moveUp();
        return Attitude::HESITATE;
    } else if (ch == NK::Left || ch == NK::Right) {
        shiftFocus();
        return Attitude::HESITATE;
    } else if (ch == NK::Enter) {
        if (isOK) {
            return Attitude::OK;
        } else {
            return Attitude::REFUSE;
        }
    } else if (ch == NK::Esc) {
        return Attitude::REFUSE;
    }
    return Attitude::HESITATE;
}
