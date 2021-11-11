//---------------------------------------------------------------------------
// NAME: Adam Huonder
// DATE: Fall 2021
// DESC: implements linked map
//---------------------------------------------------------------------------

#ifndef LINKEDMAP_H
#define LINKEDMAP_H

#include "map.h"
#include "linkedseq.h"


template<typename K, typename V>
class LinkedMap : public Map<K,V>
{
public:

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

  // Returns true if the key is in the collection, and false
  // otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns all the keys in the collection
  ArraySeq<K> all_keys() const;  

  // Returns the keys in the collection in ascending sorted order.
  ArraySeq<K> sorted_keys() const;  

private:

  // implemented as a linked list of (key-value) pairs
  LinkedSeq<std::pair<K,V>> seq;

};


// TODO: Implement the LinkedMap functions below. Note that you do not
//       need to implement a default constructor, destructor, copy
//       constructor, copy assignment operator, move constructor, and
//       move assignment operator for this version of Map. Instead,
//       the default C++ implementations are sufficient.


// Returns the number of key-value pairs in the map
template<typename K, typename V>
int LinkedMap<K,V>::size() const 
{
  return seq.size();
}

// Tests if the map is empty
template<typename K, typename V>
bool LinkedMap<K,V>::empty() const 
{
  if (seq.size() == 0)
    return true;
  return false;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& LinkedMap<K,V>::operator[](const K& key)
{
  for (int i = 0; i < seq.size(); ++i) 
  {
    if (seq[i].first == key)
      return seq[i].second;
  }
  throw std::out_of_range("V& LinkedMap<K,V>::operator[](const K& key). Key does not exist.");
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection. 
template<typename K, typename V>
const V& LinkedMap<K,V>::operator[](const K& key) const
{
  for (int i = 0; i < seq.size(); ++i) 
  {
    if (seq[i].first == key)
      return seq[i].second;
  }
  throw std::out_of_range("V& LinkedMap<K,V>::operator[](const K& key). Key does not exist.");
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template<typename K, typename V>
void LinkedMap<K,V>::insert(const K& key, const V& value)
{
  seq.insert(std::pair<K,V> {key, value}, seq.size());
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void LinkedMap<K,V>::erase(const K& key)
{
  int index = -1;
  for (int i = 0; i < seq.size(); ++i)
  {
    if (seq[i].first == key)
    {
      index = i;
      break;
    }
  }
  if (index == -1)
    throw std::out_of_range("void LinkedMap<K,V>::erase(const K& key). Key does not exist.");

  seq.erase(index);
}

// Returns true if the key is in the collection, and false
// otherwise.
template<typename K, typename V>
bool LinkedMap<K,V>::contains(const K& key) const 
{
  for (int i = 0; i < seq.size(); ++i)
  {
    if (seq[i].first == key)
      return true;
  }
  return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> LinkedMap<K,V>::find_keys(const K& k1, const K& k2) const 
{
  ArraySeq<K> tmp;

  for (int i = 0; i < seq.size(); ++i)
  {
    if (k1 <= seq[i].first and seq[i].first <= k2)
      tmp.insert(seq[i].first, tmp.size());
  }
  return tmp;
}

// Returns all the keys in the collection
template<typename K, typename V>
ArraySeq<K> LinkedMap<K,V>::all_keys() const 
{
  ArraySeq<K> tmp;

  for (int i = 0; i < seq.size; ++i)
  {
    tmp.insert(seq[i].first, tmp.size());
  }
  return tmp;
}

// Returns the keys in the collection in ascending sorted order.
template<typename K, typename V>
ArraySeq<K> LinkedMap<K,V>::sorted_keys() const 
{
  ArraySeq<K> tmp;
  
  for (int i = 0; i < seq.size(); ++i)
  {
    tmp.insert(seq[i].first, i);
  }
  tmp.sort();
  return tmp;
}

#endif
