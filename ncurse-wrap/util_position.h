#ifndef UTIL_POSITION_H
#define UTIL_POSITION_H

#include "exceptions.h"

class Position
{
public:
    Position(int r = 0, int c = 0): row(r), col(c) {
//        if (r < 0 || c < 0)
//            throw OutOfRangeError("Position()");
        // 原谅我，超出去不显示
    }

    friend bool operator ==(const Position &l, const Position &r) {
        return (l.col == r.col && l.row == r.row);
    }

    // getter
    int getRow() const { return row; }
    int getCol() const { return col; }

private:
    int row, col;
};

#endif // POSITION_H
