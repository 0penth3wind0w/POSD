#include "term.h"
#include "variable.h"
#include "iterator.h"

Iterator * Term::createIterator(){
  return new NullIterator(this);
}
// Iterator <Term*> * Term::createIterator(){
//     return new NullIterator<Term*>(this);
// }

bool Term::match(Term & a){
  if (a.getVariable() !=  nullptr)
    return a.match(*this);
  return symbol() == a.symbol();
}