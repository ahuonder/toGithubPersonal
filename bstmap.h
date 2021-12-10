//---------------------------------------------------------------------------
// NAME: Adam Huonder
// DATE: Fall 2021
// DESC: Implements a binary search tree
//---------------------------------------------------------------------------

#ifndef BSTMAP_H
#define BSTMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class BSTMap : public Map<K,V>
{
public:

  // default constructor
  BSTMap();

  // copy constructor
  BSTMap(const BSTMap& rhs);

  // move constructor
  BSTMap(BSTMap&& rhs);

  // copy assignment
  BSTMap& operator=(const BSTMap& rhs);

  // move assignment
  BSTMap& operator=(BSTMap&& rhs);  

  // destructor
  ~BSTMap();
  
  // Returns the number of key-value pairs in the map
  int size() const;

  // Tests if the map is empty
  bool empty() const;

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
  V& operator[](const K& key);

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
  const V& operator[](const K& key) const;

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
  void insert(const K& key, const V& value);

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
  void erase(const K& key);

  // Returns true if the key is in the collection, and false otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order
  ArraySeq<K> sorted_keys() const;  

  // Returns the height of the binary search tree
  int height() const;
  
private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
  };

  // number of key-value pairs in map
  int count = 0;

  // array of linked lists
  Node* root = nullptr;

  // clean up the tree and reset count to zero given subtree root
  void make_empty(Node* st_root);

  // copy assignment helper
  Node* copy(const Node* rhs_st_root) const;
  
  // erase helper
  Node* erase(const K& key, Node* st_root);

  // find_keys helper
  void find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const;

  // sorted_keys helper
  void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

  // height helper
  int height(const Node* st_root) const;

};


// TODO: Implement the above functions per the directions in HW-7

// default constructor
template<typename K, typename V>
BSTMap<K,V>::BSTMap()
{
  //I dont think I need anything here
}

// copy constructor
template<typename K, typename V>
BSTMap<K,V>::BSTMap(const BSTMap& rhs)
{
  root = copy(rhs.root);
  count = rhs.count;
}

// move constructor
template<typename K, typename V>
BSTMap<K,V>::BSTMap(BSTMap&& rhs)
{
  count = rhs.count;
  root = rhs.root;
  rhs.root = nullptr;
  rhs.count = 0;
}

// copy assignment
template<typename K, typename V>
BSTMap<K,V>& BSTMap<K,V>::operator=(const BSTMap& rhs)
{
  if (this != &rhs)
  {
    make_empty(root);
    root = copy(rhs.root);
    count = rhs.count;
  }
  return *this;
}

// move assignment
template<typename K, typename V>
BSTMap<K,V>& BSTMap<K,V>::operator=(BSTMap&& rhs)
{
  if (this != &rhs)
  {
    make_empty(root);
    root = rhs.root;
    count = rhs.count;
    rhs.root = nullptr;
    rhs.count = 0;
  }
  return *this;
}

// destructor
template<typename K, typename V>
BSTMap<K,V>::~BSTMap()
{
  make_empty(root);
  count = 0;
}
  
// Returns the number of key-value pairs in the map
template<typename K, typename V>
int BSTMap<K,V>::size() const
{
  return count;
}

