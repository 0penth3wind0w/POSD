#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Atom {
public:
  Atom (string s):_symbol(s) {}
  //bool operator ==(Atom a) {return _symbol == a._symbol;}
  string symbol(){ return _symbol; }
  string value(){ return _value; }
  bool match( Atom atom ){
    if(symbol() == atom.symbol()){
      return true;
    }
    return false;
  }
private:
  string _symbol;
  string _value;
};

#endif
