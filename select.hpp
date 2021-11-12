#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select_Column 
{
protected:
    string name;

public:
    Select_Contains(const Spreadsheet* sheet, const std::string& columnName, const std::string& dataName) : Select_Column(sheet, columnName){
	    name = dataname;
    }

    virtual bool select(const std::string& s) const{
	    if(s == ""){ //empty word
	        return true;
        }

	    int temp = s.find(name);
	    if(temp != std::string::npos){
		    return true;
	    } else {
		    return false;
	    }
    }	 



};

class Select_And : public Select {
protected:
    Select* s1;
    Select* s2;

public:
    Select_And(Select* a, Select* b) {
        s1 = a;
        s2 = b;
    }
    ~Select_And() {
        delete s1;
        delete s2;
    }
    virtual bool select(const Spreadsheet* sheet, int row) const {
        bool one = false;
        bool two = false;

        one = s1->select(sheet, row);
        two = s2->select(sheet, row);

        return (one && two);

};

class Select_Not : public Select {
protected:
    Select* a;

public:
    Select_Not(Select* select) { a = select; }
    ~Select_Not() { delete a; }
    virtual bool select(const Spreadsheet* sheet, int row) const {
        return !(a->select(sheet, row));
    }

};


class Select_Or : public Select{
	protected:
	  Select* temp1;
	  Select* temp2;

	public:
	  Select_Or(Select* left, Select* right){
		temp1 = left;
		temp2 = right;
	
	}

	~Select_Or(){
	delete temp1;
	delete temp2;
	}

	virtual bool select(const Spreadsheet* sheet, int row) const{
	   bool flag1 = false;
	   bool flag2 = false;

	   flag1 = temp1->select(sheet,row);
	   flag2 = temp2->select(sheet,row);

	   if(flag1 == true || flag2 == true){
		return true;
	} else {
		return false;

	}



	}


};

#endif //__SELECT_HPP__
