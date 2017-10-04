#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "number.h"
#include "variable.h"

using std::string;

class Atom {
public:
  Atom (string s):_symbol(s) {};
  //bool operator ==(Atom a) {return _symbol == a._symbol;}
  string symbol();
  int value();
  bool match( Atom atom );
  bool match(Number &num);
private:
  string _symbol;
  int _value;
};

#endif
