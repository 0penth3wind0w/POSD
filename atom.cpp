#include "atom.h"
#include "variable.h"

string Atom::symbol() const { return _symbol; }
string Atom::value() const { return _value; }

/*bool Atom::match(Variable &var){
    if(var.assignable()){
        var.setValue(_symbol);
        var.setAssignableToFalse();
        if(symbol() == var.value()){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if(symbol() == var.value()){
            return true;
        }
        else {
            return false;
        }
    }
}*/
