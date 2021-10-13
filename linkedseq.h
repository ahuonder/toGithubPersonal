
//---------------------------------------------------------------------------
// NAME: Adam Huonder
// FILE: linkedlist.h
// DATE: Fall 2021
// DESC: Implements LinkedSeq, a subclass of Sequence
//----------------------------------------------------------------------


#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <ostream>
#include "sequence.h"

template<typename T>
class LinkedSeq : public Sequence<T>
{
public:

  // Default constructor
  LinkedSeq();

  // Copy constructor
  LinkedSeq(const LinkedSeq& rhs);

  // Move constructor
  LinkedSeq(LinkedSeq&& rhs);

  // Copy assignment operator
  LinkedSeq& operator=(const LinkedSeq& rhs);

  // Move assignment operator
  LinkedSeq& operator=(LinkedSeq&& rhs);
  
  // Destructor
  ~LinkedSeq();
  
  // Returns the number of elements in the sequence
  int size() const override;

  // Tests if the sequence is empty
  bool empty() const override;

  // Returns a reference to the element at the index in the
  // sequence. Used for lvalues (assignments into the
  // sequence). Throws out_of_range if index is invalid (less than 0
  // or greater than or equal to size()).
  T& operator[](int index) override;

  // Returns a constant address to the element at the index in the
  // sequence. Used for rvalues (evaluating to the value at the
  // index). Throws out_of_range if index is invalid (less than 0 or
  // greater than or equal to size()).
  const T& operator[](int index) const override;

  // Extends (grows) the sequence by inserting the element at the
  // given index (shifting existing elements to the "right" in the
  // sequence).  Throws out_of_range if the index is invalid (less
  // than 0 or greater than size()).
  void insert(const T& elem, int index) override;

  // Shrinks the sequence by removing the element at the index in the
  // sequence (shifing elements to the "left" in the sequence). Throws
  // out_of_range if index is invalid.
  void erase(int index) override;

  // Returns true if the element is in the sequence, and false
  // otherwise.
  bool contains(const T& elem) const override;

  // Sorts the elements in the sequence using less than equal (<=)
  // operator. (Not implemented in HW-2)
  void sort() override; 
  
private:

  // linked list node
  struct Node {
    T value;
    Node* next = nullptr;
  };

  // head pointer
  Node* head = nullptr;

  // tail pointer
  Node* tail = nullptr;

  // size of list
  int node_count = 0;

  // helper to delete all the nodes in the list (called by destructor
  // and copy assignment operator)
  void make_empty();
};


// TODO: implement the following stream insertion operator. Note that
//       the function should be implemented using only public
//       functions of LinkedSeq

template<typename T>
std::ostream& operator<<(std::ostream& stream, const LinkedSeq<T>& seq)
{
  for (int i = 0; i < seq.size(); ++i)
  {
    if (i == 0)
      stream << seq[i];
    else
      stream << ", " << seq[i];
  }
  return stream;
}

template<typename T>
LinkedSeq<T>::LinkedSeq()
{
}

// TODO: Finish the remaining LinkedSeq functions below. To get your
//       code to initially compile, "stub out" each function (i.e.,
//       define each function but with an empty function body less a
//       return if required by the function). Then incrementally
//       implement each function as per the homework specfications.

//copy constructor
template<typename T>
LinkedSeq<T>::LinkedSeq(const LinkedSeq& rhs)
{
  node_count = 0;
  Node* tmp = rhs.head;
  
  if (tmp != nullptr)
  {
    for (int i = 0; i < rhs.node_count; ++i)
    {
      insert(tmp->value, i);
      tmp = tmp->next;
    }
  }
}

//move constructor
template<typename T>
LinkedSeq<T>::LinkedSeq(LinkedSeq&& rhs)
{
  head = rhs.head;
  tail = rhs.tail;
  node_count = rhs.node_count;

  rhs.tail = nullptr;
  rhs.head = nullptr;
  rhs.node_count = 0;
}

// Copy assignment operator
template<typename T>
LinkedSeq<T>& LinkedSeq<T>::operator=(const LinkedSeq& rhs)
{
  if (this != &rhs)
  {
    make_empty();
    if (rhs.node_count > 0)
    {
      Node* tmp = rhs.head;

      for (int i = 0; i < rhs.node_count; ++i)
      {
        insert(tmp->value, i);
        tmp = tmp->next;
      }
    }
  }
  return *this;
}

