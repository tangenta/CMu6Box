#ifndef SETTING_H
#define SETTING_H
#include "../ncurse-wrap/ncurses_wrapper.h"
#include "dictionary.h"
class Setting {

public:
    Setting();
    ~Setting();
    void openSetting();
    void saveCurrentSetting();
    Dictionary::Language getLanguage();
    Attr getTheme();
private:
    Dictionary::Language language;
    Attr theme;
};

#endif // SETTING_H
