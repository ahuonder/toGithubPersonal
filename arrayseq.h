
//---------------------------------------------------------------------------
// NAME: Adam Huonder
// FILE: arrayseq.h
// DATE: Fall 2021
// DESC: Implements ArraySeq, a subclass of Sequence
//----------------------------------------------------------------------


#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdexcept>
#include <ostream>
#include "sequence.h"


template<typename T>
class ArraySeq : public Sequence<T>
{
public:

  // Default constructor
  ArraySeq();

  // Copy constructor
  ArraySeq(const ArraySeq& rhs);

  // Move constructor
  ArraySeq(ArraySeq&& rhs);

  // Copy assignment operator
  ArraySeq& operator=(const ArraySeq& rhs);

  // Move assignment operator
  ArraySeq& operator=(ArraySeq&& rhs);
  
  // Destructor
  ~ArraySeq();
  
  // Returns the number of elements in the sequence
  virtual int size() const;

  // Tests if the sequence is empty
  virtual bool empty() const;

  // Returns a reference to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual T& operator[](int index);

  // Returns a constant address to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual const T& operator[](int index) const;

  // Extends the sequence by inserting the element at the given
  // index. Throws out_of_range if the index is invalid.
  virtual void insert(const T& elem, int index);

  // Shrinks the sequence by removing the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual void erase(int index);

  // Returns true if the element is in the sequence, and false
  // otherwise.
  virtual bool contains(const T& elem) const;

  // Sorts the elements in the sequence using less than equal (<=)
  // operator. (Not implemented in HW-3)
  virtual void sort(); 
  
private:

  // resizable array
  T* array = nullptr;

  // size of list
  int count = 0;

  // max capacity of the array
  int capacity = 0;

  // helper to double the capacity of the array
  void resize();
  
  // helper to delete the array list (called by destructor and copy
  // constructor)
  void make_empty();

};

// << operator
template<typename T>
std::ostream& operator<<(std::ostream& stream, const ArraySeq<T>& aSeq)
{
  for (int i = 0; i < aSeq.size(); ++i)
  {
    if (i != 0)
    {
      stream << ", " << aSeq[i];
    }
    else 
    {
      stream << aSeq[i];
    }
  }
  return stream;
}

//constructor
template<typename T>
ArraySeq<T>::ArraySeq()
{
}


template<typename T>
void ArraySeq<T>::sort()
{
  // TODO: saved for future assignment
}


// TODO: Implement the above functions below using the approaches
//       discussed in class and specified in the homework assignment.

// Copy constructor
template<typename T>
ArraySeq<T>::ArraySeq(const ArraySeq& rhs)
{
  array = new T[rhs.capacity];
  count = rhs.count;
  capacity = rhs.capacity;
  
  for (int i = 0; i < count; ++i)
  {
    array[i] = rhs[i];
  }
}

// Move constructor
template<typename T>
ArraySeq<T>::ArraySeq(ArraySeq&& rhs)
{
  array = rhs.array;
  count = rhs.count;
  capacity = rhs.capacity;
  rhs.array = nullptr;
  rhs.count = 0;
  rhs.capacity = 0;
}

// Copy assignment operator
template<typename T>
ArraySeq<T>& ArraySeq<T>::operator=(const ArraySeq& rhs)
{
  if (array == rhs.array)
    return *this;

  delete[] array;
  array = new T[rhs.capacity];
  count = rhs.count;
  capacity = rhs.capacity;

  for (int i = 0; i < rhs.count; ++i)
  {
    array[i] = rhs.array[i];
  }
  return *this;
}

// Move assignment operator
template<typename T>
ArraySeq<T>& ArraySeq<T>::operator=(ArraySeq&& rhs)
{
  array = rhs.array;
  count = rhs.count;
  capacity = rhs.capacity;
  rhs.array = nullptr;
}
  
// Destructor
template<typename T>
ArraySeq<T>::~ArraySeq()
{
  make_empty();
}
  
// Returns the number of elements in the sequence
template<typename T>
int ArraySeq<T>::size() const
{
  return count;
}

// Tests if the sequence is empty
template<typename T>
bool ArraySeq<T>::empty() const
{
  if (count == 0)
    return true;
  return false;
}

// Returns a reference to the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
T& ArraySeq<T>::operator[](int index)
{
  if (index < 0 or index >= count)
  {
    throw std::out_of_range("T& ArraySeq<T>::operator[](int index)");
  }

  return array[index];
}

// Returns a constant address to the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
const T& ArraySeq<T>::operator[](int index) const
{
  if (index < 0 or index >= count)
  {
    throw std::out_of_range("const T& ArraySeq<T>::operator[](int index)");
  }

  return array[index];
}

// Extends the sequence by inserting the element at the given
// index. Throws out_of_range if the index is invalid.
template<typename T>
void ArraySeq<T>::insert(const T& elem, int index)
{
  if (index < 0 or index > count)
  {
    throw std::out_of_range("void ArraySeq<T>insert(const T& elem, int index)");
  }

  if (count == capacity)
  {
    resize();
  }

  for (int i = count; i > index; --i)
  {
    array[i] = array[i-1];
  }
  //std::cout << *array << std::endl;
  //std::cout << "before assignment " << count << " " << capacity << " " << elem << std::endl;
  //array[0] = 5;
  //std::cout << "after first assignment" << std::endl;
  array[index] = elem;
  ++count;
  //std::cout << "after assignment" << std::endl;
}

// Shrinks the sequence by removing the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
void ArraySeq<T>::erase(int index)
{
  if (index < 0 or index >= count)
  {
    throw std::out_of_range("void ArraySeq<T>::erase(int index)");
  }

  for (int i = index; i < count - 1; ++i)
  {
    array[i] = array[i+1];
  }

  --count;
}

// Returns true if the element is in the sequence, and false
// otherwise.
template<typename T>
bool ArraySeq<T>::contains(const T& elem) const
{
  for (int i = 0; i < count; ++i)
  {
    if (array[i] == elem)
      return true;
  }

  return false;
}

// helper to double the capacity of the array
template<typename T>
void ArraySeq<T>::resize()
{
  if (capacity == 0)
  {
    array = new T[1];
    capacity = 1;
    return;
  }

  T* array2 = new T[capacity * 2];
  
  for (int i = 0; i < count; ++i)
  {
    array2[i] = array[i];
  }

  capacity *= 2;

  delete[] array;

  array = array2;
  array2 = nullptr;
}
  
// helper to delete the array list (called by destructor and copy
// constructor)
template<typename T>
void ArraySeq<T>::make_empty()
{
  delete[] array;
  array = nullptr;
  count = 0;
  capacity = 0;
}



#endif
