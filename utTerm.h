#ifndef UTTERM_H
#define UTTERM_H
#include <iostream>
#include "Number.h"
#include "Variable.h"

using std::cout;
using std::endl;

//test Number.value()
TEST (Number,ctor) {
    Number n1("NUM1","1");
    ASSERT_EQ("1", n1.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number n1("NUM1","1");
    ASSERT_EQ("NUM1", n1.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number n1("NUM1","25");
    Number n2("NUM1","25");
    ASSERT_TRUE( n1.match(n2) );
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number n1("NUM1","25");
    Number n2("NUM2","0");
    ASSERT_FALSE( n1.match(n2) );
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Atom atom("tom");
    Number n1("NUM1","25");
    ASSERT_FALSE( n1.match(atom) );
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number n1("NUM1", "25");
    Number n2("NUM2", "50");
    Variable v1("VAR1");
    EXPECT_TRUE(n1.match(v1));
    EXPECT_EQ(n1.value(),v1.value());

    EXPECT_FALSE(n2.match(v1));
    cout<<n1.value()<<"\t"<<v1.value()<<endl;
    cout<<n2.value()<<"\t"<<v1.value()<<endl;
}
/*
//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom atom("tom");
    Number n1("NUM1","25")
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom atom("tom");
    Variable var("X");
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Atom atom()
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {

}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
 
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {

}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {

}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {

}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){

}*/
#endif
