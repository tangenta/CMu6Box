#include "setting_win.h"
#include "menu_win.h"
#include "../resources.h"
#include "../ncurse-wrap/util_nblock.h"
#include "../ncurse-wrap/util_nborder.h"
#include <QDir>

SettingWin::SettingWin(Resources* res): Window(res) {
    // prepare data
    std::vector<std::string> languages = {"Chinese", "English"};
    std::vector<std::string> colors =
            {"Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White"};

    // get current themeColor and match color in options
    std::string currentThemeColor = resource->themeColor.toStdString();
    int themeIndex = 0;
    auto pos = std::find(colors.begin(), colors.end(), currentThemeColor);
    if (pos != colors.end()) themeIndex = pos-colors.begin();

    QString themeColor = resource->themeColor;
    Attr unifiedAttr(resource->parseColor(themeColor));

    // initialize members for displaying current setting
    focus = 0;
    langBox = MultiText(languages, unifiedAttr);
    langBox.setIndex(resource->translator.isEnglish() ? 1 : 0);
    theme = MultiText(colors, unifiedAttr);
    theme.setIndex(themeIndex);
    aboutShow = false;
    aboutPage = Dialog(
                tl("\nVersion: 0.8.0 (build-1232)\nKernel: Powered by QT\nRender: Powered by Ncurses\nCopyright (c) 2018 licensed under the MIT License"),
                50, 6, normal, "", "");
}

Window* SettingWin::handleInput(int ch) {
    if (aboutShow == true) {
        switch (aboutPage.handleInput(ch)) {
        case Dialog::Attitude::HESITATE:
            return this;
            break;
        case Dialog::Attitude::REFUSE:
        case Dialog::Attitude::OK:
            aboutShow = false;
            return this;
            break;
        }
    }

    if (ch == NK::Esc) {
        return new MenuWin(resource);
    } else if (ch == NK::Enter) {
        if (focus == 2) {
            aboutShow = true;
        }
    } else if (ch == NK::Down) {
        if (focus < 2) focus++;
    } else if (ch == NK::Up) {
        if (focus > 0) focus--;
    } else if (ch == NK::Left) {
        if (focus == 0) langBox.prev();
        else if (focus == 1) theme.prev();
        validateSetting();
    } else if (ch == NK::Right) {
        if (focus == 0) langBox.next();
        else if (focus == 1) theme.next();
        validateSetting();
    }
    return this;
}

void SettingWin::update() {

}

void SettingWin::draw() {
    QString themeColor = resource->themeColor;
    Attr unifiedAttr(resource->parseColor(themeColor));
    labels = {NText(tl("language"), unifiedAttr),
              NText(tl("theme"), unifiedAttr),
              NText(tl("about"), unifiedAttr)};
    int labelsNum = labels.size();
    for (int i = 0; i != labelsNum; ++i) {
        Window::draw(labels[i], Position(4+2*i, 15));
        NText cursor = i == focus ? NText("->", unifiedAttr) :
                                    NText("  ", unifiedAttr);
        Window::draw(cursor, Position(4+2*i, 12));
    }
    Window::draw(langBox, Position(4, 45));
    Window::draw(theme, Position(6, 45));
    Window::draw(NText(tl(std::string("available key")) + ": ← → ↑ ↓ Enter Esc", normal), Position(23, 1));

    if (aboutShow == true) {
        NBorder bord('-', '|', '+', normal);
        bord.fit(aboutPage);
        Window::draw(NBlock<Dialog, NBorder>(aboutPage, bord), Position(7, 10));
    }
}

void SettingWin::validateSetting() {
    resource->translator = Translator(langBox.text());
    resource->themeColor = QString(theme.text().c_str());
    Attr attr(resource->parseColor(resource->themeColor));
    langBox.setAttr(attr);
    theme.setAttr(attr);
    normal = attr;
    setBackground(resource->themeColor);
    aboutPage = Dialog(
                tl("\nVersion: 0.8.0 (build-1232)\nKernel: Powered by QT\nRender: Powered by Ncurses\nCopyright (c) 2018 licensed under the MIT License"),
                50, 6, normal, "", "");
}
