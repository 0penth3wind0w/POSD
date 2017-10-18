#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <iostream>
#include "atom.h"
#include "struct.h"

using std::string;
using std::cout;

class Number;
//class Struct;

class Variable : public Term{
public:
  Variable(string s):_symbol(s),_value(s){}
  string value() const;
  string valuePtr() const;
  string symbol() const;
  bool match(Term & term);
  //bool match(Atom atom);
  //bool match(Number num);
  void setValue(string s);
  void setValuePtr(Term *t);
  bool assignable();
  void setAssignableToFalse();
  bool isVar(){ return true; };
private:
  string const _symbol;
  string _value;
  Term *_ptrValue;
  bool _assignable = true;
};

#endif