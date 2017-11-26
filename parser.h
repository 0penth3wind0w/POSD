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

// class Parser{
// public:
//   Parser(Scanner scanner) : _scanner(scanner), _terms(){}

//   Term* createTerm(){
//     int token = _scanner.nextToken();
//     _currentToken = token;
//     if(token == VAR){
//       return new Variable(symtable[_scanner.tokenValue()].first);
//     }else if(token == NUMBER){
//       return new Number(_scanner.tokenValue());
//     }else if(token == ATOM || token == ATOMSC){
//       Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
//       if(_scanner.currentChar() == '(' ) {
//         return structure();
//       }
//       else
//         return atom;
//     }
//     else if(token == '['){
//       return list();
//     }

//     return nullptr;
//   }

//   Term * structure() {
//     Atom structName = Atom(symtable[_scanner.tokenValue()].first);
//     int startIndexOfStructArgs = _terms.size();
//     _scanner.nextToken();
//     createTerms();
//     if(_currentToken == ')')
//     {
//       vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
//       _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
//       return new Struct(structName, args);
//     } else {
//       throw string("unexpected token");
//     }
//   }

//   Term * list() {
//     int startIndexOfListArgs = _terms.size();
//     createTerms();
//     if(_currentToken == ']')
//     {
//       vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
//       _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
//       return new List(args);
//     } else {
//       throw string("unexpected token");
//     }
//   }

//   vector<Term *> & getTerms() {
//     return _terms;
//   }

//   void matchings(){
//     Node *subTree;
//     Term* term = createTerm();
//     if(term!=nullptr)
//     {
//       _terms.push_back(term);
//       while((_currentToken = _scanner.nextToken()) == ','||(_currentToken  == ';')||(_currentToken  == '=')){
//         if(_currentToken  == ';'){
//           Node *l = subTree;
//           matchings();
//           Node *r = _parseTree;
          
//           Node *parseTree = new Node(SEMICOLON);
//           parseTree->left = l;
//           parseTree->right = r;
//           subTree = parseTree;
//         }
//         else if(_currentToken  == ','){
//           Node *l = subTree;
//           matchings();
//           Node *r = _parseTree;
          
//           Node *parseTree = new Node(COMMA);
//           parseTree->left = l;
//           parseTree->right = r;
//           subTree = parseTree;

//           for(int i=0; i<_terms.size()-1; ++i){
//             Variable *ps = dynamic_cast<Variable *>(_terms[i]);
//             if(ps){
//               cout<<_terms[i]->symbol()<<"\tsymbol_i\n";
//               for(int j=i+1; j<_terms.size()-1; ++j){
//                 Variable *ps2 = dynamic_cast<Variable *>(_terms[j]);
//                 if(ps2){
//                   if(ps->symbol()==ps2->symbol()){
//                     cout<<ps->symbol()<<"\t"<<ps2->symbol()<<"\ttwo_symbol\n";
//                     cout<<"parseHere5\n";
//                     _terms[i]->match(*_terms[j]);
//                     //_terms[j]=_terms[i];
//                     cout<<"parseHere6\n";
//                   }
//                 }
//               }
//             }
//           }
//         }
//         else if(_currentToken == '='){
//           Node *l = new Node(TERM);
//           l->term = _terms.back();
//           _terms.push_back(createTerm());
//           Node *r = new Node(TERM);
//           r->term = _terms.back();
//           Node *parseTree = new Node(EQUALITY);
//           parseTree->left = l;
//           parseTree->right = r;
//           subTree = parseTree;
//         }
//       }
//     }
//     if(symtable.back().first == "."){
//       symtable.pop_back();
//     }
//     _parseTree = subTree;
//   }
  
//   Node *expressionTree(){
//     return _parseTree;
//   }

// private:
//   FRIEND_TEST(ParserTest, createArgs);
//   FRIEND_TEST(ParserTest,ListOfTermsEmpty);
//   FRIEND_TEST(ParserTest,listofTermsTwoNumber);
//   FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

//   void createTerms() {
//     Term* term = createTerm();
//     if(term!=nullptr)
//     {
//       _terms.push_back(term);
//       while((_currentToken = _scanner.nextToken()) == ','||(_currentToken  == '=')){
//         _terms.push_back(createTerm());
//       }
//     }
//   }

//   vector<Term *> _terms;
//   Scanner _scanner;
//   int _currentToken;
//   Node *_parseTree;
// };
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
    Term* term = createTerm();
    if(term!=nullptr)
    { 
      if(isCOMMA==1){
        cout<<"is comma, find "<<term->symbol()<<"\n";
        Term * findTerm = find(term);
        if(findTerm != nullptr) term->match(*findTerm);
      }
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',' ||  _currentToken=='='|| _currentToken == ';') {
        if (_currentToken == '=') {
          isCOMMA = 0;
          Node * left = new Node(TERM, _terms.back(), nullptr, nullptr);
          _terms.push_back(createTerm());          
          Node * right = new Node(TERM, _terms.back(), nullptr, nullptr);
          Node * root = new Node(EQUALITY, nullptr, left, right);
          _expressionTree = root;
          // for(int i = 0; i<_terms.size();++i){
          //   Struct * s = dynamic_cast<Struct*>(_terms[i]);
          //   if(s){
          //     if(s->args(i)->isVar() && s->args(i)->symbol()==_terms.back()->symbol()){
          //       s->args(i)->match(*(_terms.back()));
          //     }
          //   }
          // }
        }
        else if(_currentToken == ','){
          isCOMMA = 1;
          Node * left = _expressionTree;
          matchings();
          Node * root = new Node(COMMA, nullptr, left, expressionTree());
          _expressionTree = root;
          
        }
        else if(_currentToken == ';'){
          isCOMMA = 0;
          Node * left = _expressionTree;
          matchings();
          Node * root = new Node(SEMICOLON, nullptr, left, expressionTree());
          _expressionTree = root;
        }
      }
    }
    if(symtable.back().first == "."){
      symtable.pop_back();
    }
  }

  Term * find(Term * term){
    for(int index = 0; index < _terms.size() ; index++){
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

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  Node * _expressionTree;
  int isCOMMA = 0;
};
#endif
