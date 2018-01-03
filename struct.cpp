#include "struct.h"
#include "iterator.h"

Iterator * Struct::createIterator()
{
  return new StructIterator(this);
}

// Iterator<Term*> * Struct::createIterator(){
//     return new StructIterator<Term*> (this);
// }

// Iterator<Term*> * Struct::createDFSIterator()
// {
// 	return new  DFSIterator<Term*> (this);
// }

// Iterator<Term*> * Struct::createBFSIterator()
// {
// 	return new BFSIterator<Term*> (this);
// }