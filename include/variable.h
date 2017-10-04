#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "number.h"
using std::string;

class Atom;

class Variable{
public:
  Variable(string s):_symbol(s){}
  string value();
  string symbol();
  bool match(Atom atom);
  bool match(Number num);
  void setValue(string s);
  bool assignable();
  void setAssignableToFalse();
private:
  string const _symbol;
  string _value;
  bool _assignable = true;
};

#endif