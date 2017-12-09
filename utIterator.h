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

//a(1, 2, b(tom, 3), jerry)
TEST(iterator,struct_dfs){
  Atom tom("tom"), jerry("jerry");
  Number one(1), two(2), three(3);
  Struct b(Atom("b"), {&tom, &three});
  Struct a(Atom("a"), {&one, &two, &b, &jerry});
  
  Iterator <Term*> *itDFSStruct = a.createDFSIterator();
  itDFSStruct->first();
  EXPECT_EQ("1", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("2", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("b(tom, 3)", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("tom", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("3", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("jerry", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_TRUE(itDFSStruct->isDone());
}

//a(X, [1, Y], b(tom), [2, jerry])
TEST(iterator,struct_dfs2){
  Atom tom("tom"), jerry("jerry");
  Number one(1), two(2);
  Variable X("X"), Y("Y");
  Struct b(Atom("b"),{&tom});
  List l1({&one, &Y}), l2({&two, &jerry});
  Struct a(Atom("a"),{&X, &l1, &b, &l2});

  Iterator <Term*> *itDFSStruct = a.createDFSIterator();
  itDFSStruct->first();
  
  EXPECT_EQ("X", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("[1, Y]", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("1", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("Y", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("b(tom)", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("tom", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("[2, jerry]", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("2", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_EQ("jerry", itDFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itDFSStruct->isDone());
  itDFSStruct->next();
  EXPECT_TRUE(itDFSStruct->isDone());

}

//a(1, 2, b(tom, 3), jerry)
TEST(iterator,struct_bfs){
  Atom tom("tom"), jerry("jerry");
  Number one(1), two(2), three(3);
  Struct b(Atom("b"), {&tom, &three});
  Struct a(Atom("a"), {&one, &two, &b, &jerry});
  
  Iterator <Term*> *itBFSStruct = a.createBFSIterator();
  itBFSStruct->first();
  ASSERT_EQ("1", itBFSStruct->currentItem()->symbol());
  ASSERT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  ASSERT_EQ("2", itBFSStruct->currentItem()->symbol());
  ASSERT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  ASSERT_EQ("b(tom, 3)", itBFSStruct->currentItem()->symbol());
  ASSERT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  ASSERT_EQ("jerry", itBFSStruct->currentItem()->symbol());
  ASSERT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  ASSERT_EQ("tom", itBFSStruct->currentItem()->symbol());
  ASSERT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  ASSERT_EQ("3", itBFSStruct->currentItem()->symbol());
  ASSERT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  ASSERT_TRUE(itBFSStruct->isDone());
}

//a(X, [1, Y], b(tom), [2, jerry])
TEST(iterator,struct_bfs2){
  Atom tom("tom"), jerry("jerry");
  Number one(1), two(2);
  Variable X("X"), Y("Y");
  Struct b(Atom("b"),{&tom});
  List l1({&one, &Y}), l2({&two, &jerry});
  Struct a(Atom("a"),{&X, &l1, &b, &l2});

  Iterator <Term*> *itBFSStruct = a.createBFSIterator();
  itBFSStruct->first();
  
  EXPECT_EQ("X", itBFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  EXPECT_EQ("[1, Y]", itBFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  EXPECT_EQ("b(tom)", itBFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  EXPECT_EQ("[2, jerry]", itBFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  EXPECT_EQ("1", itBFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  EXPECT_EQ("Y", itBFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  EXPECT_EQ("tom", itBFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  EXPECT_EQ("2", itBFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  EXPECT_EQ("jerry", itBFSStruct->currentItem()->symbol());
  EXPECT_FALSE(itBFSStruct->isDone());
  itBFSStruct->next();
  EXPECT_TRUE(itBFSStruct->isDone());
}

//[tom, [1, 2], jerry]
TEST(iterator,list_dfs){
  Atom tom("tom"), jerry("jerry");
  Number one(1), two(2);
  List num({&one, &two});
  List combo({&tom, &num, &jerry});
  
  Iterator <Term*> *itDFSList = combo.createDFSIterator();
  itDFSList->first();
  
  EXPECT_EQ("tom", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("[1, 2]", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("1", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("2", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("jerry", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_TRUE(itDFSList->isDone());
}

//[X, Y, tom(1, 2), [Z, 3, jerry], 4]
TEST(iterator,list_dfs2){
  Atom jerry("jerry");
  Number one(1), two(2), three(3), four(4);
  Variable X("X"), Y("Y"), Z("Z");
  Struct tom(Atom("tom"), {&one, &two});
  List inner({&Z, &three, &jerry});
  List combo({&X, &Y, &tom, &inner, &four});

  Iterator <Term*> *itDFSList = combo.createDFSIterator();
  itDFSList->first();
  
  EXPECT_EQ("X", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("Y", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("tom(1, 2)", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("1", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("2", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("[Z, 3, jerry]", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("Z", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("3", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("jerry", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_EQ("4", itDFSList->currentItem()->symbol());
  EXPECT_FALSE(itDFSList->isDone());
  itDFSList->next();
  EXPECT_TRUE(itDFSList->isDone());
}

//[tom, [1, 2], jerry]
TEST(iterator,list_bfs){
  Atom tom("tom"), jerry("jerry");
  Number one(1), two(2);
  List num({&one, &two});
  List combo({&tom, &num, &jerry});

  Iterator <Term*> *itBFSList = combo.createBFSIterator();
  itBFSList->first();
  
  EXPECT_EQ("tom", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("[1, 2]", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("jerry", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("1", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("2", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_TRUE(itBFSList->isDone());
}

//[X, Y, tom(1, 2), [Z, 3, jerry], 4]
TEST(iterator,list_bfs2){
  Atom jerry("jerry");
  Number one(1), two(2), three(3), four(4);
  Variable X("X"), Y("Y"), Z("Z");
  Struct tom(Atom("tom"), {&one, &two});
  List inner({&Z, &three, &jerry});
  List combo({&X, &Y, &tom, &inner, &four});

  Iterator <Term*> *itBFSList = combo.createBFSIterator();
  itBFSList->first();

  EXPECT_EQ("X", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("Y", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("tom(1, 2)", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("[Z, 3, jerry]", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("4", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("1", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("2", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("Z", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("3", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_EQ("jerry", itBFSList->currentItem()->symbol());
  EXPECT_FALSE(itBFSList->isDone());
  itBFSList->next();
  EXPECT_TRUE(itBFSList->isDone());
}

//combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
// TEST(iterator,combo_dfs){
//   Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"), sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"), pickleSlice2("pickleSlice2"), onions1("onions1"), onions2("onions2"), fries1("fries1"), fries2("fries2");
//   List pickleSlice({&pickleSlice1, &pickleSlice2});
//   List onions({&onions1,&onions2});
//   Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce, &cheese, &pickleSlice, &onions});
//   Atom coke("coke");
//   List fries({&fries1, &fries2});
//   Struct combo1(Atom("Combo1"), {&bigMac, &coke,&fries});

//   Iterator <Term*> *itDFSCombo = combo1.createDFSIterator();
//   itDFSCombo->first();

//   EXPECT_EQ("bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onions1, onions2])", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("bun", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("beefPatty", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("shreddedLettuce", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("sauce", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("cheese", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("[pickleSlice1, pickleSlice2]", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("pickleSlice1", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("pickleSlice2", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("[onions1, onions2]", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("onions1", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("onions2", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("coke", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("[fries1, fries2]", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("fries1", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
//   EXPECT_EQ("fries2", itDFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itDFSCombo->isDone());
//   itDFSCombo->next();
// }

//combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice, pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
// TEST(iterator,combo_bfs){
//   Atom bun("bun"), beefPatty("beefPatty"), shreddedLettuce("shreddedLettuce"), sauce("sauce"), cheese("cheese"), pickleSlice1("pickleSlice1"), pickleSlice2("pickleSlice2"), onions1("onions1"), onions2("onions2"), fries1("fries1"), fries2("fries2");
//   List pickleSlice({&pickleSlice1, &pickleSlice2});
//   List onions({&onions1,&onions2});
//   Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce, &cheese, &pickleSlice, &onions});
//   Atom coke("coke");
//   List fries({&fries1, &fries2});
//   Struct combo1(Atom("Combo1"), {&bigMac, &coke,&fries});

//   Iterator <Term*> *itBFSCombo = combo1.createBFSIterator();
//   itBFSCombo->first();

//   EXPECT_EQ("bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onions1, onions2])", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("coke", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("[fries1, fries2]", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("bun", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("beefPatty", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("shreddedLettuce", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("sauce", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("cheese", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("[pickleSlice1, pickleSlice2]", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("[onions1, onions2]", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("fries1", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("fries2", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("pickleSlice1", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("pickleSlice2", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("onions1", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
//   EXPECT_EQ("onions2", itBFSCombo->currentItem()->symbol());
//   EXPECT_FALSE(itBFSCombo->isDone());
//   itBFSCombo->next();
// }
#endif
