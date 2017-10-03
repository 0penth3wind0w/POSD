#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"
#include "Variable.h"
using std::string;

class Number{
public:
    Number(string s, string v):_symbol(s),_value(v) {}
    string symbol(){ return _symbol; }
    string value(){ return _value; }
    bool match(Number num){
        if(value() == num.value()){
          return true;
        }
        return false;
    }
    bool match(Atom atom){
        if(value() == atom.symbol()){
            return true;
        }
        return false;
    }
    bool match(Variable &var){
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
    }
    
private:
    string _symbol;
    string _value;
};

#endif
