#ifndef TERM_H
#define TERM_H

#include <string>

class Term {
public:
    string symbol();
    string value();
    virtual bool match(Atom atom);
private:
    string _symbol;
    int _value;
}

#endif
