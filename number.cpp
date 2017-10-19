#include "number.h"
#include "variable.h"

using std::to_string;

string Number::symbol() const {
    string input =  to_string(_value);
    input.erase(input.find_last_not_of('0') + 1, std::string::npos);
    if(input.back() == '.'){
        input.erase(input.find_last_not_of('.') + 1, std::string::npos);
    }
    //_symbol = input;
    return input;
 }
string Number::value() const {
    string input =  to_string(_value);
    input.erase(input.find_last_not_of('0') + 1, std::string::npos);
    if(input.back() == '.'){
        input.erase(input.find_last_not_of('.') + 1, std::string::npos);
    }
    return input;
}
void Number::setSymbol(string s){
    _symbol = s;
}

bool Number::match(Term & term) {
    //cout<<"123";
    return symbol() == term.symbol();
}

bool Number::match(Variable &var){
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