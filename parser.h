#ifndef PARSER_H
#define PARSER_H

//#include <iostream>
#include <string>

#include "atom.h"
#include "variable.h"
#include "number.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"

//using std::cout;
using std::string;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken=token;
    //cout<<"in\t"<<token<<"\n";
    if(token == VAR){
      //cout<<symtable[_scanner.tokenValue()].first<<"VAR \n";
      return new Variable(symtable[_scanner.tokenValue()].first);
    }
    else if(token == NUMBER){
      //cout<<_scanner.tokenValue()<<" NUMBER\n";
      return new Number(_scanner.tokenValue());
    }
    else if(token == ATOM){
      //cout<<"atom\n";
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        _scanner.nextToken() ;
        vector<Term*> terms = getArgs();
        if(_currentToken == ')')
          return new Struct(*atom, terms);
      }
      else
        return atom;
    }
    else if(token == ATOMSC){
      //cout<<"atomsc\n";
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        _scanner.nextToken() ;
        vector<Term*> terms = getArgs();
        if(_currentToken == ')')
          return new Struct(*atom, terms);
      }
      else
        return atom;
    }
    else if(token == '['){
      vector<Term*> terms = getArgs();
      if(_currentToken == ']'){
        List* l = new List(terms);
        return l;
      }
      if(_currentToken == ')'){
        throw std::string( "unexpected token" );
      }
    }      
    return nullptr;
  }

  vector<Term*> getArgs()
  {
    Term* term = createTerm();
    vector<Term*> args;
    if(term)
      args.push_back(term);
    if((_currentToken == ']' || _currentToken == ')') && term == nullptr){
        return args;
    }
    while((_currentToken = _scanner.nextToken()) == ',') {
      args.push_back(createTerm());
    }
    return args;
  }



private:
  Scanner _scanner;
  int _currentToken;
};
#endif