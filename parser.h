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
#include "exp.h"
#include <stack>

using std::stack;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(), _startIndex(0) {}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      for (int i = _startIndex; i < _vars.size(); i++)
        if (symtable[_scanner.tokenValue()].first == _vars[i]->symbol())
          return _vars[i];
      Variable *variable = new Variable(symtable[_scanner.tokenValue()].first);
      _vars.push_back(variable);
      return variable;
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
    }
    else if(_currentToken == ';'){
      throw string("Unbalanced operator");
    }
    else {
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
      if(args.size()==0){
        return new Atom("[]");
      }
      return new List(args);
    }
    else if(_currentToken == ';'){
      throw string("Unbalanced operator");
    }
    else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  Exp *buildExpression()
  {
    if (_scanner.getContext().find(";.") != string::npos){
      throw string("Unexpected ';' before '.'");
    } 
    if (_scanner.getContext().find(",.") != string::npos){
      throw string("Unexpected ',' before '.'");
    }
    disjunctionMatch();
    restDisjunctionMatch();
    if (createTerm() != nullptr || _currentToken != '.'){
      throw string("Missing token '.'");
    }
    return _expStack.top();
  }


  void restDisjunctionMatch() {
    if (_scanner.currentChar() == ';'){
      _startIndex = _vars.size();
      createTerm();
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch() {
    conjunctionMatch();
    restConjunctionMatch();
  }

  void restConjunctionMatch() {
    if (_scanner.currentChar() == ',') {
      createTerm();
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch() {
    Term * left = createTerm();
    if (createTerm() == nullptr && _currentToken == '=') {
      Term * right = createTerm();
      _expStack.push(new MatchExp(left, right));
    }
    else{
      throw string(left->symbol() + " does never get assignment");
    }
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }

private:
  // FRIEND_TEST(ParserTest, createArgs);
  // FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  // FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  // FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  // FRIEND_TEST(ParserTest, createTerms);

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

  vector<Term *> _terms;
  vector<Variable *> _vars;
  Scanner _scanner;
  int _currentToken;
  //MatchExp* _root;
  stack<Exp*> _expStack;
  int _startIndex;
};
#endif