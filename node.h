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
      cout<<payload<<"\t eva root SEMI\n";
      bool lEva=left->evaluate();
      bool rEva=right->evaluate();
      return lEva||rEva;
    }
    if(payload == COMMA){
      cout<<payload<<"\t eva root COM\n";
      bool lEva=left->evaluate();
      bool rEva=right->evaluate();
      return lEva&&rEva;
    }
    if(payload == EQUALITY){
      cout<<payload<<"\t eva root EQ\n";
      cout<<left->term->symbol()<<"\t eva left EQ\n";
      cout<<right->term->symbol()<<"\t eva right EQ\n";
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
