#ifndef UTTERM_H
#define UTTERM_H

#include <string>
#include "atom.h"
#include "number.h"
#include "variable.h"

using std::to_string;

//test Number.value()
TEST (Number,ctor) {
    Number num(1);
    ASSERT_EQ("1", num.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number num(1);
    num.setSymbol("NUM1");
    ASSERT_EQ("NUM1", num.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number num1(25);
    Number num2(25);
    ASSERT_TRUE( num1.match(num2) );
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number num1(25);
    Number num2(0);
    ASSERT_FALSE( num1.match(num2) );
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Atom atom("tom");
    Number num(25);
    ASSERT_FALSE( num.match(atom) );
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number num(25);
    Variable var("VAR1");
    ASSERT_TRUE(num.match(var));
    ASSERT_EQ(num.value(), var.value());
}
//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom atom("tom");
    Number n1(25);
    ASSERT_FALSE(atom.match(n1));
}
// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom atom("tom");
    Variable var("X");
    ASSERT_TRUE(atom.match(var));
    ASSERT_EQ(atom.symbol(), var.value());
}
// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Atom atom("tom");
    Variable var("X");
    ASSERT_TRUE(atom.match(var));
    ASSERT_EQ(atom.symbol(), var.value());
    ASSERT_TRUE(atom.match(var));
}
// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Atom tom("tom");
    Atom jerry("jerry");
    Variable var("X");
    var.match(jerry);
    ASSERT_FALSE(var.match(tom));
}
// ?- X = 5.
// X = 5.
TEST (Variable, matchSuccessToNumber) {
    Variable var("X");
    Number num(5);
    var.match(num);
    ASSERT_TRUE(var.match(num));
}
// ?- X=25, X= 100.
// false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
    Variable var("X");
    Number num1(25);
    Number num2(100);
    ASSERT_TRUE(var.match(num1));
    ASSERT_FALSE(var.match(num2));
}
// ?- X=tom, X= 25.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
    Variable var("X");
    Atom tom("tom");
    Number num(25);
    var.match(tom);
    ASSERT_FALSE(var.match(num));
}
//?- tom=X, 25=X.
//false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {
    Variable var("X");
    Atom tom("tom");
    Number num(25);
    var.match(tom);
    ASSERT_FALSE(var.match(num));
}
//?- X=tom, X=tom.
//true.
TEST(Variable, reAssignTheSameAtom){
    Variable var("X");
    Atom tom("tom");
    var.match(tom);
    ASSERT_EQ(tom.symbol(),var.value());
    ASSERT_TRUE(var.match(tom));
}

#endif