#ifndef CONSTANTS_H
#define CONSTANTS_H

struct NC {
    static short Black;
    static short Red;
    static short Green;
    static short Yellow;
    static short Blue;
    static short Magenta;
    static short Cyan;
    static short White;
};

struct NF {
    static unsigned long Normal;
    static unsigned long Standout;
    static unsigned long Underline;
    static unsigned long Reverse;
    static unsigned long Blink;
    static unsigned long Dim;
    static unsigned long Bold;
    static unsigned long AltCharSet;
};

enum class AlignMode {
    Center,
    Left,
    Right,
};

class Color {
public:
    Color() = delete;
    Color(short c): icolor(c) {}
    short getNC() const { return icolor; }
private:
    short icolor;
};

class Font {
public:
    Font() = delete;
    Font(unsigned long f): ifont(f) {}
    unsigned long getNF() const { return ifont; }
private:
    unsigned long ifont;   //// bugfix: unable to pack fonts through "|"
};


#endif // CONSTANTS_H
