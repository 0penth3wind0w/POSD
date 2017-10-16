#ifndef UTATOM_H
#define UTATOM_H

#include "atom.h"
#include "number.h"

TEST(Atom, first) {
  ASSERT_TRUE(true);
}

TEST(Atom, tom) {
  Atom tom("tom");
  ASSERT_EQ("tom", tom.symbol());
}

TEST(Atom, match_tom_and_jerry) {
  Atom tom("tom");
  Atom jerry("jerry");
  //EXPECT_FALSE(tom == jerry);
  ASSERT_TRUE( tom.match(tom) );
}

TEST(Atom, value)
{
  Atom tom("tom");
  EXPECT_EQ("tom", tom.value());
}

/*TEST(Atom, Virtual)
{
  Term* t = new Atom("tom");
  EXPECT_EQ("tom", t->value());
}*/

/*TEST(Atom, match_tom_and_number) {
  Atom tom("tom");
  Number n1(1);
  ASSERT_FALSE( tom.match(n1) );
}

TEST(Atom, match_tom_and_variable) {
  Atom tom("tom");
  Atom jerry("jerry");
  Variable var("var");
  ASSERT_TRUE( tom.match(var) );
  ASSERT_EQ(tom.symbol(), var.value());
  ASSERT_FALSE( jerry.match(var) );
}*/

#endif
