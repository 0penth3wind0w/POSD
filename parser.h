#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include "utParser.h"

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
        Term *returnStruct = structure();
        return returnStruct;
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
    Struct *outputStruct;
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      outputStruct = new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
    return outputStruct;
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    List *outputList;
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      outputList = new List(args);
    } else {
      throw string("unexpected token");
    }
    return outputList;
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void matchings(){
    Term* term = createTerm();
    if(term!=nullptr)
    { 
      if(_isCOMMA==1){
        Term * findTerm = find(term);
        if(findTerm != nullptr) term->match(*findTerm);
      }
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',' ||  _currentToken=='='|| _currentToken == ';') {
        if (_currentToken == '=') {
          _isCOMMA = 0;
          Node * left = new Node(TERM, _terms.back(), nullptr, nullptr);
          _terms.push_back(createTerm());          
          Node * right = new Node(TERM, _terms.back(), nullptr, nullptr);
          Node * root = new Node(EQUALITY, nullptr, left, right);
          _expressionTree = root;
        }
        else if(_currentToken == ','){
          _isCOMMA = 1;
          Node * left = _expressionTree;
          matchings();
          Node * root = new Node(COMMA, nullptr, left, expressionTree());
          _expressionTree = root;
          
        }
        else if(_currentToken == ';'){
          _isCOMMA = 0;
          Node * left = _expressionTree;
          //here to test left recursive match
          for(int i = _startIndex; i < _terms.size(); i++){
            Struct * s = dynamic_cast<Struct*>(_terms[i]);
            if(s){
              for(int j = _startIndex; j < _terms.size(); j++){
                Variable * v = dynamic_cast<Variable*>(_terms[j]);
                if(v){
                  for(int i = 0; i < s->arity(); i++){
                    if(s->args(i)->value() != v->value()){
                      Term *f = findStruct(s, v);
                      if(f != nullptr ){
                        v->match(*f);
                      }
                    }
                  }
                }
              }
            }
          }
          _startIndex = _terms.size();
          matchings();
          Node * root = new Node(SEMICOLON, nullptr, left, expressionTree());
          _expressionTree = root;
          //here to test left recursive match
          for(int i = _startIndex; i < _terms.size(); i++){
            Struct * s = dynamic_cast<Struct*>(_terms[i]);
            if(s){
              for(int j = _startIndex; j < _terms.size(); j++){
                Variable * v = dynamic_cast<Variable*>(_terms[j]);
                if(v){
                  for(int i = 0; i < s->arity(); i++){
                    if(s->args(i)->value() != v->value()){
                      Term *f = findStruct(s, v);
                      if(f != nullptr ){
                        v->match(*f);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  Term * find(Term * term){
    for(int index = _startIndex; index < _terms.size() ; index++){
      if(_terms[index]->symbol() == term->symbol()) return _terms[index];
      Struct * s = dynamic_cast<Struct*>(_terms[index]);
      if(s) {
        return findStruct(s,term);
      }
    }
    return nullptr;
  }

  Term * findStruct(Struct * s, Term * term){
    for(int i = 0; i < s->arity() ; i++){
      if(s->args(i)->symbol() == term->symbol()) return s->args(i);
      Struct * ss = dynamic_cast<Struct*>(s->args(i));
      if(ss) {
        return findStruct(ss,term);
      }
    }
  }

  Node * expressionTree(){
    return _expressionTree;
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
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }
  void createStruct() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  Node * _expressionTree;
  int _isCOMMA = 0;
  int _startIndex = 0;
};
#endif
