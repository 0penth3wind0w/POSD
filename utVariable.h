#ifndef UTVARIABLE_H
#define UTVARIABLE_H

#include "variable.h"
#include "atom.h"

TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X._symbol);

}

TEST(Variable , matching){
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}

TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

TEST (Variable , setValue){
  Variable X("X");
  X.setValue("123");
  ASSERT_EQ("123", X.value());
}

#endif
