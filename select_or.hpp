#ifndef _SELECT_OR_HPP_
#define _SELECT_OR_HPP_

#include "select.hpp"


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
