#include "include/number.h"
#include "include/atom.h"
#include "include/variable.h"

using std::to_string;

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
    if(to_string(value()) == atom.value()){
        return true;
    }
    return false;
}
bool Number::match(Variable &var){
    if(var.assignable()){
        var.setValue(to_string(_value));
        var.setAssignableToFalse();
        if(to_string(value()) == var.value()){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if(to_string(value()) == var.value()){
            return true;
        }
        else {
            return false;
        }
    }
}