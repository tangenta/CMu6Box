#include "setting_win.h"
#include "menu_win.h"
#include "../resources.h"
#include <QDir>

SettingWin::SettingWin(Resources* res): Window(res) {
    labels.push_back(NText(tl("language")));
    labels.push_back(NText(tl("theme")));
    labels.push_back(NText(tl("about")));
    focus = 0;
    QStringList qfiles = QDir("./locale").entryList(QStringList() << "*.json");
    std::vector<std::string> files;
    for (auto &str: qfiles) {
        QString tmp(str);
        files.push_back(tmp.remove(".json").toStdString());
    }
    langBox = MultiText(files);
    theme = NText(tl("default"));
}

SettingWin::~SettingWin() {
    if (!langBox.text().empty()) {
        resource->translator =
                Translator(std::string() + "./locale/" + langBox.text() + ".json");
    }
}

Window* SettingWin::handleInput(int ch) {
    if (ch == NK::Esc || ch == NK::Enter) {
        return new MenuWin(resource);
    } else if (ch == NK::Down) {
        if (focus < 2) focus++;
    } else if (ch == NK::Up) {
        if (focus > 0) focus--;
    } else if (ch == NK::Left) {
        if (focus == 0) langBox.prev();
    } else if (ch == NK::Right) {
        if (focus == 0) langBox.next();
    }

    return this;
}

void SettingWin::update() {

}

void SettingWin::draw() {
    int labelsNum = labels.size();
    for (int i = 0; i != labelsNum; ++i) {
        Window::draw(labels[i], Position(4+2*i, 15));
        NText cursor = i == focus ? NText("->", Attr(Color(), Font({NF::Bold}))) :
                                    NText("  ");
        Window::draw(cursor, Position(4+2*i, 12));
    }
    Window::draw(langBox, Position(4, 45));
    Window::draw(theme, Position(6, 45));
}
