#ifndef BLOCK_H
#define BLOCK_H

#include "util_position.h"

template<typename BORD, typename CONT>
class Block
{
public:
    Block(const BORD &bd, const CONT &ct) : width(bd.width), height(bd.height), position(bd.position), border(bd), content(ct) {
        // 这个类的作用就是组合外边界和里面的内容，但外边界怎么定义取决于你，这里附赠“边界检查”
        const bool out0 = bd.position.getRow() >= ct.position.getRow();
        const bool out1 = bd.position.getRow()+bd.height <= ct.position.getRow()+ct.height;
        const bool out2 = bd.position.getCol() >= ct.position.getCol();
        const bool out3 = bd.position.getCol()+bd.width <= ct.position.getCol()+ct.width;
        if (out0 || out1 || out2 || out3) {
            throw OutOfRangeError("Block()");
        }
    }

    void update() {
        border.update();
        content.update();
    }
    void draw(Window *win) {
        border.draw(win);
        content.draw(win);
    }

    const int width;
    const int height;
    Position position;
    BORD border;
    CONT content;
};

#endif // BLOCK_H
