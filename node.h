#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "term.h"

using std::cout;

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}

  bool evaluate(){
    if(payload == SEMICOLON){
      return left->evaluate()==true||right->evaluate()==true;
    }
    if(payload == COMMA){
      return left->evaluate()==true&&right->evaluate()==true;
    }
    if(payload == EQUALITY){
      return left->term->match(*(right->term));
    }
    //fix here
    cout<<"error\n";
    return false;
  }

  Operators payload;
  Term *term;
  Node *left;
  Node *right;

private:
  
};

#endif
