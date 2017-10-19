#ifndef ATOM_H
#define ATOM_H

#include <string>
//#include "variable.h"

using std::string;

class Variable;

class Term{
  public:
    virtual string symbol() const = 0;
  
    virtual string value() const = 0;
  
    virtual bool match(Term & term) {
      return symbol() == term.symbol();
    }
    
    //virtual bool match(Variable & variable){}
    virtual bool isVar() {return false;};
  
};

class Atom : public Term{
public:
  Atom (string s):_symbol(s), _value(s) {}
  string symbol() const { return _symbol; }
  string value() const  { return _value; }
  //bool match(Variable &var);
private:
  string _symbol;
  string _value;
};

#endif
