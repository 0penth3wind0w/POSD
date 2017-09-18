#include "include/Sort.h"

#define MIN_VALUE 0
#define MAX_VALUE 99999

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
    /*for( int i = shapeList->size()-1; i > 0; --i ){
        int largestPeri = MIN_VALUE;
        int index = 0;
        Shape *temp;
        for(int j = i; j > 0; --j){
            if( *shapeList[j]-> perimeter() > largestPeri ){
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
    /*for( int i = 0; i < shapeList.size()-1; ++i ){
        int smallestPeri = MAX_VALUE;
        int index = 0;
        Shape *temp;
        for(int j = i; j < shapeList.size()-1; ++j){
            if( shapeList[j]->perimeter() < smallestPeri ){
                smallestPeri = shapeList[j]->perimeter();
                index = j;
            }
        }
        temp = shapeList[index];
        shapeList[index] = shapeList[i];
        shapeList[i] = temp;
    }*/
    shapeList->sort( [](Shape *a, Shape *b){ return ( a->perimeter() > b->perimeter() );} );
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList){
    /*for( int i = shapeList.size()-1; i > 0; --i ){
        int largestArea = 0;
        int index = 0;
        Shape *temp;
        for(int j = i; j > 0; --j){
            if( shapeList[j]->area() > largestArea ){
                largestPeri = shapeList[j]->area();
                index = j;
            }
        }
        temp = shapeList[index];
        shapeList[index] = shapeList[i];
        shapeList[i] = temp;
    }*/
    shapeList->sort( [](Shape *a, Shape *b){ return ( a->area() < b->area() );} );
}
/*
void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList){
    for( int i = 0; i < shapeList.size()-1; ++i ){
        int smallestArea = MAX_VALUE;
        int index = 0;
        Shape *temp;
        for(int j = i; j < shapeList.size()-1; ++j){
            if( shapeList[j]->Area() < smallestArea ){
                smallestArea = shapeList[j]->area();
                index = j;
            }
        }
        temp = shapeList[index];
        shapeList[index] = shapeList[i];
        shapeList[i] = temp;
    }
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList){
    std::sort (shapeList.begin(), shapeList.end(), myfunction);
}*/