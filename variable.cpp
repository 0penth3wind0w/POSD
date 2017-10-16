#include "variable.h"
#include "atom.h"

using std::to_string;

string Variable::value() { return _value; }
string Variable::symbol() const { return _symbol; }

/*bool Variable::match(Atom atom) {
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
}*/

void Variable::setValue(string s) {
    _value = s;
}

bool Variable::assignable() { return _assignable; };

void Variable::setAssignableToFalse() {
    _assignable = false;
}