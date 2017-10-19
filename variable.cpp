#include "variable.h"
#include "number.h"
#include "struct.h"

using std::to_string;

string Variable::value() const
{
    if (!_ptrValue)
    {
        return symbol();
    }
    else
    {
        return _ptrValue->value();
    }
}
string Variable::valuePtr() const
{
    if (!_ptrValue)
    {
        return symbol();
    }
    else
    {
        return _ptrValue->value();
    }
}
string Variable::symbol() const { return _symbol; }

bool Variable::match(Term &term)
{
    if (term.isVar())
    { //variable match variable
        cout << "123\n";
        Variable *ps = dynamic_cast<Variable *>(&term);
        if (ps)
        {
            if (ps->assignable() && assignable())
            {
                ps->setValuePtr(this);
                setValuePtr(ps);
                return true;
            }
            else if (!ps->assignable() && !assignable())
            { //pending
                return false;
            }
            else if (ps->assignable())
            { //pending
                ps->setAssignableToFalse();
                ps->setValuePtr(this);
                return true;
            }
            else
            { //pending
                setAssignableToFalse();
                setValuePtr(ps);
                return true;
            }
        }
        return false;
    }
    else
    { //variable match other*/
        cout << "o1\n";
        if (assignable())
        {
            cout << "o2\n";
            setAssignableToFalse();
            cout << "o3\n";
            _ptrValue = &term;
            cout << "o4\n";
            setValue(term.value());
            cout << "o5\n";
        }
        if (_ptrValue->value() == term.value())
        {
            return true;
        }
        else
        {
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

void Variable::setValuePtr(Term *t) { _ptrValue = t; }

bool Variable::assignable() { return _assignable; }

void Variable::setAssignableToFalse() { _assignable = false; }