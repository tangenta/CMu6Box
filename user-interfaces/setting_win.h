#ifndef SETTING_WIN_H
#define SETTING_WIN_H
#include "../ncurse-wrap/util_window.h"
#include <vector>
#include "../ncurse-wrap/util_multitext.h"
class SettingWin: public Window {
public:
    SettingWin(Resources* res);
    ~SettingWin();
    Window* handleInput(int ch) override;
    void update() override;
    void draw() override;
private:
    std::vector<NText> labels;
    int focus;
    MultiText langBox;
    NText theme;
//    NText languageCombobox;
//    NText themeCombobox;
};

#endif // SETTING_WIN_H
