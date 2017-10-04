#ifndef UTTERM_H
#define UTTERM_H

#include <string>
#include "include/atom.h"
#include "include/number.h"
#include "include/variable.h"

using std::to_string;

//test Number.value()
TEST (Number,ctor) {
    Number n1(1);
    ASSERT_EQ(1, n1.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number n1(1);
    n1.setSymbol("NUM1");
    ASSERT_EQ("NUM1", n1.symbol());
}
/*
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
    //cout<<n1.value()<<"\t"<<v1.value()<<endl;
    //cout<<n2.value()<<"\t"<<v1.value()<<endl;
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom atom("tom");
    Number n1("NUM1","25")
    ASSERT_EQ(atom.match(n1));
}
// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom atom("tom");
    Variable var("X");
    ASSERT_EQ()
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Atom atom("tom");

}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Atom tom("tom");
    Atom jerry("jerry");
    Variable var();
    ASSERT_FALSE();
}

// ?- X = 5.
// X = 5.
TEST (Variable, matchSuccessToNumber) {
    Variable var();
    Number num();
    ASSERT_TRUE();
    ASSERT_EQ();
}

// ?- X=25, X= 100.
// false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
    Variable var();
    Number num();
}

// ?- X=tom, X= 25.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
    Variable var();
    Atom tom();
    Number num();

}
//?- tom=X, 25=X.
//false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {

}
//?- X=tom, X=tom.
//true.
TEST(Variable, reAssignTheSameAtom){
    Variable var();
    Atom tom();

}*/
#endif
