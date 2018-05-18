#include "util_nmenu.h"

NMenu::NMenu(): width(0), height(0), focus(0), frame(0),
    highlight(Attr(Color(), Font({NF::Bold, NF::Reverse}))) {

}

NMenu::NMenu(int width, int height)
    : width(width), height(height), focus(0), frame(0),
    highlight(Attr(Color(), Font({NF::Bold, NF::Reverse}))) {

}

void NMenu::addItem(NText const& newItem) {
    focus = frame = 0;
    NText item(newItem);
    item.setWidth(width);
    items.push_back(item);
    items[0].setAttr(highlight);
}

void NMenu::removeItemAt(int index) {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        throw FatalError("NMenu::removeItemAt()");
    }
    focus = frame = 0;
    items.erase(items.begin()+index);
}

int NMenu::getHeight() const {
    return height;
}

int NMenu::getWidth() const {
    return width;
}

int NMenu::getFocus() const {
    return focus;
}

void NMenu::setAttr(Attr const& attr) {
    normal = attr;
    for (auto& i: items) {
        i.setAttr(attr);
    }
    if (!items.empty()) {
        items[focus].setAttr(highlight);
    }
}

void NMenu::setHighlight(const Attr& attr) {
    highlight = attr;
}

void NMenu::moveUp() {
    if (items.empty()) return;
    items[focus].setBeginPoint(0);
    items[focus].setAttr(normal);
    if (focus == frame && focus != 0) {
        frame--;
    }
    focus = (focus == 0) ? focus : focus-1;
    items[focus].setAttr(highlight);
}

void NMenu::moveDown() {
    if (items.empty()) return;
    items[focus].setBeginPoint(0);
    items[focus].setAttr(normal);
    if (focus == frame+height-1 && focus != static_cast<int>(items.size()-1)) {
        frame++;
    }
    focus = (focus == static_cast<int>(items.size()-1)) ?
                static_cast<int>(items.size()-1) : focus+1;
    items[focus].setAttr(highlight);
}

void NMenu::update() {
    if (items.empty()) return;
    NText* objText = &items[focus];
    if (static_cast<int>(objText->getContent().size())-objText->getBeginPoint() <= width) {
        objText->setBeginPoint(0);
    } else {
        objText->setBeginPoint(objText->getBeginPoint()+1);
    }
}

Printer NMenu::toPrinter() const {
    int counter = height;
    Printer printer;
    for (auto i = items.begin()+frame; i != items.end(); ++i) {
        Printer subPrinter = i->toPrinter();
        printer.splice(printer.end(), subPrinter);
        if (--counter == 0) break;
        printer.back().bias = printer.back().bias + Bias(1,0);
    }
    return printer;
}
