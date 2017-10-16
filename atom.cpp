#include "atom.h"

string Atom::symbol() const { return _symbol; }

/*bool Atom::match( Atom atom ){
    if(symbol() == atom.symbol()){
        return true;
    }
    return false;
}

bool Atom::match(Number num){
    if(symbol() == num.symbol()){
        return true;
    }
    else{
        return false;
    }
}

bool Atom::match(Variable &var){
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
