#ifndef SETTING_WIN_H
#define SETTING_WIN_H
#include "../ncurse-wrap/util_window.h"
#include "../database/dictionary.h"
class SettingWin: public Window {
public:
    SettingWin(Resources* res);

    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;
private:
    NText languageLabel;
//    NText languageCombobox;
    NText themeLabel;
//    NText themeCombobox;
    NText aboutLabel;
};

#endif // SETTING_WIN_H
