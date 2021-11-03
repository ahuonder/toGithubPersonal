//---------------------------------------------------------------------------
// NAME: Adam Huonder
// FILE: hw4_test.cpp
// DATE: Fall 2021
// DESC: tests the merge sort and quick sort implementations
//       on LinkedSeq and ArraySeq
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "linkedseq.h"
#include "arrayseq.h"

using namespace std;


//----------------------------------------------------------------------
// ArraySeq Merge Sort Tests
//----------------------------------------------------------------------

/*TEST(BasicLinkedSeqTests, ExQuick)
{

  LinkedSeq<int> seq;

  seq.insert(25, 0);
  seq.insert(20,1);
  seq.insert(17,2);
  seq.insert(21,3);
  seq.insert(41,4);
  seq.insert(32,5);
  seq.insert(10,6);
  seq.insert(53,7);

  seq.quick_sort();

  LinkedSeq<int> seq2;

  seq2.insert(10, 0);
  seq2.insert(17,1);
  seq2.insert(20,2);
  seq2.insert(21,3);
  seq2.insert(25,4);
  seq2.insert(32,5);
  seq2.insert(41,6);
  seq2.insert(53,7);
  for (int i = 0; i < 8; ++i)
  {
    ASSERT_EQ(seq[i], seq2[i]);
  }
}*/

TEST(BasicArraySeqTests, EmptySeqMergeSort)
{
  ArraySeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  seq.merge_sort();
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicArraySeqTests, OneElemMergeSort)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
  seq.merge_sort();
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
}

TEST(BasicArraySeqTests, TwoElemInOrderMergeSort)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  seq.merge_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

TEST(BasicArraySeqTests, TwoElemReverseMergeSort)
{
  ArraySeq<int> seq;
  seq.insert(20, 0);
  seq.insert(10, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(20, seq[0]);
  ASSERT_EQ(10, seq[1]); 
  seq.merge_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

TEST(BasicArraySeqTests, ThreeElemMergeSortCases)
{
  ArraySeq<int> seq1; // <10,20,30>
  ArraySeq<int> seq2; // <20,30,10>
  ArraySeq<int> seq3; // <30,10,20>
  seq1.insert(10, 0);
  seq1.insert(20, 1);
  seq1.insert(30, 2);
  seq2.insert(20, 0);
  seq2.insert(30, 1);
  seq2.insert(10, 2);
  seq3.insert(30, 0);
  seq3.insert(10, 1);
  seq3.insert(20, 2);
  seq1.merge_sort();
  seq2.merge_sort();
  seq3.merge_sort();

  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(i*10, seq1[i-1]);
    ASSERT_EQ(i*10, seq2[i-1]);
    ASSERT_EQ(i*10, seq3[i-1]);
  }
}


//----------------------------------------------------------------------
// LinkedSeq Merge Sort Tests
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, EmptySeqMergeSort)
{
  LinkedSeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  seq.merge_sort();
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicLinkedSeqTests, OneElemMergeSort)
{
  LinkedSeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
  seq.merge_sort();
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
}

TEST(BasicLinkedSeqTests, TwoElemInOrderMergeSort)
{
  LinkedSeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  seq.merge_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

TEST(BasicLinkedSeqTests, TwoElemReverseMergeSort)
{
  LinkedSeq<int> seq;
  seq.insert(20, 0);
  seq.insert(10, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(20, seq[0]);
  ASSERT_EQ(10, seq[1]);
  seq.merge_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

TEST(BasicLinkedSeqTests, ThreeElemMergeSortCases)
{
  LinkedSeq<int> seq1; // <10,20,30>
  LinkedSeq<int> seq2; // <20,30,10>
  LinkedSeq<int> seq3; // <30,10,20>
  seq1.insert(10, 0);
  seq1.insert(20, 1);
  seq1.insert(30, 2);
  seq2.insert(20, 0);
  seq2.insert(30, 1);
  seq2.insert(10, 2);
  seq3.insert(30, 0);
  seq3.insert(10, 1);
  seq3.insert(20, 2);
  seq1.merge_sort();
  seq2.merge_sort();
  seq3.merge_sort();
  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(i*10, seq1[i-1]);
    ASSERT_EQ(i*10, seq2[i-1]);
    ASSERT_EQ(i*10, seq3[i-1]);
  }
}

//----------------------------------------------------------------------
// ArraySeq Quick Sort Tests
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, EmptySeqQuickSort)
{
  ArraySeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  seq.quick_sort();
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicArraySeqTests, OneElemQuickSort)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
  seq.quick_sort();
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
}

TEST(BasicArraySeqTests, TwoElemInOrderQuickSort)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  seq.quick_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

