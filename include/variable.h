#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
using std::string;

class Atom;

class Variable{
public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string value();
  bool match( Atom atom );
  void setValue(string s);
  bool assignable();
  void setAssignableToFalse();
private:
  string _value;
  bool _assignable = true;
};

#endif