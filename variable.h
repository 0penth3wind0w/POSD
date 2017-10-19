#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <iostream>
#include "atom.h"
#include "struct.h"

using std::string;
using std::cout;

//class Number;
//class Struct;

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
                ps->setValuePtr(this);
                setValuePtr(ps);
                return true;
            }
            else if (!ps->assignable() && !assignable()){ //pending
                return false;
            }
            else if (ps->assignable()){ //pending
                ps->setAssignableToFalse();
                ps->setValuePtr(this);
                return true;
            }
            else{ //pending
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
            setAssignableToFalse();
            _ptrValue = &term;
            setValue(term.value());
        }
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
  //bool match(Atom atom);
  //bool match(Number num);
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