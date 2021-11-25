#ifndef HASHMAP_H
#define HASHMAP_H

#include <functional>
#include "map.h"
#include "arrayseq.h"

//{{{ Header
template<typename K, typename V>
class HashMap : public Map<K,V>
{
public:

  // default constructor
  HashMap();

  // copy constructor
  HashMap(const HashMap& rhs);

  // move constructor
  HashMap(HashMap&& rhs);

  // copy assignment
  HashMap& operator=(const HashMap& rhs);

  // move assignment
  HashMap& operator=(HashMap&& rhs);  

  // destructor
  ~HashMap();
  
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

  // statistics functions for the hash table implementation
  int min_chain_length() const;
  int max_chain_length() const;
  double avg_chain_length() const;
  
private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    Node* next;
  };

  // number of key-value pairs in map
  int count = 0;

  // max size of the (array) table
  int capacity = 16;

  // threshold for resize and rehash
  const double load_factor_threshold = 0.75;
  
  // array of linked lists
  Node** table = new Node*[capacity];

  // the hash function
  int hash(const K& key) const;

  // resize and rehash the table
  void resize_and_rehash();

  // initialize the table to all nullptr
  void init_table();
  
  // clean up the table and reset member variables
  void make_empty();
};
//}}}

// TODO: implement the public and private HashMap functions below.

//{{{ public functions / essential operators
// default constructor
template<typename K, typename V>
HashMap<K,V>::HashMap()
{
  init_table();
}

// copy constructor
template<typename K, typename V>
HashMap<K,V>::HashMap(const HashMap& rhs)
{
  if (this != &rhs)
  {
    init_table();
    make_empty();
    table = new Node*[rhs.capacity];//could this be a mem leak?
    count = rhs.count;
    capacity = rhs.capacity;
    init_table();
    for (int i = 0; i < capacity; ++i)
    {
      Node* tmp = rhs.table[i];
      while (tmp != nullptr)
      {
        Node* cpy = new Node;
        cpy->key = tmp->key;
        cpy->value = tmp->value;
        cpy->next = table[i];
        table[i] = cpy;
        tmp = tmp->next;
      }
    }
  }
}

// move constructor
template<typename K, typename V>
HashMap<K,V>::HashMap(HashMap&& rhs)
{
  init_table();
  make_empty();
  capacity = rhs.capacity;
  count = rhs.count;
  table = rhs.table;
  //come back to this
  rhs.table = nullptr;
  rhs.count = 0;
  rhs.capacity = 0;
}

// copy assignment
template<typename K, typename V>
HashMap<K,V>& HashMap<K,V>::operator=(const HashMap& rhs)
{
  if (this != &rhs)
  {
    make_empty();
    table = new Node*[rhs.capacity];//could this be a mem leak?
    count = rhs.count;
    capacity = rhs.capacity;
    init_table();
    for (int i = 0; i < capacity; ++i)
    {
      Node* tmp = rhs.table[i];
      while (tmp != nullptr)
      {
        Node* cpy = new Node;
        cpy->key = tmp->key;
        cpy->value = tmp->value;
        cpy->next = table[i];
        table[i] = cpy;
        tmp = tmp->next;
      }
    }
  }
  return *this;
}

// move assignment
template<typename K, typename V>
HashMap<K,V>& HashMap<K,V>::operator=(HashMap&& rhs)
{
  if (this != &rhs)
  {
    make_empty();
    capacity = rhs.capacity;
    count = rhs.count;
    table = rhs.table;
    rhs.table = new Node*[16];
    rhs.count = 0;
    rhs.capacity = 16;
    rhs.init_table();
  }
  return *this;
}

// destructor
template<typename K, typename V>
HashMap<K,V>::~HashMap()
{
  make_empty();
}
  
// Returns the number of key-value pairs in the map
template<typename K, typename V>
int HashMap<K,V>::size() const
{
  return count;
}

