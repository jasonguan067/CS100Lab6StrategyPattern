#ifndef __SELECT_NOT_HPP__
#define __SELECT_NOT_HPP__


#include "select.hpp"

class Select_Not : public Select {
protected:
    Select* a;
public:
    Select_Not(Select* select) {
        a = select;
    }
    ~Select_Not() {
        delete a;
    }
    virtual bool select(const Spreadsheet* sheet, int row) const {
        return !(a->select(sheet, row));
    }
};

#endif
