#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

TEST (Sort, sortByIncreasingPerimeter) {
    Rectangle r1(0.0, 0.0, 1.0, 2.0, "r1");
    Rectangle r2(0.0, 0.0, 2.0, 4.0, "r2");
    
    Circle c1(0.0, 0.0, 1.0, "c1");
    Circle c2(0.0, 0.0, 2.0, "c2");
    
    vertex t1_1 = {0.0, 0.0}, t1_2 = { 1.0, 0.0 }, t1_3 = { 0.0, 1.0 };
    Triangle t1( t1_1, t1_2, t1_3, "t1");
    vertex t2_1 = {0.0, 0.0}, t2_2= { 2.0, 0.0 }, t2_3= { 0.0, 2.0 };
    Triangle t2( t2_1, t2_2, t2_3, "t2");

    std::list<Shape *> Shapes;
    Shapes.push_back (&r1);
    Shapes.push_back (&r2);
    Shapes.push_back (&c1);
    Shapes.push_back (&c2);
    Shapes.push_back (&t1);
    Shapes.push_back (&t2);

    Sort::sortByIncreasingPerimeter( &Shapes );

    ASSERT_EQ(&t1, Shapes.front());  // compare the address
    Shapes.pop_front();
    ASSERT_EQ(&r1, Shapes.front());
    Shapes.pop_front();
    ASSERT_EQ(&c1, Shapes.front());
    Shapes.pop_front();
    ASSERT_EQ(&t2, Shapes.front());
    Shapes.pop_front();
    ASSERT_EQ(&r2, Shapes.front());
    Shapes.pop_front();
    ASSERT_EQ(&c2, Shapes.front());
    Shapes.pop_front();
}

TEST (Sort, sortByDecreasingPerimeter) {
    Rectangle r1(0.0, 0.0, 1.0, 2.0, "r1");
    Rectangle r2(0.0, 0.0, 2.0, 4.0, "r2");
    
    Circle c1(0.0, 0.0, 1.0, "c1");
    Circle c2(0.0, 0.0, 2.0, "c2");

    vertex t1_1 = {0.0, 0.0}, t1_2 = { 1.0, 0.0 }, t1_3 = { 0.0, 1.0 };
    Triangle t1( t1_1, t1_2, t1_3, "t1");
    vertex t2_1 = {0.0, 0.0}, t2_2= { 2.0, 0.0 }, t2_3= { 0.0, 2.0 };
    Triangle t2( t2_1, t2_2, t2_3, "t2");

    std::list<Shape *> Shapes;
    Shapes.push_back (&r1);
    Shapes.push_back (&r2);
    Shapes.push_back (&c1);
    Shapes.push_back (&c2);
    Shapes.push_back (&t1);
    Shapes.push_back (&t2);

    Sort::sortByDecreasingPerimeter( &Shapes );

    /*ASSERT_EQ(&c2, Shapes.front());  // compare the address
    Shapes.pop_front();
    ASSERT_EQ(&r2, Shapes.front());
    Shapes.pop_front();
    ASSERT_EQ(&t2, Shapes.front());
    Shapes.pop_front();
    ASSERT_EQ(&c1, Shapes.front());
    Shapes.pop_front();
    ASSERT_EQ(&r1, Shapes.front());
    Shapes.pop_front();
    ASSERT_EQ(&t1, Shapes.front());
    Shapes.pop_front();
    */

    std::list<Shape *> ansShapes;
    ansShapes.push_back (&c2);
    ansShapes.push_back (&r2);
    ansShapes.push_back (&t2);
    ansShapes.push_back (&c1);
    ansShapes.push_back (&r1);
    ansShapes.push_back (&t1);

    ASSERT_EQ(ansShapes, Shapes);
}

