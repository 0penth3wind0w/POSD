#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"
using std::string;

class Number{
public:
    Number(string s, string v):_symbol(s),_value(v) {}
    string symbol(){ return _symbol; }
    string value(){ return _value; }
    //bool match(){ }
private:
    string _symbol;
    string _value;
};

#endif