TEST(BasicArraySeqTests, TwoElemReverseQuickSort)
{
  ArraySeq<int> seq;
  seq.insert(20, 0);
  seq.insert(10, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(20, seq[0]);
  ASSERT_EQ(10, seq[1]);
  seq.quick_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

TEST(BasicArraySeqTests, ThreeElemQuickSortCases)
{
  ArraySeq<int> seq1; // <10,20,30>
  ArraySeq<int> seq2; // <20,30,10>
  ArraySeq<int> seq3; // <30,10,20>
  seq1.insert(10, 0);
  seq1.insert(20, 1);
  seq1.insert(30, 2);
  seq2.insert(20, 0);
  seq2.insert(30, 1);
  seq2.insert(10, 2);
  seq3.insert(30, 0);
  seq3.insert(10, 1);
  seq3.insert(20, 2);
  seq1.quick_sort();
  seq2.quick_sort();
  seq3.quick_sort();
  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(i*10, seq1[i-1]);
    ASSERT_EQ(i*10, seq2[i-1]);
    ASSERT_EQ(i*10, seq3[i-1]);
  }
}


//----------------------------------------------------------------------
// LinkedSeq Quick Sort Tests
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, EmptySeqQuickSort)
{
  LinkedSeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  seq.quick_sort();
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicLinkedSeqTests, OneElemQuickSort)
{
  LinkedSeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
  seq.quick_sort();
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
}

TEST(BasicLinkedSeqTests, TwoElemInOrderQuickSort)
{
  LinkedSeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  seq.quick_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}


TEST(BasicLinkedSeqTests, TwoElemReverseQuickSort)
{
  LinkedSeq<int> seq;
  seq.insert(20, 0);
  seq.insert(10, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(20, seq[0]);
  ASSERT_EQ(10, seq[1]);
  seq.quick_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

TEST(BasicLinkedSeqTests, ThreeElemQuickSortCases)
{
  LinkedSeq<int> seq1; // <10,20,30>
  LinkedSeq<int> seq2; // <20,30,10>
  LinkedSeq<int> seq3; // <30,10,20>
  seq1.insert(10, 0);
  seq1.insert(20, 1);
  seq1.insert(30, 2);
  seq2.insert(20, 0);
  seq2.insert(30, 1);
  seq2.insert(10, 2);
  seq3.insert(30, 0);
  seq3.insert(10, 1);
  seq3.insert(20, 2);
  seq1.quick_sort();
  seq2.quick_sort();
  seq3.quick_sort();
  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(i*10, seq1[i-1]);
    ASSERT_EQ(i*10, seq2[i-1]);
    ASSERT_EQ(i*10, seq3[i-1]);
  }
}

TEST(BasicArraySeqTests, FourElemMergeSortCases)
{
  ArraySeq<int> seq1; // <1,2,3,4>
  ArraySeq<int> seq2; // <4,3,2,1>
  ArraySeq<int> seq3; // <2,1,3,4>
  
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(3,2);
  seq1.insert(4,3);
  
  seq2.insert(4,0);
  seq2.insert(3,1);
  seq2.insert(2,2);
  seq2.insert(1,3);
  
  seq3.insert(2,0);
  seq3.insert(1,1);
  seq3.insert(3,2);
  seq3.insert(4,3);

  seq1.merge_sort();
  seq2.merge_sort();
  seq3.merge_sort();

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
    ASSERT_EQ(i, seq2[i-1]);
    ASSERT_EQ(i, seq3[i-1]);
  }
}

TEST(BasicArraySeqTests, FourElemQuickSortCases)
{

  ArraySeq<int> seq1; // <1,2,3,4>
  ArraySeq<int> seq2; // <4,3,2,1>
  ArraySeq<int> seq3; // <2,1,3,4>
  
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(3,2);
  seq1.insert(4,3);
  
  seq2.insert(4,0);
  seq2.insert(3,1);
  seq2.insert(2,2);
  seq2.insert(1,3);
  
  seq3.insert(2,0);
  seq3.insert(1,1);
  seq3.insert(3,2);
  seq3.insert(4,3);

  seq1.quick_sort();
  seq2.quick_sort();
  seq3.quick_sort();

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
    ASSERT_EQ(i, seq2[i-1]);
    ASSERT_EQ(i, seq3[i-1]);
  }
}

TEST(BasicLinkedSeqTests, FourElemMergeSortCases)
{

  LinkedSeq<int> seq1; // <1,2,3,4>
  LinkedSeq<int> seq2; // <4,3,2,1>
  LinkedSeq<int> seq3; // <2,1,3,4>
  
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(3,2);
  seq1.insert(4,3);
  
  seq2.insert(4,0);
  seq2.insert(3,1);
  seq2.insert(2,2);
  seq2.insert(1,3);
  
  seq3.insert(2,0);
  seq3.insert(1,1);
  seq3.insert(3,2);
  seq3.insert(4,3);

  seq1.merge_sort();
  seq2.merge_sort();
  seq3.merge_sort();

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
    ASSERT_EQ(i, seq2[i-1]);
    ASSERT_EQ(i, seq3[i-1]);
  }
}

