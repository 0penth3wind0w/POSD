#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>
#include <queue>
#include "struct.h"
#include "list.h"

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
  friend class Term;
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }
private:
  NullIterator(T t) : _term(t) {}
  T _term;
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
    // _index = 0;
  }
  void next(){
    if(!isDone()){
      if(_DFSStack.top()->currentItem()->createIterator()->isDone()){
        _DFSStack.top()->next();
        while(!isDone() && _DFSStack.top()->isDone()){
          _DFSStack.pop();
          if(!isDone()){
            _DFSStack.top()->next();
          }
        }
      }
      else{
        _DFSStack.push(currentItem()->createIterator());
      }
    }
  }
  Term* currentItem() const {
    return _DFSStack.top()->currentItem();
  }
  bool isDone() const { return _DFSStack.empty();}
private:
  DFSIterator(T t):_tptr(t){
    _DFSStack.push(_tptr->createIterator());
  };
  stack <Iterator<Term*> *> _DFSStack;
  // int _index;
  T _tptr;
};

template <class T>
class BFSIterator : public Iterator<T>{
public:
  friend class Struct;
  friend class List;
  void first(){
    // _index = 0;
  }
  void next(){
    if(!isDone()){
      if(!currentItem()->createIterator()->isDone()){
        _BFSQueue.push(currentItem()->createIterator());
      }
      _BFSQueue.front()->next();
      if(_BFSQueue.front()->isDone()){
        _BFSQueue.pop();
      }
    }
  }
  Term* currentItem() const {
    return _BFSQueue.front()->currentItem();
  }
  bool isDone() const { return _BFSQueue.empty();}
private:
  BFSIterator(T t):_tptr(t){
    _BFSQueue.push(_tptr->createIterator());
  };
  queue <Iterator<Term*> *> _BFSQueue;
  T _tptr;
};
#endif
