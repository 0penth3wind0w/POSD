#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
#include "variable.h"

using std::string;

//class Variable;

/*class Term{
  public:
    virtual string symbol() const = 0;
  
    virtual string value() const = 0;
  
    virtual bool match(Term & term) {
      return symbol() == term.symbol();
    }
    
    //virtual bool match(Variable & variable){}
    virtual bool isVar() {return false;};
  
};*/

class Atom : public Term{
public:
  Atom (string s):_symbol(s), _value(s) {}
  string symbol() const { return _symbol; }
  string value() const  { return _value; }
  virtual bool match(Term & term) {
    return symbol() == term.symbol();
  }
  bool match(Variable &var){
    if(var.assignable()){
      var.setValue(_value);
      var.setValuePtr(this);
      var.setAssignableToFalse();
      return true;
    }
    else {
      if(value() == var.value()){
        return true;
      }
      else {
        return false;
      }
    }
  }
private:
  string _symbol;
  string _value;
};

#endif
