#ifndef __SELECT_AND_HPP__
#define __SELECT_AND_HPP__

#include "select.hpp"

class Select_And : public Select {
protected:
    Select* a;
    Select* b;
public:
    Select_And(Select* a1, Select* b1) {
        a = a1;
        b = b1;
    }
    ~Select_And() {
        delete a;
        delete b;
    }
    virtual bool select(const Spreadsheet* sheet, int row) const {
        bool one = false;
        bool two = false;
        
        one = a->select(sheet, row);
        two = b->select(sheet, row);
        
        return (one && two);
    }

};

#endif
