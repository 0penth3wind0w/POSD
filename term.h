#ifndef TERM_H
#define TERM_H

#include <string>

class Term{
public:
  virtual string symbol() const = 0;

  virtual string value() const = 0;

  virtual bool match(Term & term) {
    return symbol() == term.symbol();
  }
  
  //virtual bool match(Variable & variable){}
  virtual bool isVar() {return false;};

};

#endif
