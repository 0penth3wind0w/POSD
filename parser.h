#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>

#include "term.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "list.h"
#include "global.h"
#include "scanner.h"
#include "node.h"

using std::string;

using std::cout;
//#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void matchings(){
    Node *subTree;
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ','||(_currentToken  == ';')||(_currentToken  == '=')){
        Operators op;
        if(_currentToken  == ';'){
          op = SEMICOLON;
        }
        else if(_currentToken  == ','){
          Node *l = subTree;
          matchings();
          Node *r = _parseTree;
          
          Node *parseTree = new Node(COMMA);
          parseTree->left = l;
          parseTree->right = r;
          subTree = parseTree;
        }
        else if(_currentToken == '='){
          Node *l = new Node(TERM);
          l->term = _terms.back();
          _terms.push_back(createTerm());
          Node *r = new Node(TERM);
          r->term = _terms.back();
          Node *parseTree = new Node(EQUALITY);
          parseTree->left = l;
          parseTree->right = r;
          subTree = parseTree;
        }
      }
    }
    _parseTree = subTree;
  }

  Node *expressionTree(){
    return _parseTree;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ','||(_currentToken  == '=')){
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  Node *_parseTree;
};
#endif
