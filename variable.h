#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <iostream>
#include "atom.h"
#include "term.h"
using std::string;
using std::cout;

class Variable : public Term
{
public:
  Variable(string s) : Term(s), _inst(0){
    isVar = true;
  }
  string value() const{
    if (_inst)
      return _inst->value();
    else
      return Term::value();
  }
  bool match(Term &term){
    if (term.isList == true){
      for (int i = 0; i < term.size(); i++){
        if (term.count(i).symbol() == _symbol){
          return false;
        }
      }
      if (!_inst){
        _inst = &term;
        return true;
      }
      return _inst->match(term);
    }

    if (this == &term){
      return true;
    }
    if (!_inst){
      _inst = &term;
      return true;
    }
    else{
      Variable *ps = dynamic_cast<Variable*>(&term);
      if(ps){
        if(ps->assignable()){
          ps->setValue(_inst);
          return true;
        }
        else{
          _inst->match(*ps);
        }
      }
      return _inst->match(term);
    }
  }

  void setValue(Term *term){
    _inst = term;
  }
  bool assignable(){
    if(!_inst){
      return true;
    }
    else{
      return false;
    }
  }
  Variable* getVariable() {
    return this;
  }

  Term *_inst;

private:
};

#endif
