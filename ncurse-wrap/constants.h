#ifndef CONSTANTS_H
#define CONSTANTS_H

enum class NC {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
};

enum class NF {
    Normal,
    Standout,
    Underline,
    Reverse,
    Blink,
    Dim,
    Bold,
    AltCharSet,
};

enum class AlignMode {
    Center,
    Left,
    Right,
};

class Color {
public:
    Color() = delete;
    Color(NC c): icolor(c) {}
    NC getNC() const { return icolor; }
private:
    NC icolor;
};

class Font {
public:
    Font() = delete;
    Font(NF f): ifont(f) {}
    NF getNF() const { return ifont; }
private:
    NF ifont;   //// bugfix: unable to pack fonts through "|"
};


#endif // CONSTANTS_H
