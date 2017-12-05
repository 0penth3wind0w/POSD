#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "term.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "variable.h"
#include "list.h"
#include "iterator.h"

//s(1, t(X, 2), Y)
TEST(iterator, first) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator <Term*> *itStruct = s.createIterator();
  itStruct->first();
  ASSERT_EQ("1", itStruct->currentItem()->symbol());
  ASSERT_FALSE(itStruct->isDone());
  itStruct->next();
  ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
  ASSERT_FALSE(itStruct->isDone());
  itStruct->next();
  ASSERT_EQ("Y", itStruct->currentItem()->symbol());
  itStruct->next();
  ASSERT_TRUE(itStruct->isDone());
}

//s(1, t(X, 2), Y)
TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });

  Iterator <Term*> *itStruct = s.createIterator();
  itStruct->first();
  ASSERT_EQ("1", itStruct->currentItem()->symbol());
  ASSERT_FALSE(itStruct->isDone());
  
  itStruct->next();
  Iterator <Term*> *itStruct2 = itStruct->currentItem()->createIterator();
  
  ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
  ASSERT_FALSE(itStruct->isDone());
  itStruct->next();
  ASSERT_EQ("Y", itStruct->currentItem()->symbol());
  itStruct->next();
  ASSERT_TRUE(itStruct->isDone());
  
  itStruct2->first();
  ASSERT_EQ("X", itStruct2->currentItem()->symbol());
  ASSERT_FALSE(itStruct2->isDone());
  itStruct2->next();
  ASSERT_EQ("2", itStruct2->currentItem()->symbol());
  ASSERT_FALSE(itStruct2->isDone());
  itStruct2->next();
  ASSERT_TRUE(itStruct2->isDone());
}

//[1, t(X, 2), Y]
TEST(iterator, firstList) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  List l({ &one, &t, &Y });
  Iterator <Term*> *itList = l.createIterator();
  itList->first();
  
  ASSERT_EQ("1", itList->currentItem()->symbol());
  ASSERT_FALSE(itList->isDone());
  itList->next();
  ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
  ASSERT_FALSE(itList->isDone());
  itList->next();
  ASSERT_EQ("Y", itList->currentItem()->symbol());
  itList->next();
  ASSERT_TRUE(itList->isDone());
}

//1
TEST(iterator, NullIterator){
  Number one(1);
  Iterator <Term*> *itTerm = one.createIterator();
  itTerm->first();
  ASSERT_TRUE(itTerm->isDone());
}

TEST(iterator,struct_bfs){

}
TEST(iterator,struct_bfs2){

}
TEST(iterator,struct_dfs){

}
TEST(iterator,struct_dfs2){

}
TEST(iterator,list_bfs){

}
TEST(iterator,list_bfs2){

}
TEST(iterator,list_dfs){

}
TEST(iterator,list_dfs2){

}
#endif
