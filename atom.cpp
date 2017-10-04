#include "include/atom.h"

string Atom::symbol(){ return _symbol; }

int Atom::value(){ return _value; }

bool Atom::match( Atom atom ){
    if(symbol() == atom.symbol()){
        return true;
    }
    return false;
}

bool Atom::match(Number &num){
    if(symbol() == num.symbol()){
        return true;
    }
    else{
        return false;
    }
}