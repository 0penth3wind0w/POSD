#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <string>
#include "term.h"
#include "list.h"

using std::cout;
using std::string;

class Variable : public Term{
public:
  Variable(string s):_symbol(s),_value(s){}
  string value() const {
    if (_ptrValue == this){
        return symbol();
    }
    else{   
        return _ptrValue->value();
    }
  };
  string valuePtr() const {
    if (!_ptrValue){
        return symbol();
    }
    else{
        return _ptrValue->value();
    }
  }
  string symbol() const { return _symbol; }
  bool match(Term & term) {
    if (term.isVar()){ //variable match variable
        Variable *ps = dynamic_cast<Variable *>(&term);
        if (ps){
            if (ps->assignable() && assignable()){
                cout<<"VARMATCH_1\n";
                ps->setValuePtr(this);
                setValuePtr(ps);
                return true;
            }
            else if (!ps->assignable() && !assignable()){ //pending
                cout<<"VARMATCH_2\n";
                return false;
            }
            else if (ps->assignable()){ //pending
                cout<<"VARMATCH_3\n";
                ps->setAssignableToFalse();
                ps->setValuePtr(this);
                return true;
            }
            else{ //pending
                cout<<"VARMATCH_4\n";
                setAssignableToFalse();
                setValuePtr(ps);
                return true;
            }
        }
        return false;
    }
    else{ //variable match other*/
        if (assignable())
        {
			List *ps = dynamic_cast<List *>(&term);
			if(ps){
				for(int i=0; i<ps->esize();++i){
					if(ps->element(i)==value()){
						return false;
					}
				}
		}
            setAssignableToFalse();
            setValue(term.value());
            _ptrValue = &term;
            return true;
        }
        //need a fix to match term
        else{
            if (_ptrValue->value() == term.value())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
  	}
  }
  void setValue(string s) { _value = s; }
  void setValuePtr(Term *t){ _ptrValue = t; }
  bool assignable(){ return _assignable; }
  void setAssignableToFalse(){ _assignable = false; }
  bool isVar(){ return true; };
private:
  string const _symbol;
  string _value;
  Term *_ptrValue=this;
  bool _assignable = true;
};

#endif
