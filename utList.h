#ifndef UTLIST_H
#define UTLIST_H

#include <string>
#include <vector>

#include "term.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "list.h"

using std::string;

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST(List, constructor) {
    List *l = new List();
    EXPECT_EQ("[]", l->symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
    Number num1(496);
    Number num2(8128);
    std::vector<Term *> vec = {&num1, &num2};
    List numlist(vec);
    EXPECT_EQ("[496, 8128]", numlist.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  std::vector<Term *> vec = {&terence_tao, &alan_mathison_turing};
  List atomlist(vec);
  EXPECT_EQ("[terence_tao, alan_mathison_turing]", atomlist.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X");
  Variable Y("Y");
  std::vector<Term *> vec = {&X, &Y};
  List varlist(vec);
  EXPECT_EQ("[X, Y]", varlist.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Atom tom("tom");
  Number num1(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> vec = {&num1, &X, &terence_tao};
  List compact(vec);
  EXPECT_FALSE(tom.match(compact));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number num1(8128);
  Number num2(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> vec = {&num2, &X, &terence_tao};
  List compact(vec);
  EXPECT_FALSE(num1.match(compact));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Variable X("X");
  std::vector<Term *> vec = {&X};
  Struct s(Atom("s"),vec);
  Number num1(496);
  Atom terence_tao("terence_tao");
  std::vector<Term *> vec1 = {&num1, &X, &terence_tao};
  List compact(vec1);
  EXPECT_FALSE(s.match(compact));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Variable Y("Y");
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> vec = {&num, &X, &terence_tao};
  List compact(vec);
  EXPECT_TRUE(Y.match(compact));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  EXPECT_TRUE(false);
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> vec = {&num, &X, &terence_tao};
  List compact(vec);
  EXPECT_TRUE(compact.match(compact));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number num(496);
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  std::vector<Term *> vec1 = {&num, &X, &terence_tao};
  std::vector<Term *> vec2 = {&num, &Y, &terence_tao};
  List compactX(vec1);
  List compactY(vec2);
  EXPECT_TRUE(compactX.match(compactY));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number num1(496);
  Number num2(8128);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> vec1 = {&num1, &X, &terence_tao};
  std::vector<Term *> vec2 = {&num1, &num2, &terence_tao};
  List compactX(vec1);
  List compactY(vec2);
  EXPECT_TRUE(compactX.match(compactY));
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  Number num(496);
  Variable X("X");
  Variable Y("Y");
  std::vector<Term *> vec = {&num, &X, &terence_tao};
  List compact(vec);
  X.match(alan_mathison_turing);
  EXPECT_TRUE(Y.match(compact));
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args1 = {&f};
  List l(args1);
  vector<Term *> args = {&l, &s, &t};
  List l2(args);
  EXPECT_EQ(string("[first]"), l2.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  List *l = new List();
  EXPECT_TRUE(false);
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  List *l = new List();
  EXPECT_TRUE(false);
}




#endif