#include "util_dialog.h"
#include <QStringList>

Dialog::Dialog(): width(0), height(0) {}

Dialog::Dialog(std::string const& str, int width, int height, Attr const& attr) :
    content(str), width(width), height(height), attr(attr) {}

Printer Dialog::toPrinter() const {
    Printer printer;
    // split content by '\n'
    QStringList list = QString(content.c_str()).split(QChar('\n'));
    for (auto const& i: list) {
        std::string obj = i.toStdString();
        // switch to next line automatically
        while (static_cast<int>(obj.size()) > width) {
            printer.push_back(Printee(std::string(obj.begin(), obj.begin()+width),
                                      attr, Bias(1, 0)));
            obj.erase(obj.begin(), obj.begin()+width);
        }
        printer.push_back(Printee(obj, attr, Bias(1,0)));
    }
    if (height < static_cast<int>(printer.size())) {
        throw InvalidError("Dialog::toPrinter()");
    }
    return printer;
}
