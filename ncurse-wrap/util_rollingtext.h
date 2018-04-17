#ifndef UTIL_ROLLINGTEXT_H
#define UTIL_ROLLINGTEXT_H

#include "util_text.h"

class RollingText : public Text {
public:
    RollingText(std::string const&,
                Position const&,
                int,
                Attr const& = Attr());
    ~RollingText() {}


    void update() override;
    void draw(Window*) override;

    void enable(bool b) { running = b; }

private:
    bool running;
    int textPos;
    int lenOutOfRange;
};

#endif // UTIL_ROLLINGTEXT_H
