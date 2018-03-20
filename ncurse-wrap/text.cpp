#include "text.h"
#include <ncurses.h>
#include "window.h"
#include "constants_transform.h"
#include "exceptions.h"

Text::Text(std::string const& text, Position pos, int size,
           Color color, Font font, AlignMode mode)
        : itext(text), ipos(pos), isize(size), icolor(color), ifont(font), imode(mode) {
    if (size < 0 || text.size() > static_cast<size_t>(size))
        throw OutOfRangeError("Text()");
}

