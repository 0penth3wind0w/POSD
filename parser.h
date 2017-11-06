#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>

#include "atom.h"
#include "variable.h"
#include "number.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"

using std::cout;
using std::string;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  Term* createTerm(){
    cout<<"in\t";
    int token = _scanner.nextToken();
    cout<<token<<"\n";
    if(token == VAR){
      cout<<symtable[_scanner.tokenValue()].first<<"VAR \n";
      return new Variable(symtable[_scanner.tokenValue()].first);
    }
    else if(token == NUMBER){
      cout<<_scanner.tokenValue()<<" NUMBER\n";
      return new Number(_scanner.tokenValue());
    }
    else if(token == ATOM){
      cout<<"atom\n";
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
      int i = _scanner.tokenValue();
      cout<<i<<" i\n";
      if(i == ']'){
        cout<<"empty\n";
        return new List();
      }
      else{
        cout<<"non empty\n";
        vector<Term*> terms = getArgs();
        //cout<<terms[0]->symbol();
        int tmp = _currentToken;
        cout<<tmp<<" tmp\n";
        if(tmp == ']'){
          cout<<"non empty2\n";
          return new List(terms);
        }
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