TEST(BasicLinkedSeqTests, FourElemQuickSortCases)
{

  LinkedSeq<int> seq1; // <1,2,3,4>
  LinkedSeq<int> seq2; // <4,3,2,1>
  LinkedSeq<int> seq3; // <2,1,3,4>
  
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(3,2);
  seq1.insert(4,3);
  
  seq2.insert(4,0);
  seq2.insert(3,1);
  seq2.insert(2,2);
  seq2.insert(1,3);
  
  seq3.insert(2,0);
  seq3.insert(1,1);
  seq3.insert(3,2);
  seq3.insert(4,3);

  seq1.quick_sort();
  seq2.quick_sort();
  seq3.quick_sort();

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
    ASSERT_EQ(i, seq2[i-1]);
    ASSERT_EQ(i, seq3[i-1]);
  }
}

//----------------------------------------------------------------------
// TODO: Create 4-Element Merge and Quick Sort Tests for ArraySeq and
//       LinkedSeq. You should end up with four total new tests
//       (ArraySeq MergeSort, ArraySeq QuickSort, LinkedSeq MergeSort,
//       LinkedSeq QuickSort). In each test, you don't need to try all
//       possibilities (there are 24 total cases if we only consider
//       lists with unique values). Instead, you can focus on the
//       cases that can generally occur on the initial recursive
//       step. For example, for merge sort, you can consider the cases
//       for the merge step of two element lists. For quick sort, you
//       can consider the cases of partitioning the four element list
//       with respect to the pivot.
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, FunctionalityAfterMergeSort)
{
  ArraySeq<int> seq1; // <1,2,3,4>
  
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(3,2);
  seq1.insert(4,3);
  
  seq1.merge_sort();

  //accessing values
  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
  }

  //erasing values
  seq1.erase(3);
  seq1.erase(1);
  seq1.erase(0);
  ASSERT_EQ(3, seq1[0]);
  
  //inserting values
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(4,3);

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
  }
  //copying
  ArraySeq<int> seq2; // <10>

  seq2.insert(10,0);

  seq2 = seq1;

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq2[i-1]);
  }

}

TEST(BasicArraySeqTests, FunctionalityAfterQuickSort)
{

  ArraySeq<int> seq1; // <1,2,3,4>
  
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(3,2);
  seq1.insert(4,3);
  
  seq1.quick_sort();
  //accessing values
  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
  }

  //erasing values
  seq1.erase(3);
  seq1.erase(1);
  seq1.erase(0);
  ASSERT_EQ(3, seq1[0]);
  
  //inserting values
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(4,3);

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
  }
  //copying
  ArraySeq<int> seq2; // <10>

  seq2.insert(10,0);

  seq2 = seq1;

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq2[i-1]);
  }
}

TEST(BasicLinkedSeqTests, FunctionalityAfterMergeSort)
{

  LinkedSeq<int> seq1; // <1,2,3,4>
  
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(3,2);
  seq1.insert(4,3);

  seq1.merge_sort();
  //accessing values
  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
  }

  //erasing values
  seq1.erase(3);
  seq1.erase(1);
  seq1.erase(0);
  ASSERT_EQ(3, seq1[0]);
  
  //inserting values
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(4,3);

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
  }
  //copying
  LinkedSeq<int> seq2; // <10>

  seq2.insert(10,0);

  seq2 = seq1;

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq2[i-1]);
  }
}

TEST(BasicLinkedSeqTests, FuncitonalityAfterQuickSort)
{

  LinkedSeq<int> seq1; // <1,2,3,4>
  
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(3,2);
  seq1.insert(4,3);

  seq1.quick_sort();
  //accessing values
  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
  }

  //erasing values
  seq1.erase(3);
  seq1.erase(1);
  seq1.erase(0);
  ASSERT_EQ(3, seq1[0]);
  
  //inserting values
  seq1.insert(1,0);
  seq1.insert(2,1);
  seq1.insert(4,3);

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq1[i-1]);
  }
  //copying
  LinkedSeq<int> seq2; // <10>

  seq2.insert(10,0);

  seq2 = seq1;

  for (int i = 1; i < 5; ++i)
  {
    ASSERT_EQ(i, seq2[i-1]);
  }
}

//----------------------------------------------------------------------
// TODO: Create 4 unit tests to ensure your ArraySeq and LinkedSeq
//       sequences function correctly after they have been sorted
//       using merge sort and quick sort. You should have one test per
//       combination, i.e., one test for merge sort with array
//       sequence, one for merge sort with linked seq, and so
//       on. Things to try are accessing values, inserting values,
//       erasing values, and copying.
//----------------------------------------------------------------------



//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
