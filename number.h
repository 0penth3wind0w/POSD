#ifndef NUMBER_H
#define NUMBER_H

#include <string>

using std::string;
using std::to_string;

class Atom;
class Variable;

class Number{
public:
    Number(float v):_value(v), _symbol(to_string(v)) {}
    string symbol() const;
    string value() const;
    void setSymbol(string s);
    //bool match(Number num);
    //bool match(Atom atom);
    //bool match(Variable &var);
    
private:
    string _symbol;
    float _value;
};

#endif
