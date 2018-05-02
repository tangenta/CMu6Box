#ifndef UTIL_NBLOCK_H
#define UTIL_NBLOCK_H

#include <vector>
#include "ncurse-wrap/util_position.h"
#include "ncurse-wrap/ncurses_wrapper.h"

template <typename Front, typename Back>
class NBlock {
public:
    NBlock(): bias(Bias(1,1)) {}
    NBlock(Front const& frontEntity, Back const& backEntity, Bias bias = Bias(1,1))
        : frontEntity(frontEntity), backEntity(backEntity), bias(bias) {
        checkValidation();
    }
    NBlock(Front const& frontEntity, Back const& backEntity, bool verticalCentering,
           bool horizontalCentering): frontEntity(frontEntity), backEntity(backEntity) {
        int biasRow = 1;
        int biasCol = 1;
        if (verticalCentering) {
            biasRow = (backEntity.getHeight() - frontEntity.getHeight())/2;
        }
        if (horizontalCentering) {
            biasCol = (backEntity.getWidth() - frontEntity.getWidth())/2;
        }
        bias = Bias(biasRow, biasCol);
        checkValidation();
    }

    Printer toPrinter() const {
        // overwrite the background
        Printer printer = backEntity.toPrinter();
        printer.back().bias = printer.back().bias + bias;
        printer.splice(printer.end(), frontEntity.toPrinter());
        return printer;
    }

    void setFront(Front const& front) {
        frontEntity = front;
        checkValidation();
    }

    void setBack(Back const& back) {
        backEntity = back;
        checkValidation();
    }

    void setAttr(Attr const& attr) {
        frontEntity.setAttr(attr);
        backEntity.setAttr(attr);
    }

private:
    void checkValidation() {
        if (frontEntity.getWidth()+bias.getCol() >= backEntity.getWidth()
                || frontEntity.getHeight()+bias.getRow() >= backEntity.getHeight()) {
            throw FatalError("NBlock::checkValidation()");
        }
    }

    Front frontEntity;
    Back backEntity;
    Bias bias;
};

#endif // UTIL_NBLOCK_H
