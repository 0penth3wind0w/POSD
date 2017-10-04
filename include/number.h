#ifndef NUMBER_H
#define NUMBER_H

#include <string>
//#include "variable.h"
using std::string;

class Atom;

class Number{
public:
    Number(int v):_value(v) {}
    string symbol();
    int value();
    void setSymbol(string s);
    bool match(Number num);
    bool match(Atom atom);
    //bool match(Variable &var);
    
private:
    string _symbol;
    int _value;
};

#endif
