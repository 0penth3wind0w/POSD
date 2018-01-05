#ifndef EXP_H
#define EXP_H

#include <iostream>
#include <string>

#include "atom.h"

using std::cout;
using std::string;

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string result() = 0;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){
    return _left->match(*_right);
  }

  string result(){
    if (evaluate() && _left->symbol() == _right->symbol()){
      return "true";
    }
    else if (!evaluate()){
      return "false";
    }
    else
      return _left->symbol() + " = " + _right->value();
  }

private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

  string result(){
    evaluate();
    if (_left->result() == "true" && _right->result() == "true"){
      return "true";
    }
    else if (_left->result() == "false" || _right->result() == "false"){
      return "false";
    }
    else if (_left->result() == "true"){
      return _right->result();
    }
    else if (_right->result() == "true"){
      return _left->result();
    }
    else if (_left->result().find(_right->result()) != string::npos){
      return _left->result();
    }
    else{
      return _left->result() + ", " + _right->result();
    }
  }

private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

  string result(){
    evaluate();
    if ( _left->result() == "false"){
      return _right->result();
    }
    else if ( _right->result() == "false"){
      cout<<"HAHAHA\n";
      return _left->result();
    }
    else{
      return _left->result() + "; " + _right->result();
    }
  }

private:
  Exp * _left;
  Exp * _right;
};
#endif
