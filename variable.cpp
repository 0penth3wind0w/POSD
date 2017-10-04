#include "include/variable.h"
#include "include/atom.h"

string Variable::value(){ return _value; }

bool Variable::match( Atom atom ){
    bool ret = _assignable;
    if(_assignable){
        _value = atom.symbol() ;
        _assignable = false;
    }
    return ret;
}

void Variable::setValue(string s){
    _value = s;
}

bool Variable::assignable(){ return _assignable; };

void Variable::setAssignableToFalse(){
    _assignable = false;
}