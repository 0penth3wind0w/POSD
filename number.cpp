#include "include/number.h"
#include "include/atom.h"

string Number::symbol(){ return _symbol; }
int Number::value(){ return _value; }
void Number::setSymbol(string s){
    _symbol = s;
}
bool Number::match(Number num){
    if(value() == num.value()){
      return true;
    }
    return false;
}
bool Number::match(Atom atom){
    if(value() == atom.value()){
        return true;
    }
    return false;
}
/*bool Number::match(Variable &var){
    if(var.assignable()){
        var.setValue(_value);
        var.setAssignableToFalse();
        if(value()==var.value()){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if(value()==var.value()){
            return true;
        }
        else {
            return false;
        }
    }
}*/