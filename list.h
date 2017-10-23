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
        if(term.isVar()){
            //penfing
        }
        else{
            List * ps = dynamic_cast<List *>(&term);
            if (ps){
                if(_elements.size()!= ps->_elements.size())
                    return false;
                for(int i=0;i<_elements.size();i++){
                    _elements[i]->match(*ps->_elements[i]);
                }
                return true;
            }
            return false;
        }
    }
    Term * head() const { 
        if( _elements.empty() ){
            
        }
        return _elements.front();
    }
    List * tail() const {
        vector<Term *> outvec = _elements;
        outvec.erase(outvec.begin());
        List *l = new List(outvec);
        return l;
    }

private:
    vector<Term *> _elements;

};

#endif