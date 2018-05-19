#include "setting_win.h"
#include "menu_win.h"
#include "../resources.h"
#include <QDir>

SettingWin::SettingWin(Resources* res): Window(res) {
    // prepare data
    QStringList qfiles = QDir("./locale").entryList(QStringList() << "*.json");
    std::vector<std::string> files;
    for (auto &str: qfiles) {
        QString tmp(str);
        files.push_back(tmp.remove(".json").toStdString());
    }
    std::vector<std::string> colors =
            {"Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White"};

    std::string currentLangFile = resource->translator.getFilename();
    int langFileIndex = 0;
    auto split = currentLangFile.find_last_of('/');
    if (split != currentLangFile.npos) {
        currentLangFile = currentLangFile.substr(split+1);
    }
    if (!currentLangFile.empty()) {
        langFileIndex = qfiles.indexOf(QRegExp(currentLangFile.c_str()));
        if (langFileIndex == -1) {
            throw FatalError("SettingWin::SettingWin()");
        }
    }

    std::string currentThemeColor = resource->themeColor.toStdString();
    int themeIndex = 0;
    auto pos = std::find(colors.begin(), colors.end(), currentThemeColor);
    if (pos != colors.end()) themeIndex = pos-colors.begin();

    // initialize members
    focus = 0;
    langBox = MultiText(files);
    langBox.setIndex(langFileIndex);
    theme = MultiText(colors);
    theme.setIndex(themeIndex);
}

Window* SettingWin::handleInput(int ch) {
    if (ch == NK::Esc) {
        return new MenuWin(resource);
    } else if (ch == NK::Enter) {
        validateSetting();
    } else if (ch == NK::Down) {
        if (focus < 2) focus++;
    } else if (ch == NK::Up) {
        if (focus > 0) focus--;
    } else if (ch == NK::Left) {
        if (focus == 0) langBox.prev();
        else if (focus == 1) theme.prev();
    } else if (ch == NK::Right) {
        if (focus == 0) langBox.next();
        else if (focus == 1) theme.next();
    }
    return this;
}

void SettingWin::update() {

}

void SettingWin::draw() {
    labels = {NText(tl("language")),NText(tl("theme")),NText(tl("about"))};
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

void SettingWin::validateSetting() {
    if (QDir("./locale").exists(std::string(langBox.text() + ".json").c_str())) {
        resource->translator =
                Translator(std::string() + "./locale/" + langBox.text() + ".json");
    }
    resource->themeColor = QString(theme.text().c_str());
    setBackground(resource->themeColor);
}
