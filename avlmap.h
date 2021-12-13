//---------------------------------------------------------------------------
// NAME: Adam Huonder
// DATE: Fall 2021
// DESC: Implements an AVL tree
//---------------------------------------------------------------------------

#ifndef AVLMAP_H
#define AVLMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class AVLMap : public Map<K,V>
{
public:

  // default constructor
  AVLMap();

  // copy constructor
  AVLMap(const AVLMap& rhs);

  // move constructor
  AVLMap(AVLMap&& rhs);

  // copy assignment
  AVLMap& operator=(const AVLMap& rhs);

  // move assignment
  AVLMap& operator=(AVLMap&& rhs);  

  // destructor
  ~AVLMap();
  
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

  // helper to print the tree for debugging
  void print() const;
  
private:

  // node for avl tree
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
    int height;
  };

  // number of nodes
  int count = 0;

  // root node
  Node* root = nullptr;

  // clean up the tree and reset count to zero given subtree root
  void make_empty(Node* st_root);

  // copy assignment helper
  Node* copy(const Node* rhs_st_root) const;
  
  // erase helper
  Node* erase(const K& key, Node* st_root);

  // insert helper
  Node* insert(const K& key, const V& value, Node* st_root);
  
  // find_keys helper
  void find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const;

  // sorted_keys helper
  void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

  // rotations
  Node* right_rotate(Node* k2);
  Node* left_rotate(Node* k2);
  
  // rebalance
  Node* rebalance(Node* st_root);

  // print helper
  void print(std::string indent, const Node* st_root) const;
  
};


template<typename K, typename V>
void AVLMap<K,V>::print() const
{
  print(std::string(""), root);
}


template<typename K, typename V>
void AVLMap<K,V>::print(std::string indent, const Node* st_root) const
{
  if (!st_root)
    return;
  std::cout << st_root->key << " (" << st_root->height << ")" <<  std::endl;
  if (st_root->left) {
    std::cout << indent << " lft: ";
    print(indent + " ", st_root->left);
  }
  if (st_root->right) {
    std::cout << indent << " rgt: ";
    print(indent + " ", st_root->right);
  }
}


//----------------------------------------------------------------------
// TODO: Implement the above functions below
//----------------------------------------------------------------------

// default constructor
template<typename K, typename V>
AVLMap<K,V>::AVLMap()
{
  //dont think I need anything here
}

// copy constructor
template<typename K, typename V>
AVLMap<K,V>::AVLMap(const AVLMap& rhs)
{
  root = copy(rhs.root);
  count = rhs.count;
}

// move constructor
template<typename K, typename V>
AVLMap<K,V>::AVLMap(AVLMap&& rhs)
{
  count = rhs.count;
  root = rhs.root;
  rhs.root = nullptr;
  rhs.count = 0;
}

// copy assignment
template<typename K, typename V>
AVLMap<K,V>& AVLMap<K,V>::operator=(const AVLMap& rhs)
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
AVLMap<K,V>& AVLMap<K,V>::operator=(AVLMap&& rhs)
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
AVLMap<K,V>::~AVLMap()
{
  make_empty(root);
  count = 0;
}
  
// Returns the number of key-value pairs in the map
template<typename K, typename V>
int AVLMap<K,V>::size() const
{
  return count;
}

