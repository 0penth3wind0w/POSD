#ifndef TERM_H
#define TERM_H

#include <string>
#include <sstream>
#include <iostream>

using std::string;
using namespace std;

class Variable;
class Struct;
// template <class T>
class Iterator;

class Term
{
public:
  virtual string symbol() const { return _symbol; }
  virtual string value() const { return symbol(); }
  virtual bool match(Term &a);
  // {
  //   return _symbol == a.symbol();
  // }
  virtual int size() { return 0; }
  virtual Term count(int &i) { return 0; }
  virtual Iterator * createIterator();
  // virtual Iterator <Term*> * createIterator();
  virtual Struct* getStruct() {
    return nullptr;
  }
  virtual Variable* getVariable() {
    return nullptr;
  }

  bool isAtom = false;
  bool isVar = false;
  bool isNum = false;
  bool isStruct = false;
  bool isList = false;

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