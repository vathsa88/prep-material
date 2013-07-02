// BST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>

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
    ,count (0)
  {
  }
  Key _key;
  TreeNode* _pLeft;
  TreeNode* _pRight;
  int count;
};
template <class Key>
class BSTSymbolTable {
public:  
  class BSTRecord {
  public:
    bool isValid(){
      return _key ? true : false;
    }
  public:
    BSTRecord( ):_key (NULL), _pNext(NULL)
    {
    }
    Key* _key;
    BSTRecord* _pNext;
  };
public:
  BSTSymbolTable():
      _pRoot(NULL)
  {
  }
private:
  int size (TreeNode<Key>* node){
    if (node == NULL){
      return 0;
    }
    return node->count;
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

    node->count = 1 + size(node->_pLeft) + size(node->_pRight);
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
private:
  int rank (TreeNode<Key>* node, Key& key)
  {
    if (node == NULL)
      return -1;

    int nRet = node->_key.compare(key);
    if (0 == nRet){
      return node->count;
    }else if (nRet < 0){
      //node key is greater than inKey
      return rank (node->_pLeft,key);
    }else{
      //node key is less than inKey
      return 1 + size(node->_pLeft) + rank (node->_pRight,key);
    }

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
  BSTRecord get (Key& key)
  {
       TreeNode<Key>* resNode = get(_pRoot,key);
       BSTRecord record;
       if (resNode != NULL){
         record._key = &resNode->_key;
       }
       return record;
  }

  int rank (Key& key)
  {

    return 
  }
private:
  TreeNode<Key>* inorder_successor(TreeNode<Key>* node, Key& key) {
    if (node == NULL)
      return NULL;
    int nRet = node->_key.compare(key);
    TreeNode<Key>* retNode = NULL;
    if (0 == nRet){ /*TreeNode Match Found*/ 
      //Now find inorder successor
      retNode = node->_pRight;
      while ( (retNode != NULL) && (retNode->_pLeft != NULL)){
        retNode = retNode->_pLeft;
      }

    }else if (nRet < 0){ //node.val > key => key must be in left sub tree
      retNode = inorder_successor(node->_pLeft,  key);
      if (retNode == NULL)
        retNode = node;
    }else { //node.val < key => key must be in right sub tree
      retNode = inorder_successor(node->_pRight,  key);
      // if inorder successor of right sub tree is null
      // then no such element exists
    }

    return retNode;
  }

  TreeNode<Key>* inorder_successor(Key& key) {
    TreeNode<Key>* nextNode = inorder_successor(_pRoot, key);
    return nextNode;
  }

  //TreeNode<Key>* remove (TreeNode<Key>* node, Key& key)
  //{
  //  if (node == NULL)
  //    return NULL;
  //  int nRet = node->_key.compare(key);
  //  
  //  TreeNode<Key>* nodeToDelete = NULL;
  //  
  //  if (nRet == 0){
  //    nodeToDelete = node;
  //    return nodeToDelete;
  //  }else if (nRet < 0){
  //    nodeToDelete = remove (node->_pLeft, key);
  //  }else {
  //    nodeToDelete = remove (node->_pRight, key);
  //  }

  //  if (nodeToDelete){
  //    int nChildCase = 0;
  //    if (nodeToDelete->_pLeft){
  //      nChildCase = nChildCase | 1;
  //    }

  //    if (nodeToDelete->_pRight){
  //      nChildCase = nChildCase | 2;
  //    }

  //    switch (nChildCase) {
  //      case 0:
  //        {
  //          if (node->_pLeft == nodeToDelete)
  //            node->_pLeft = NULL;
  //          else
  //            node->_pRight = NULL;

  //          delete nodeToDelete;
  //          nodeToDelete = NULL;
  //        }break;
  //      case 1: // only left child
  //        {
  //          if (node->_pLeft == nodeToDelete)
  //            node->_pLeft = nodeToDelete->_pLeft;
  //          else
  //            node->_pRight = nodeToDelete->_pLeft;

  //          if (nodeToDelete == _pRoot){
  //            _pRoot = nodeToDelete->_pLeft;
  //          }

  //          delete nodeToDelete;
  //          nodeToDelete = NULL;

  //        }break;
  //      case 2:// only rt child
  //        {
  //          if (node->_pLeft == nodeToDelete)
  //            node->_pLeft = nodeToDelete->_pRight;
  //          else
  //            node->_pRight = nodeToDelete->_pRight;

  //          if (nodeToDelete == _pRoot){
  //            _pRoot = nodeToDelete->_pRight;
  //          }

  //          delete nodeToDelete;
  //          nodeToDelete = NULL;

  //        }break;
  //      case 3:// both left and right child
  //        {
  //          TreeNode<Key>* _pNextNode = inorder_successor(node,nodeToDelete->_key);
  //          nodeToDelete->_key = _pNextNode->_key;
  //          remove(nodeToDelete->_pRight,nodeToDelete->_key);
  //          
  //          //copy contents of _pNextNode into nodeToDelete
  //          //delete _pNextNode
  //        }break;
  //    }
  //  }

  //  return nodeToDelete;
  //}

public:
  BSTRecord next ( Key& key)
  {
    TreeNode<Key>* nextNode = inorder_successor(key);
    BSTRecord retRecord;
    if (nextNode != NULL){
      retRecord._key = &nextNode->_key;
    }
    return retRecord;
  }

  void remove (Key& key)
  {
    //remove(_pRoot,key);
  }

private:
  TreeNode<Key>* floor (TreeNode<Key>* node, Key& key)
  {    
    if (node == NULL)
      return NULL;

    TreeNode<Key>* retNode = NULL;
    int nRet = node->_key.compare(key);
    if (nRet < 0) {
      retNode = floor(node->_pRight,key);
      if (retNode == NULL){
        retNode = node;
      }
    }else if (nRet > 0){
      retNode = floor(node->_pLeft,key);
    }else {
      retNode = node;
    }
    return retNode;
  }

  TreeNode<Key>* ceil (TreeNode<Key>* node, Key& key)
  {    
    if (node == NULL)
      return NULL;

    TreeNode<Key>* retNode = NULL;
    int nRet = node->_key.compare(key);
    if (nRet < 0) {
      retNode = ceil(node->_pRight,key);      
    }else if (nRet > 0){
      retNode = ceil(node->_pLeft,key);
      if (retNode == NULL){
        retNode = node;
      }
    }else {
      retNode = node;
    }

    return retNode;
  }
public:
  BSTRecord floor (Key& key)
  {
    TreeNode<Key>* _pFloorTreeNode = floor(_pRoot,key);    
    BSTRecord record;
    if (_pFloorTreeNode != NULL){
      record._key = &_pFloorTreeNode->_key;
    }   
    return record;
  }
  BSTRecord ceil (Key& key)
  {
    TreeNode<Key>* _pCeilTreeNode = floor(_pRoot,key);    
    BSTRecord record;
    if (_pCeilTreeNode != NULL){
      record._key = &_pCeilTreeNode->_key;
    }  
    return record;
  }
private:
  void range (TreeNode<Key>* node, Key& startVal, Key& endVal, std::list<BSTRecord>& refList)
  {
    if (node == NULL)
      return;
    
    int nRet1 = node->_key.compare(startVal);
    int nRet2 = node->_key.compare(endVal);

    if ( (nRet1 == 0) || (nRet2 == 0)){
      BSTRecord record; record._key = &node->_key;
      refList.push_back(record);
    }else{
      if ((nRet1 < 0) && (nRet2 > 0)){
        
        BSTRecord record; record._key = &node->_key;
        refList.push_back(record);

        range(node->_pLeft,startVal,endVal,refList);
        range(node->_pRight,startVal,endVal,refList);
      }

      //if node.val < startVal then all elements in left subtree are invalid
      // as left subtree < node.val < startVal
      if (nRet1 > 0){
        range(node->_pRight,startVal,endVal,refList);
      }

      if (nRet2 < 0){
        range(node->_pLeft,startVal,endVal,refList);
      } 
    }
  }
public:
  std::list<BSTRecord> range (Key& startVal, Key& endVal)
  {
    std::list<BSTRecord> resultList;
    range(_pRoot,startVal,endVal,resultList);
    return resultList;
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

  
  //while (1) {
  //  std::cin >> key1.val;
  //  BSTSymbolTable<IntKey>::BSTRecord record = bst.get(key1);
  //  if (record.isValid()){
  //    std::cout << key1.val << " Exists \n";
  //  }else{
  //    std::cout <<  key1.val << " Does not exist\n";
  //  }

  //  if (key1.val == -2)
  //    break;
  //}

  key1.val = 2;
  bst.remove(key1);
  IntKey keyStart; keyStart.val = -1;
  IntKey keyEnd; keyEnd.val = 4;

  std::list<BSTSymbolTable<IntKey>::BSTRecord> rangeItems = bst.range(keyStart, keyEnd);
  std::list<BSTSymbolTable<IntKey>::BSTRecord>::iterator iterList = rangeItems.begin();
  while (iterList != rangeItems.end()){
    std::cout << "Record: " << iterList->_key->val << std::endl;
    iterList++;
  }


  key1.val = -1;
  BSTSymbolTable<IntKey>::BSTRecord record;
  record._key = &key1;
  do {
    key1.val = record._key->val;
    std::cout << key1.val << "--->";
    record = bst.next(key1);
  }while (record.isValid());
  std::cout << "END" << std::endl;
	return 0;
}

