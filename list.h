#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>
#include "term.h"

using std::string;
using std::vector;

class List : public Term{
public:
    List():_elements() {}
    //List(vector<Term *> const & elements):_elements(elements){}
    string symbol() const {
        string ret = "[";
        for(int i = 0; i < _elements.size() - 1 ; i++){
            ret += _elements[i]-> symbol() + ", ";
        }
        ret += _elements[_elements.size()-1]-> symbol() + "]";
        return  ret;
    }
    string value() const {
        string ret = "[";
        for(int i = 0; i < _elements.size() - 1 ; i++){
            ret += _elements[i]-> value() + ", ";
        }
        ret += _elements[_elements.size()-1]-> value() + "]";
        return  ret;
    }
    bool match(Term & term);
    Term * head() const { return _elements.front();}
    List * tail() const ;

private:
    vector<Term *> _elements;

};

#endif