// Move assignment operator
template<typename T>
LinkedSeq<T>& LinkedSeq<T>::operator=(LinkedSeq&& rhs)
{
  if (this != &rhs)
  {
    make_empty();
    head = rhs.head;
    tail = rhs.tail;
    node_count = rhs.node_count;
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.node_count = 0;
  }
  return *this;
}

// Destructor
template<typename T>
LinkedSeq<T>::~LinkedSeq()
{
  make_empty();
}

// Returns the number of elements in the sequence
template<typename T>
int LinkedSeq<T>::size() const 
{
  return node_count;
}

// Tests if the sequence is empty
template<typename T>
bool LinkedSeq<T>::empty() const 
{
  if (node_count == 0)
    return true;

  return false;
}

// Returns a reference to the element at the index in the
// sequence. Used for lvalues (assignments into the
// sequence). Throws out_of_range if index is invalid (less than 0
// or greater than or equal to size()).
template<typename T>
T& LinkedSeq<T>::operator[](int index) 
{
  if (index < 0 or index >= node_count)
  {
    throw std::out_of_range("LinkedSeq<T> : operator[]");
  }

  Node* tmp = head;
  
  for (int i = 0; i < index; ++i)
  {
    tmp = tmp->next;
  }
  
  return tmp->value;
}

// Returns a constant address to the element at the index in the
// sequence. Used for rvalues (evaluating to the value at the
// index). Throws out_of_range if index is invalid (less than 0 or
// greater than or equal to size()).
template<typename T>
const T& LinkedSeq<T>::operator[](int index) const 
{
  if (index < 0 or index >= node_count)
  {
    throw std::out_of_range("LinkedSeq<T> : operator[]");
  }

  Node* tmp = head;
  
  for (int i = 0; i < index; ++i)
  {
    tmp = tmp->next;
  }
  
  return tmp->value;
}

// Extends (grows) the sequence by inserting the element at the
// given index (shifting existing elements to the "right" in the
// sequence).  Throws out_of_range if the index is invalid (less
// than 0 or greater than size()).
template<typename T>
void LinkedSeq<T>::insert(const T& elem, int index) 
{
  if (index < 0 or index > node_count)
  {
    throw std::out_of_range("LinkedSeq<T> : insert(const T& elem, int index)");
  }
  
  Node* tmp = new Node;
  
  if (node_count == 0)
  {
    tmp->value = elem;
    tmp->next = nullptr;
    head = tmp;
    tail = tmp;
    ++node_count;
    return;
  }

  if (index == 0)
  {
    tmp->value = elem;
    tmp->next = head;
    head = tmp;
    ++node_count;
    return;
  }
  
  if (index == node_count)
  {
    tmp->value = elem;
    tmp->next = nullptr;
    tail->next = tmp;
    tail = tmp;
    ++node_count;
    return;
  }

  Node* ptr = head;

  for (int i = 0; i < index - 1; ++i)
  {
    ptr = ptr->next;
  }
  
  tmp->value = elem;
  tmp->next = ptr->next;
  ptr->next = tmp;
  ++node_count;

}

// Shrinks the sequence by removing the element at the index in the
// sequence (shifing elements to the "left" in the sequence). Throws
// out_of_range if index is invalid.
template<typename T>
void LinkedSeq<T>::erase(int index)
{
  if (index < 0 or index >= node_count)
  {
    throw std::out_of_range("LinkedSeq<T> : erase(int index)");
  }
  
  Node* ptr = head;
  Node* del = nullptr;
  
  if (index == 0)
  {
    head = head->next;
    delete ptr;
    --node_count;
    return;
  }

  for (int i = 0; i < index - 1; ++i)
  {
    ptr = ptr->next;
  }
  
  del = ptr->next;
  ptr->next = del->next;

  if (del->next == nullptr)
    tail = ptr;

  delete del;
  --node_count;
}

// Returns true if the element is in the sequence, and false
// otherwise.
template<typename T>
bool LinkedSeq<T>::contains(const T& elem) const 
{
  Node* ptr = head;
  
  if (node_count == 0)
    return false;

  for (int i = 0; i < node_count; ++i)
  {
    if (ptr->value == elem)
      return true;

    ptr = ptr->next;
  }

  return false;
}

template<typename T>
void LinkedSeq<T>::make_empty()
{
  int count = node_count;
  
  for (int i = 0; i < count; ++i)
  {
    erase(0);
  }
  head = nullptr;
  tail = nullptr;
}

template<typename T>
void LinkedSeq<T>::sort()
{
  // TODO: saved for a future assignment
}


#endif
