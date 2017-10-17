#include "variable.h"
#include "number.h"
#include "struct.h"

using std::to_string;

string Variable::value() const { return ptrValue->value()/*_value*/; }
string Variable::valuePtr() const { }
string Variable::symbol() const { return _symbol; }
/*
bool Variable::match(Term &term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
        if(assignable()){
            setValue(term.value());
            setAssignableToFalse();
            if(value() == term.symbol()){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            if(value() == term.symbol()){
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}
*/
bool Variable::match(Term &term){
    //Struct * ps = dynamic_cast<Struct *>(&term);
    //if (ps){
        if(assignable()){
            //setValuePtr(term);
            setAssignableToFalse();
            ptrValue = &term;
            if(ptrValue->value() == term.value()){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            if(ptrValue->value() == term.value()){
                return true;
            }
            else {
                return false;
            }
        }
    //}
    return false;
}



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