// Tests if the map is empty
template<typename K, typename V>
bool BSTMap<K,V>::empty() const
{
  if (count == 0)
    return true;
  return false;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& BSTMap<K,V>::operator[](const K& key)
{
  Node* ptr = root;

  while (ptr != nullptr)
  {
    if (ptr->key == key)
      return ptr->value;
    else if (ptr->key < key)
      ptr = ptr->right;
    else if (ptr->key > key)
      ptr= ptr->left;
  }
  throw std::out_of_range("V& BSTMap<K,V>::operator[](const K& key). Key does not exist.");
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection. 
template<typename K, typename V>
const V& BSTMap<K,V>::operator[](const K& key) const
{
  Node* ptr = root;

  while (ptr != nullptr)
  {
    if (ptr->key == key)
      return ptr->value;
    else if (ptr->key < key)
      ptr = ptr->right;
    else if (ptr->key > key)
      ptr= ptr->left;
  }

  throw std::out_of_range("const V& BSTMap<K,V>::operator[](const K& key) const. Key does not exist.");
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template<typename K, typename V>
void BSTMap<K,V>::insert(const K& key, const V& value)
{
  Node* ptr = root;
  Node* pre = root;

  Node* in = new Node;
  in->key = key;
  in->value = value;
  in->left = nullptr;
  in->right = nullptr;
  
  if (root == nullptr)
  {
    root = in;
    count++;
    return;
  }

  while (ptr != nullptr)
  {
    pre = ptr;
    if (key > ptr->key)
      ptr = ptr->right;
    else if (key <= ptr->key)
      ptr = ptr->left;
  }
  
  if (pre->key >= key)
    pre->left = in;
  else if (pre->key < key)
    pre->right = in;

  count++;
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void BSTMap<K,V>::erase(const K& key)
{
  root = erase(key, root);
  return;
}

// Returns true if the key is in the collection, and false otherwise.
template<typename K, typename V>
bool BSTMap<K,V>::contains(const K& key) const
{
  Node* ptr = root;
  
  while(ptr != nullptr)
  {
    if (ptr->key == key)
      return true;
    else if (ptr->key < key)
      ptr = ptr->right;
    else if (ptr->key > key)
      ptr= ptr->left;
  }
  return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> BSTMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  ArraySeq<K> tmp;
  find_keys(k1, k2, root, tmp);
  return tmp;
}

// Returns the keys in the collection in ascending sorted order
template<typename K, typename V>
ArraySeq<K> BSTMap<K,V>::sorted_keys() const
{
  ArraySeq<K> tmp;
  sorted_keys(root, tmp);
  return tmp;
}

// Returns the height of the binary search tree
template<typename K, typename V>
int BSTMap<K,V>::height() const
{
  return height(root);
}
  
// clean up the tree and reset count to zero given subtree root
template<typename K, typename V>
void BSTMap<K,V>::make_empty(Node* st_root)
{
  if (st_root != nullptr)
  {
    make_empty(st_root->left);
    make_empty(st_root->right);

    st_root->left = nullptr;
    st_root->right = nullptr;
    delete st_root;
  }
  return;
}

// copy assignment helper
template<typename K, typename V>
typename BSTMap<K,V>::Node* BSTMap<K,V>::copy(const Node* rhs_st_root) const
{
  Node* cpy = nullptr;
  if (rhs_st_root != nullptr)
  {
    cpy = new Node;
    cpy->key = rhs_st_root->key;
    cpy->value = rhs_st_root->value;

    cpy->left = copy(rhs_st_root->left);
    cpy->right = copy(rhs_st_root->right);
  }
  return cpy;
}
  
// erase helper
template<typename K, typename V>
typename BSTMap<K,V>::Node* BSTMap<K,V>::erase(const K& key, Node* st_root)
{
  if (st_root == nullptr)
    throw std::out_of_range("void erase(const K& key). Key does not exist.");
  else if (key < st_root->key)
    st_root->left = erase(key , st_root->left);
  else if (key > st_root->key)
    st_root->right = erase(key , st_root->right);
  else if (key == st_root->key) {
    // case 1: left subtree is empty
    if (st_root->left == nullptr)
    {
      Node* tmp = st_root;
      st_root = st_root->right;
      count--;
      delete tmp;
      return st_root;
    }
    // case 2: right subtree is empty
    else if (st_root->right == nullptr)
    {
      Node* tmp = st_root;
      st_root = st_root->left;
      count--;
      delete tmp;
      return st_root;
    }
    // case 3: inorder successor
    // use iteration to find , replace , delete inorder successor
    else 
    {
      Node* succ = st_root->right;
      Node* pre = st_root;
      while (succ->left != nullptr)
      {
        pre = succ;
        succ = succ->left;
      }
      st_root->key = succ->key;
      if(pre != st_root)
        pre->left = succ->right;
      else if (pre == st_root)
      {
        pre->right = succ->right;
      }
      delete succ;
      count--;
      return st_root;
    }
  }
  
  return st_root;
}

// find_keys helper
template<typename K, typename V>
void BSTMap<K,V>::find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const
{
  //base
  if (st_root == nullptr)
    return;

  find_keys(k1, k2, st_root->left, keys);

  if (st_root->key >= k1 and st_root->key <= k2)
    keys.insert(st_root->key, keys.size());
  
  find_keys(k1, k2, st_root->right, keys);
  return;
}

// sorted_keys helper
template<typename K, typename V>
void BSTMap<K,V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const
{
  if (st_root == nullptr)
    return;

  sorted_keys(st_root->left, keys);
  keys.insert(st_root->key, keys.size());
  sorted_keys(st_root->right, keys);
  return;
}

// height helper
template<typename K, typename V>
int BSTMap<K,V>::height(const Node* st_root) const
{
  if (st_root == nullptr)
    return 0;

  int left = height(st_root->left);
  int right = height(st_root->right);
  
  if (left > right)
    return 1 + left;
  else
    return 1 + right;
}



#endif
