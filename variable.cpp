#include "variable.h"
#include "atom.h"

using std::to_string;

string Variable::value() const { return _value; }
string Variable::symbol() const { return _symbol; }

bool match(Term &term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
        if(assignable()){
            setValue(term.value());
            setAssignableToFalse();
            if(value() == atom.symbol()){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            if(value() == atom.symbol()){
                return true;
            }
            else {
                return false;
            }
        }

      /*if (!_name.match(ps->_name))
        return false;
      if(_args.size()!= ps->_args.size())
        return false;
      for(int i=0;i<_args.size();i++){
        if(_args[i]->symbol() != ps->_args[i]->symbol())
            return false;
      }
      return true;*/
    }
    return false;
  }

bool Variable::match(Atom atom) {
    if(assignable()){
        setValue(atom.symbol());
        setAssignableToFalse();
        if(value() == atom.symbol()){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if(value() == atom.symbol()){
            return true;
        }
        else {
            return false;
        }
    }
}
bool Variable::match(Number num) {
    if(assignable()){
        setValue(num.value());
        setAssignableToFalse();
        if(value() == num.value()){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if(value() == num.value()){
            return true;
        }
        else {
            return false;
        }
    }
}

void Variable::setValue(string s) {
    _value = s;
}

bool Variable::assignable() { return _assignable; };

void Variable::setAssignableToFalse() {
    _assignable = false;
}