// Tests if the map is empty
template<typename K, typename V>
bool AVLMap<K,V>::empty() const
{
  if (count == 0)
    return true;
  return false;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& AVLMap<K,V>::operator[](const K& key)
{
  Node* ptr = root;

  while (ptr != nullptr)
  {
    if (ptr->key == key)
      return ptr->value;
    else if (ptr->key < key)
      ptr = ptr->right;
    else if (ptr->key > key)
      ptr = ptr->left;
  }
  throw std::out_of_range("V& AVLMap<K,V>::operator[](const K& key). Key does not exist.");
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection. 
template<typename K, typename V>
const V& AVLMap<K,V>::operator[](const K& key) const
{
  Node* ptr = root;

  while (ptr != nullptr)
  {
    if (ptr->key == key)
      return ptr->value;
    else if (ptr->key < key)
      ptr = ptr->right;
    else if (ptr->key > key)
      ptr = ptr->left;
  }
  throw std::out_of_range("const V& AVLMap<K,V>::operator[](const K& key) const. Key does not exist.");
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template<typename K, typename V>
void AVLMap<K,V>::insert(const K& key, const V& value)
{
  root = insert(key, value, root);
  return;
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void AVLMap<K,V>::erase(const K& key)
{
  root = erase(key, root);
  return;
}

// Returns true if the key is in the collection, and false otherwise.
template<typename K, typename V>
bool AVLMap<K,V>::contains(const K& key) const
{
  Node* ptr = root;

  while (ptr != nullptr)
  {
    if (ptr->key == key)
      return true;
    else if (ptr->key < key)
      ptr = ptr->right;
    else if (ptr->key > key)
      ptr = ptr->left;
  }
  return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> AVLMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  //different than last time
  ArraySeq<K> tmp;
  find_keys(k1, k2, root, tmp);
  return tmp;
}

// Returns the keys in the collection in ascending sorted order
template<typename K, typename V>
ArraySeq<K> AVLMap<K,V>::sorted_keys() const
{
  ArraySeq<K> tmp;
  sorted_keys(root, tmp);
  return tmp;
}

// Returns the height of the binary search tree
template<typename K, typename V>
int AVLMap<K,V>::height() const
{
  if (root != nullptr)
    return root->height;
  return 0;
}

// clean up the tree and reset count to zero given subtree root
template<typename K, typename V>
void AVLMap<K,V>::make_empty(Node* st_root)
{
  if (st_root != nullptr)
  {
    make_empty(st_root->left);
    make_empty(st_root->right);

    st_root->left = nullptr;
    st_root->right = nullptr;
    delete st_root;
    st_root = nullptr;
  }
  return;
}

// copy assignment helper
template<typename K, typename V>
typename AVLMap<K,V>::Node* AVLMap<K,V>::copy(const Node* rhs_st_root) const
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
typename AVLMap<K,V>::Node* AVLMap<K,V>::erase(const K& key, Node* st_root)
{
  //std::cout << "******************** subtree root: " << st_root->key << ", " << key << "\n";
  //print();
  if (st_root == nullptr)
    throw std::out_of_range("typename AVLMap<K,V>::Node* erase(const K& key, Node* st_root). Key does not exist.");
  else if (key < st_root->key)
    st_root->left = erase(key , st_root->left);
  else if (key > st_root->key)
    st_root->right = erase(key , st_root->right);
  else if (key == st_root->key) {
    // case 1: left subtree is empty
    if (st_root->left == nullptr)
    {
      //std::cout << "case 1 deleting: " << st_root->key << "\n";
      Node* tmp = st_root;
      st_root = st_root->right;
      count--;
      delete tmp;
      tmp = nullptr;
    }
    // case 2: right subtree is empty
    else if (st_root->right == nullptr)
    {
      //std::cout << "case 2 deleting: " << st_root->key << "\n";
      Node* tmp = st_root;
      st_root = st_root->left;
      count--;
      delete tmp;
      tmp = nullptr;
    }
    // case 3: inorder successor
    // use iteration to find , replace , delete inorder successor
    else 
    {
      //std::cout << "case 3" << "\n";
      //finds successor
      Node* succ = st_root->right;
      Node* pre = st_root;
      while (succ->left != nullptr)
      {
        pre = succ;
        succ = succ->left;
      }

      //copies the key of the successor into root
      st_root->key = succ->key;
      st_root->value = succ->value;

      //deletes
      st_root->right = erase(succ->key, st_root->right);
      if(pre != st_root)
        pre->left = succ->right;
      else if (pre == st_root)
      {
        pre->right = succ->right;
      }
    }
  }
  
  int rH = 0;
  int lH = 0;
  if (st_root)
  {
  if (st_root->left)
    lH = st_root->left->height;
  if (st_root->right)
    rH = st_root->right->height;
  
  if (lH > rH)
    st_root->height = lH + 1;
  else
    st_root->height = rH + 1;
  }
  return rebalance(st_root);
}

// insert helper
template<typename K, typename V>
typename AVLMap<K,V>::Node* AVLMap<K,V>::insert(const K& key, const V& value, Node* st_root)
{
  if (st_root == nullptr)
  {
    Node* ptr = new Node;
    ptr->key = key;
    ptr->value = value;
    ptr->left = nullptr;
    ptr->right = nullptr;
    ptr->height = 1;
    count++;
    return ptr;
  }
  else 
  {
    if (key > st_root->key)
    {
      st_root->right = insert(key, value, st_root->right);
    }
    else
    {
      st_root->left = insert(key, value, st_root->left);
    }
    int rH = 0;
    int lH = 0;
    if (st_root->left)
      lH = st_root->left->height;
    if (st_root->right)
      rH = st_root->right->height;
  
    if (lH > rH)
      st_root->height = lH + 1;
    else
      st_root->height = rH + 1;
  } 

  return rebalance(st_root);
}
  
// find_keys helper
template<typename K, typename V>
void AVLMap<K,V>::find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const
{
  //do this different
  if (!st_root)
    return;
  if (k1 < st_root->key)
    find_keys(k1, k2, st_root->left, keys);

  if (k1 <= st_root->key and k2 >= st_root->key)
    keys.insert(st_root->key, keys.size());

  find_keys(k1, k2, st_root->right, keys);
  /*  
  else if (st_root->key <= k1)
    find_keys(k1, k2, st_root->right, keys);
  else if (st_root->key > k1)
    find_keys(k1, k2, st_root->left, keys);
  //else if (st_root->key == k1)
    //keys.insert(k1, keys.size());
  
  find_keys(k1, k2, st_root->right, keys);
  std::cout << "key: " << st_root->key << " k1: " << k1 << " k2: " << k2 <<std::endl;
  keys.insert(st_root->key, keys.size());
*/
}

// sorted_keys helper
template<typename K, typename V>
void AVLMap<K,V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const
{
  if (st_root == nullptr)
    return;

  sorted_keys(st_root->left, keys);
  keys.insert(st_root->key, keys.size());
  sorted_keys(st_root->right, keys);
  return;
}

// rotate right
template<typename K, typename V>
typename AVLMap<K,V>::Node* AVLMap<K,V>::right_rotate(Node* k2)
{
  Node* k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  
  int rH = 0;
  int lH = 0;
  if (k2->left)
    lH = k2->left->height;
  if (k2->right)
    rH = k2->right->height;
  
  if (lH > rH)
    k2->height = lH + 1;
  else
    k2->height = rH + 1;
  
  rH = 0;
  lH = 0;
  if (k1->left)
    lH = k1->left->height;
  if (k1->right)
    rH = k1->right->height;
  
  if (lH > rH)
    k1->height = lH + 1;
  else
    k1->height = rH + 1;
  
  return k1;
}

// rotate left
template<typename K, typename V>
typename AVLMap<K,V>::Node* AVLMap<K,V>::left_rotate(Node* k2)
{
  Node* k1 = k2->right;
  k2->right = k1->left;
  k1->left = k2;

  int rH = 0;
  int lH = 0;
  if (k2->left)
    lH = k2->left->height;
  if (k2->right)
    rH = k2->right->height;
  
  if (lH > rH)
    k2->height = lH + 1;
  else
    k2->height = rH + 1;
  
  rH = 0;
  lH = 0;
  if (k1->left)
    lH = k1->left->height;
  if (k1->right)
    rH = k1->right->height;
  
  if (lH > rH)
    k1->height = lH + 1;
  else
    k1->height = rH + 1;
  
  return k1;
}
  
// rebalance
template<typename K, typename V>
typename AVLMap<K,V>::Node* AVLMap<K,V>::rebalance(Node* st_root)
{
  if (!st_root)
    return nullptr;

  Node* lptr = st_root->left;
  Node* rptr = st_root->right;
  
  int BF = 0;
  int rH = 0;
  int lH = 0;
  if (lptr)
    lH = lptr->height;
  if (rptr)
    rH = rptr->height;
  
  BF = lH - rH;
  
  if ((lptr and !rptr) and (lptr->height > 1))
  {
    //check for double
    if (lptr->right != nullptr)
    {
      lptr = left_rotate(lptr);
      st_root->left = lptr;
    }
    //rotate right
    st_root = right_rotate(st_root);
  }
  else if ((!lptr and rptr) and (rptr->height > 1))
  {
    //check for double
    if (rptr->left != nullptr)
    {
      rptr = right_rotate(rptr);
      st_root->right = rptr;
    }
    //rotate left
    st_root = left_rotate(st_root);
  }
  else if ((lptr and rptr) and BF > 1) //left heavy
  {
    //check for double
    if (lptr->right->height > lptr->left->height)
    {
      lptr = left_rotate(lptr);
      st_root->left = lptr;
    }
    //rotate right
    st_root = right_rotate(st_root);
  }
  else if ((lptr and rptr) and BF < -1) //right heavy
  {
    //check for double
    if (rptr->left->height > rptr->right->height)
    {
      rptr = right_rotate(rptr);
      st_root->right = rptr;
    }
    //rotate left
    st_root = left_rotate(st_root);
  }
  return st_root;
}

#endif
