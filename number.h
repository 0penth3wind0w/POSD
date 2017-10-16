#ifndef NUMBER_H
#define NUMBER_H

#include <string>

using std::string;
using std::to_string;

class Atom;
class Variable;

class Number{
public:
    Number(int v):_value(v), _symbol(to_string(v)) {}
    string symbol();
    string value();
    void setSymbol(string s);
    //bool match(Number num);
    //bool match(Atom atom);
    //bool match(Variable &var);
    
private:
    string _symbol;
    int _value;
};

#endif
