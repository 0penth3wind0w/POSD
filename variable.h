#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"
#include "struct.h"

using std::string;

class Variable : public Term{
public:
  Variable(string s):_symbol(s),_value(s){}
  string value() const;
  string symbol() const;
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