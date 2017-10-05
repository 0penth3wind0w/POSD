#include "number.h"
#include "atom.h"
#include "variable.h"

using std::to_string;

string Number::symbol(){ return _symbol; }
string Number::value(){ return to_string(_value); }
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
bool Number::match(Variable &var){
    if(var.assignable()){
        var.setValue(to_string(_value));
        var.setAssignableToFalse();
        if(value() == var.value()){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if(value() == var.value()){
            return true;
        }
        else {
            return false;
        }
    }
}