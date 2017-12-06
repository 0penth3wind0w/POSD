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

//combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice, pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
TEST(iterator,struct_bfs){
  Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"), sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"), pickleSlice2("pickleSlice2"), onions1("onions1"), onions2("onions2"), fries1("fries1"), fries2("fries2");
  List pickleSlice({&pickleSlice1, &pickleSlice2});
  List onions({&onions1,&onions2});
  Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce, &cheese, &pickleSlice, &onions});
  Atom coke("coke");
  List fries({&fries1, &fries2});
  Struct combo1(Atom("Combo1"), {&bigMac, &coke,&fries});
}
TEST(iterator,struct_bfs2){

}

//combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice, pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
TEST(iterator,struct_dfs){
  Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"), sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"), pickleSlice2("pickleSlice2"), onions1("onions1"), onions2("onions2"), fries1("fries1"), fries2("fries2");
  List pickleSlice({&pickleSlice1, &pickleSlice2});
  List onions({&onions1,&onions2});
  Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce, &cheese, &pickleSlice, &onions});
  Atom coke("coke");
  List fries({&fries1, &fries2});
  Struct combo1(Atom("Combo1"), {&bigMac, &coke,&fries});
}
TEST(iterator,struct_dfs2){

}

//combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice, pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
TEST(iterator,list_bfs){
  Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"), sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"), pickleSlice2("pickleSlice2"), onions1("onions1"), onions2("onions2"), fries1("fries1"), fries2("fries2");
  List pickleSlice({&pickleSlice1, &pickleSlice2});
  List onions({&onions1,&onions2});
  Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce, &cheese, &pickleSlice, &onions});
  Atom coke("coke");
  List fries({&fries1, &fries2});
  Struct combo1(Atom("Combo1"), {&bigMac, &coke,&fries});
}
TEST(iterator,list_bfs2){

}

//combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice, pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
TEST(iterator,list_dfs){
  Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"), sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"), pickleSlice2("pickleSlice2"), onions1("onions1"), onions2("onions2"), fries1("fries1"), fries2("fries2");
  List pickleSlice({&pickleSlice1, &pickleSlice2});
  List onions({&onions1,&onions2});
  Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce, &cheese, &pickleSlice, &onions});
  Atom coke("coke");
  List fries({&fries1, &fries2});
  Struct combo1(Atom("Combo1"), {&bigMac, &coke,&fries});
}
TEST(iterator,list_dfs2){

}
#endif
