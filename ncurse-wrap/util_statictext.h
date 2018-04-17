#ifndef UTIL_STATICTEXT_H
#define UTIL_STATICTEXT_H

#include "util_text.h"
#include "ncurses_wrapper.h"

class StaticText : public Text {
public:
    StaticText(std::string const&,
               Position const&,
               int,
               Attr const& = Attr(),
               AlignMode = AlignMode::Left);

    ~StaticText() {}

    void update() override;
    void draw(Window*) override;
};

#endif // UTIL_STATICTEXT_H
