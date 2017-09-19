#include "include/Sort.h"

//#define MIN_VALUE 0
//#define MAX_VALUE 99999

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
    /*
    //list cannot be random accessed
    for( int i = shapeList->size()-1; i > 0; --i ){
        int largestPeri = MIN_VALUE;
        int index = 0;
        Shape *temp;
        for(int j = i; j > 0; --j){
            if( &shapeList[j]->perimeter() > largestPeri ){
                largestPeri = *shapeList[j] -> perimeter();
                index = j;
            }
        }
        temp = &shapeList[index];
        shapeList[index] = shapeList[i];
        shapeList[i] = temp;
    }*/
    shapeList->sort( [](Shape *a, Shape *b){ return ( a->perimeter() < b->perimeter() );} );
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
    shapeList->sort( [](Shape *a, Shape *b){ return ( a->perimeter() > b->perimeter() );} );
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList){
    shapeList->sort( [](Shape *a, Shape *b){ return ( a->area() < b->area() );} );
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList){
    shapeList->sort( [](Shape *a, Shape *b){ return ( a->area() > b->area() );} );
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList){
    shapeList->sort( [](Shape *a, Shape *b){ return ( a->area()/a->perimeter() > b->area()/b->perimeter() );} );
}