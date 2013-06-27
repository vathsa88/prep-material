// BST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template <class T>
class Comparable {
public:
  int compare (T& other){
    return (static_cast<T*> (this))->compare(other);
  }
};

class IntKey: public Comparable<IntKey>
{
public:
  int compare(IntKey& other) const{
    if (val == other.val)
      return 0;
    else if (val < other.val)
      return -1;
    else
      return 1;
  }
private:
  int val;
};

template <class Key>
class BSTSymbolTable {
public:
  void put ( Key& key);
  const Key& get ( );
public:
  void remove (Key& key);
public:
  Key& floor (Key& key);
  Key& ceil (Key& key);
public:
  void range (Key& startVal, Key& endVal);
};
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

