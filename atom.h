#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "number.h"
//#include "variable.h"

using std::string;

class Term{
  public:
    virtual string symbol() const = 0;
  
    virtual string value() const{
      return symbol();
    };
  
    virtual bool match(Term & term) {
      return symbol() == term.symbol();
    }
  
};

class Atom : public Term{
public:
  Atom (string s):_symbol(s) {};
  string symbol() const;
  //bool match(Atom atom);
  //bool match(Number num);
  //bool match(Variable &var);
private:
  string _symbol;
  string _value;
};

#endif