// Tests if the map is empty
template<typename K, typename V>
bool HashMap<K,V>::empty() const
{
  if (count == 0)
    return true;
  return false;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& HashMap<K,V>::operator[](const K& key)
{
  int index = hash(key) % capacity;
  Node* tmp = table[index];
  while (tmp != nullptr)
  {
    if (tmp->key == key)
      return tmp->value;
    tmp = tmp->next;
  }
  throw std::out_of_range("V& HashMap<K,V>::operator[](const K& key). Key does not exist.");
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection. 
template<typename K, typename V>
const V& HashMap<K,V>::operator[](const K& key) const
{
  int index = hash(key) % capacity;
  Node* tmp = table[index];
  while (tmp != nullptr)
  {
    if (tmp->key == key)
      return tmp->value;
    tmp = tmp->next;
  }
  throw std::out_of_range("const V& HashMap<K,V>::operator[](const K& key) const. Key does not exist.");
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template<typename K, typename V>
void HashMap<K,V>::insert(const K& key, const V& value)
{
  Node* in = new Node;
  in->key = key;
  in->value = value;
  int index = hash(key) % capacity;
  in->next = table[index];
  table[index] = in;
  count++;
  if ((count * 1.0) / (capacity * 1.0) >= 0.75)
    resize_and_rehash();
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void HashMap<K,V>::erase(const K& key)
{
  int index = hash(key) % capacity;
  Node* tmp = table[index];
  Node* pre = nullptr;
  while (tmp != nullptr)
  {
    if (tmp->key == key)
    {
      if (pre == nullptr)
      {
        table[index] = tmp->next;
        delete tmp;
        count--;
        return;
      }
      pre->next = tmp->next;
      delete tmp;
      count--;
      return;
    }
    pre = tmp;
    tmp = tmp->next;
  }
  throw std::out_of_range("void HashMap<K,V>::erase(const K& key). Key does not exist.");
}

// Returns true if the key is in the collection, and false otherwise.
template<typename K, typename V>
bool HashMap<K,V>::contains(const K& key) const
{
  int index = hash(key) % capacity;
  Node* tmp = table[index];
  while (tmp != nullptr)
  {
    if (tmp->key == key)
      return true;
    tmp = tmp->next;
  }
  return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> HashMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  ArraySeq<K> keys;
  for (int i = 0; i < capacity; ++i)
  {
    Node* tmp = table[i];
    while(tmp != nullptr)
    {
      if (tmp->key >= k1 and tmp->key <= k2)
        keys.insert(tmp->key, keys.size());
      tmp = tmp->next;
    }
  }
  return keys;
}

// Returns the keys in the collection in ascending sorted order
template<typename K, typename V>
ArraySeq<K> HashMap<K,V>::sorted_keys() const
{
  ArraySeq<K> keys;
  for (int i = 0; i < capacity; ++i)
  {
    Node* tmp = table[i];
    while (tmp != nullptr)
    {
      keys.insert(tmp->key, keys.size());
      tmp = tmp->next;
    }
  }
  return keys;
}
//}}}

//{{{ statistics functions for the hash table implementation
template<typename K, typename V>
int HashMap<K,V>::min_chain_length() const
{
  int minChain = 1;
  if (count == 0)
    return 0;

  for (int i = 0; i < capacity; ++i)
  {
    Node* tmp = table[i];
    int chainCount = 0;
    while (tmp != nullptr)
    {
      chainCount++;
      tmp = tmp->next;
    }
    if (chainCount > 0 and chainCount < minChain)
      minChain = chainCount;
  }
  return minChain;
}

template<typename K, typename V>
int HashMap<K,V>::max_chain_length() const
{
  int maxChain = 0;
  if (count == 0)
    return 0;

  for (int i = 0; i < capacity; ++i)
  {
    Node* tmp = table[i];
    int chainCount = 0;
    while (tmp != nullptr)
    {
      chainCount++;
      tmp = tmp->next;
    }
    if (chainCount > maxChain or i == 0)
      maxChain = chainCount;
  }
  return maxChain;
}

template<typename K, typename V>
double HashMap<K,V>::avg_chain_length() const
{
  int totalChains = 0;
  double avgChain = 0.0;
  int currChain = 0;
  int chainNumTotal = 0;
  
  if (count == 0)
    return 0.0;

  for (int i = 0; i < capacity; ++i)
  {
    Node* tmp = table[i];
    if (tmp != nullptr)
    {
      totalChains++;
      while(tmp != nullptr)
      {
        currChain++;
        tmp = tmp->next;
      }
      chainNumTotal += currChain;
      currChain = 0;
    }
  }
  avgChain = (chainNumTotal * 1.0) / (totalChains * 1.0);
  return avgChain;
}
//}}}

//{{{ private functions
// the hash function
template<typename K, typename V>
int HashMap<K,V>::hash(const K& key) const
{
  std::hash<K> hash_fun;
  int index = hash_fun(key);
  return index;
}

// resize and rehash the table
template<typename K, typename V>
void HashMap<K,V>::resize_and_rehash()
{
  Node** table2 = new Node*[capacity * 2];
  for (int i = 0; i < capacity * 2; ++i)
  {
    table2[i] = nullptr;
  }
  
  for (int i = 0; i < capacity; ++i)
  {
    //go through old table and rehash all values into new slots.
    Node* tmp = table[i];
    while (table[i] != nullptr)
    {
      Node* tmp = table[i];
      int rehashIndex = hash(table[i]->key) % (capacity * 2);
      if (table2[rehashIndex] == nullptr)
      {
        table2[rehashIndex] = table[i];
        table2[rehashIndex]->next = nullptr;
        table[i] = table[i]->next;
      }
      else
      {
        table[i] = table[i]->next;
        tmp->next = table2[rehashIndex];
        table2[rehashIndex] = tmp;
      }
    }
  }
  init_table();
  delete[] table;
  capacity *= 2;
  table = table2;
}

// initialize the table to all nullptr
template<typename K, typename V>
void HashMap<K,V>::init_table()
{
  for (int i = 0; i < capacity; ++i)
    table[i] = nullptr;
}
  
// clean up the table and reset member variables
template<typename K, typename V>
void HashMap<K,V>::make_empty()
{
  for (int i = 0; i < capacity; ++i)
  {
    if (table[i] != nullptr)
    {
      //clean linked list
      while (table[i] != nullptr)
      {
        Node* del = table[i];
        table[i] = table[i]->next;
        delete del;
        del = nullptr;
      }
    }
  }
  delete[] table;
}
//}}}

#endif