TEST (Sort, sortByIncreasingArea) {
    Rectangle r1(0.0, 0.0, 1.0, 2.0, "r1");
    Rectangle r2(0.0, 0.0, 2.0, 4.0, "r2");
    
    Circle c1(0.0, 0.0, 1.0, "c1");
    Circle c2(0.0, 0.0, 2.0, "c2");

    vertex t1_1 = {0.0, 0.0}, t1_2 = { 1.0, 0.0 }, t1_3 = { 0.0, 1.0 };
    Triangle t1( t1_1, t1_2, t1_3, "t1");
    vertex t2_1 = {0.0, 0.0}, t2_2= { 2.0, 0.0 }, t2_3= { 0.0, 2.0 };
    Triangle t2( t2_1, t2_2, t2_3, "t2");

    std::list<Shape *> Shapes;
    Shapes.push_back (&r1);
    Shapes.push_back (&r2);
    Shapes.push_back (&c1);
    Shapes.push_back (&c2);
    Shapes.push_back (&t1);
    Shapes.push_back (&t2);

    Sort::sortByIncreasingArea( &Shapes );

    Shape *cmpShape;
    cmpShape = Shapes.front();
    ASSERT_EQ( t1.area(), cmpShape->area());  // compare the value
    Shapes.pop_front();
    cmpShape = Shapes.front();
    ASSERT_EQ( t2.area(), cmpShape->area());
    Shapes.pop_front();
    cmpShape = Shapes.front();
    ASSERT_EQ( r1.area(), cmpShape->area());
    Shapes.pop_front();
    cmpShape = Shapes.front();
    ASSERT_EQ( c1.area(), cmpShape->area());
    Shapes.pop_front();
    cmpShape = Shapes.front();
    ASSERT_EQ( r2.area(), cmpShape->area());
    Shapes.pop_front();
    cmpShape = Shapes.front();
    ASSERT_EQ( c2.area(), cmpShape->area());
    Shapes.pop_front();
}

TEST (Sort, sortByDecreasingArea) {
    Rectangle r1(0.0, 0.0, 1.0, 2.0, "r1");
    Rectangle r2(0.0, 0.0, 2.0, 4.0, "r2");
    
    Circle c1(0.0, 0.0, 1.0, "c1");
    Circle c2(0.0, 0.0, 2.0, "c2");

    vertex t1_1 = {0.0, 0.0}, t1_2 = { 1.0, 0.0 }, t1_3 = { 0.0, 1.0 };
    Triangle t1( t1_1, t1_2, t1_3, "t1");
    vertex t2_1 = {0.0, 0.0}, t2_2= { 2.0, 0.0 }, t2_3= { 0.0, 2.0 };
    Triangle t2( t2_1, t2_2, t2_3, "t2");

    std::list<Shape *> Shapes;
    Shapes.push_back (&r1);
    Shapes.push_back (&r2);
    Shapes.push_back (&c1);
    Shapes.push_back (&c2);
    Shapes.push_back (&t1);
    Shapes.push_back (&t2);

    Sort::sortByDecreasingArea( &Shapes );

    Shape *cmpShape;
    cmpShape = Shapes.front();
    ASSERT_EQ( c2.area(), cmpShape->area());  // compare the value
    Shapes.pop_front();
    cmpShape = Shapes.front();
    ASSERT_EQ( r2.area(), cmpShape->area());
    Shapes.pop_front();
    cmpShape = Shapes.front();
    ASSERT_EQ( c1.area(), cmpShape->area());
    Shapes.pop_front();
    cmpShape = Shapes.front();
    ASSERT_EQ( r1.area(), cmpShape->area());
    Shapes.pop_front();
    cmpShape = Shapes.front();
    ASSERT_EQ( t2.area(), cmpShape->area());
    Shapes.pop_front();
    cmpShape = Shapes.front();
    ASSERT_EQ( t1.area(), cmpShape->area());
    Shapes.pop_front();
}

TEST (Sort, sortByIncreasingCompactness) {
    Rectangle r1(0.0, 0.0, 1.0, 2.0, "r1");
    Circle c1(0.0, 0.0, 1.0, "c1");
    vertex t1_1 = {0.0, 0.0}, t1_2 = { 1.0, 0.0 }, t1_3 = { 0.0, 1.0 };
    Triangle t1( t1_1, t1_2, t1_3, "t1");

    std::list<Shape *> Shapes;
    Shapes.push_back (&r1);
    Shapes.push_back (&c1);
    Shapes.push_back (&t1);

    ASSERT_EQ(&r1, Shapes.front());  // compare the address
    Shapes.pop_front();
    ASSERT_EQ(&c1, Shapes.front());
    Shapes.pop_front();
    ASSERT_EQ(&t1, Shapes.front());
    Shapes.pop_front();
}

#endif
