#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
using std::string;

class Variable{
public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string value(){ return _value; }
  bool match( Atom atom ){
    bool ret = _assignable;
    if(_assignable){
      _value = atom.symbol() ;
      _assignable = false;
    }
    return ret;
  }
  void setValue(string s){
    _value = s;
  }
  bool assignable(){ return _assignable; };
  void changeAssignableStatus(){
    if(_assignable == true) {
      _assignable = false;
    }
    else {
      _assignable = true;
    }
  }
private:
  string _value;
  bool _assignable = true;
};

#endif
