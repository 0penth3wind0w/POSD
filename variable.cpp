#include "variable.h"
#include "number.h"
#include "struct.h"

using std::to_string;

string Variable::value() const { return _ptrValue->value()/*_value*/; }
string Variable::valuePtr() const { return _ptrValue->value(); }
string Variable::symbol() const { return _symbol; }

bool Variable::match(Term &term){
    if(term.isVar()){ //variable match other
        Variable * ps = dynamic_cast<Variable *>(&term);
        if(ps){
            if(ps->assignable()&&assignable()){
                ps->setValuePtr(this);
                setValuePtr(ps);
                return true;
            }
            
            /*if(_ptrValue->value() == ps->value()){
                return true;
            }
            else {
                return false;
            }*/
        }
        return false;
    }
    else{   //variable match variable
        if(assignable()){
            setAssignableToFalse();
            _ptrValue = &term;
            setValue( term.value());
        }
        if(_ptrValue->value() == term.value()){
            return true;
        }
        else {
            return false;
        }
    }
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

void Variable::setValue(string s) { _value = s; }

void Variable::setValuePtr(Term *t){ _ptrValue = t;}

bool Variable::assignable() { return _assignable; }

void Variable::setAssignableToFalse() { _assignable = false; }