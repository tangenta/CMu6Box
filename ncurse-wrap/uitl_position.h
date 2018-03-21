#ifndef UTIL_POSITION_H
#define UTIL_POSITION_H

#include "exceptions.h"

class Position
{
public:
    Position(int r, int c): row(r), col(c) {
        if (r < 0 || c < 0)
            throw OutOfRangeError("Position()");
    }

    // getter
    int getRow() const { return row; }
    int getCol() const { return col; }

private:
    int row, col;
};

#endif // POSITION_H
