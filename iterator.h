#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <stack>
#include <queue>
#include "struct.h"
#include "list.h"

using std::cout;
using std::stack;
using std::queue;

template <class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template <class T>
class NullIterator :public Iterator<T> {
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

template <class T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;
  void first(){_index = 0;}
  Term* currentItem() const {
    return _s->args(_index);
  }
  bool isDone() const {
    return _index >= _s->arity();
  }
  void next(){_index++;}
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template <class T>
class ListIterator :public Iterator<T> {
public:
  friend class List;
  void first(){_index = 0;}
  Term* currentItem() const {
    return _list->args(_index);
  }
  bool isDone() const {
    return _index >= _list->arity();
  }
  void next(){_index++;}
private:
  ListIterator(List *list): _index(0), _list(list) {}
  int _index;
  List* _list;
};

template <class T>
class DFSIterator : public Iterator<T>{
public:
  friend class Struct;
  friend class List;
  void first(){
    //  _index = 0;
  }
  void next(){
    if(!isDone()){
      while(currentItem()->createIterator()->isDone()){
        _DFSStack.top()->next();
        if (_DFSStack.top()->isDone())
        {
          _DFSStack.pop();
          if (!isDone()){
            _DFSStack.top()->next();
          }
        }
      }
    }
    else{
      _DFSStack.push(currentItem()->createIterator());
    }
  }
  Term* currentItem() const {
    return _DFSStack.top()->currentItem();
  }
  bool isDone() const { return _DFSStack.empty();}
private:
  DFSIterator(T t):_tptr(t){
    _DFSStack.push(_tptr->createIterator());
    cout<<_tptr->symbol()<<"\tDFSIterator\n";
  };
  stack <Iterator<Term*> *> _DFSStack;
  // int _index;
  T _tptr;
};

// template <class T>
// class BFSIterator : public Iterator<T>{
// public:
//   friend class Struct;
//   friend class List;
//   void first(){}
//   void next(){}
//   Term* currentItem(){}
//   bool isDone(){}
// private:
//   queue <Iterator<Term*> *> _BFSQueue;
// };
#endif
