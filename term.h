#ifndef TERM_H
#define TERM_H

#include <string>
#include <sstream>
#include <iostream>

using std::string;
using namespace std;

template <class T>
class Iterator;

class Term
{
public:
  virtual string symbol() const { return _symbol; }
  virtual string value() const { return symbol(); }
  virtual bool match(Term &a)
  {
    return _symbol == a.symbol();
  }
  
  bool isAtom = false;
  bool isVar = false;
  bool isNum = false;
  bool isStruct = false;
  bool isList = false;

  virtual int size() { return 0; }
  virtual Term count(int &i) { return 0; }
  virtual Iterator <Term*> * createIterator();

protected:
  Term() : _symbol("") {}
  Term(string s) : _symbol(s) {}
  Term(double db)
  {
    std::ostringstream strs;
    strs << db;
    _symbol = strs.str();
  }
  string _symbol;
};

#endif