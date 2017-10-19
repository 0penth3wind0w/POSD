#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"
#include "variable.h"

using std::string;
using std::to_string;

class Variable;

class Number : public Term{
public:
    Number(float v):_value(v), _symbol(to_string(v)) {}
    string symbol() const {
        string input =  to_string(_value);
        input.erase(input.find_last_not_of('0') + 1, std::string::npos);
        if(input.back() == '.'){
            input.erase(input.find_last_not_of('.') + 1, std::string::npos);
        }
        //_symbol = input;
        return input;
     }
    string value() const {
        string input =  to_string(_value);
        input.erase(input.find_last_not_of('0') + 1, std::string::npos);
        if(input.back() == '.'){
            input.erase(input.find_last_not_of('.') + 1, std::string::npos);
        }
        return input;
    }
    void setSymbol(string s){
        _symbol = s;
    }
    bool match(Variable &var){
        //cout<<"456";
        if(var.assignable()){
            //cout<<"1n";
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
    bool match(Term & term){
        //cout<<"123";
        return symbol() == term.symbol();
    }
    
private:
    string _symbol;
    float _value;
};

#endif
