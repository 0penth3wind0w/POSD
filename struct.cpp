#include "struct.h"

string Struct::symbol() const{
    //cout<<"22\n";
    string ret =_name.symbol() + "(";
    cout<<"23\n";
    for(int i = 0; i < _args.size() - 1 ; i++){
      cout<<"24\n";
      ret += _args[i]-> symbol() + ", ";
    }
    ret += _args[_args.size()-1]-> symbol() + ")";
    return  ret;
  }

string Struct::value() const{
    cout<<"s1\n";
    string ret =_name.value() + "(";
    cout<<"s2\n";
    for(int i = 0; i < _args.size() - 1 ; i++){
        cout<<"s3\n";
      ret += _args[i]-> value() + ", ";
    }
    ret += _args[_args.size()-1]-> value() + ")";
    return  ret;
}
bool Struct::match(Variable & variable){}
bool Struct::match(Term &term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
      if (!_name.match(ps->_name))
        return false;
      if(_args.size()!= ps->_args.size())
        return false;
      for(int i=0;i<_args.size();i++){
        if(_args[i]->symbol() != ps->_args[i]->symbol())
            return false;
      }
      return true;
    }
    return false;
  }