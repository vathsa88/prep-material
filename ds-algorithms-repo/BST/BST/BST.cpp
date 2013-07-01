// BST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <exception>

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
      return 1;
    else
      return -1;
  }
public:
  int val;
};

template <class Key>
struct TreeNode {
  TreeNode( Key& inKey)
    :_key(inKey)
    ,_pLeft(NULL)
    ,_pRight(NULL)
  {
  }
  Key _key;
  TreeNode* _pLeft;
  TreeNode* _pRight;
};
template <class Key>
class BSTSymbolTable {
public:
  BSTSymbolTable():
      _pRoot(NULL)
  {
  }
private:
  TreeNode<Key>* put (TreeNode<Key>* node, Key& key)
  {
    if (node == NULL){
      node = new TreeNode<Key>(key);      
    }else{
      int nRet = node->_key.compare(key);
      if (nRet < 0){
        node->_pLeft = put(node->_pLeft, key);
      }
      else if (nRet > 0){
        node->_pRight = put (node->_pRight, key);
      }
    }
    return node;
  }

  TreeNode<Key>* get (TreeNode<Key>* node, Key& key)
  {
    if (node == NULL){
      return NULL;
    }
    int nRet = node->_key.compare(key);
    if (nRet < 0)
      return get(node->_pLeft, key);
    else if (nRet > 0)
      return get (node->_pRight, key);
    else
      return node;
  }

public:
  void put ( Key& key)
  {
      _pRoot = put (_pRoot,key);
  }

  bool exists (Key& key)
  {
    TreeNode<Key>* res = get(_pRoot,key);
    if (res != NULL){
      return true;
    }
    return false;
  }
 /* bool get ( Key& key)
  {
    if (exists(key)){
      TreeNode* res = get(_pRoot,key);
    }
  }*/

public:
  void remove (Key& key)
  {

  }

private:
  TreeNode* floor (TreeNode* node, Key& key)
  {
    if (node == NULL)
    int nRet = node->_key.compare(key);
    if ()
  }
public:
  //
  Key& floor (Key& key)
  {
    TreeNode* _pFloorTreeNode = floor(_pRoot,key);    
    
  }
  Key& ceil (Key& key)
  {

  }
public:
  void range (Key& startVal, Key& endVal)
  {

  }
private:
  TreeNode<Key>* _pRoot;
};

#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
  BSTSymbolTable<IntKey> bst;
  IntKey key1; key1.val = 2;
  bst.put(key1);
  key1.val = 4;
  bst.put(key1);
  key1.val = 0;
  bst.put(key1);
  key1.val = -1;
  bst.put(key1);

  

  while (1) {
    std::cin >> key1.val;
    if (bst.exists(key1))
      std::cout << key1.val << " Exists \n";
    else
      std::cout <<  key1.val << " Does not exist\n";

    if (key1.val == -2)
      break;
  }

	return 0;
}

