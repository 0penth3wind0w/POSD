#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <vector>
#include <string>
#include "atom.h"

using std::string;
using std::cout;

class Struct : public Term{
public:
  Struct(Atom const & name, std::vector<Term *> args):_name(name), _args(args) { }

  Term * args(int index) {
    return _args[index];
  }

  Atom const & name() {
    return _name;
  }

  string symbol() const;

  string value() const;
  bool match(Variable & variable);
  bool match(Term &term);

private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif
