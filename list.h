#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include <vector>
#include "term.h"
#include "variable.h"

using std::cout;
using std::string;
using std::vector;

class List : public Term{
public:
    List():_elements() {}
    List(vector<Term *> const & elements):_elements(elements){}

    string symbol() const {
        if( _elements.empty() ){
            string ret = "[]";
            return ret;
        }
        else{
            string ret = "[";
            for(int i = 0; i < _elements.size() - 1 ; i++){
                ret += _elements[i]-> symbol() + ", ";
            }
            ret += _elements[_elements.size()-1]-> symbol() + "]";
            return  ret;    
        }
    }

    string value() const {
        if(_elements.empty()){
            string ret = "[]";
            return ret;
        }
        else{
            string ret = "[";
            for(int i = 0; i < _elements.size() - 1 ; i++){
                ret += _elements[i]-> value() + ", ";
            }
            ret += _elements[_elements.size()-1]-> value() + "]";
            return  ret;
        }
    }
    
    bool match(Term & term){
        List * ps = dynamic_cast<List *>(&term);
        if (ps){
            if(_elements.size()!= ps->_elements.size())
                return false;
                for(int i=0;i<_elements.size();i++){
                    if(_elements[i]->isVar()){
                        _elements[i]->match(ps->_elements[i]);
                    }
                    else{
                        if(_elements[i]->value() != ps->_elements[i]->value()){
                            cout<<_elements[i]->symbol()<<"\t"<<ps->_elements[i]->value()<<"\n";
                            return false;
                        }
                    }
                }
                return true;
            }
        return false;
    }
    Term * head() const { return _elements.front();}
    List * tail() const ;

private:
    vector<Term *> _elements;

};

#endif