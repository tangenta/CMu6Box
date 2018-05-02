#ifndef UTIL_POSITION_H
#define UTIL_POSITION_H

#include "exceptions.h"

class Position
{
public:
    Position(int r = 0, int c = 0): row(r), col(c) {}

    friend bool operator ==(const Position &l, const Position &r) {
        return (l.col == r.col && l.row == r.row);
    }

    friend Position operator +(const Position &l, const Position &r) {
        return Position(l.getRow()+r.getRow(), l.getCol()+r.getCol());
    }

    // getter
    int getRow() const { return row; }
    int getCol() const { return col; }

private:
    int row, col;
};
using Bias = Position;


#endif // POSITION_H
