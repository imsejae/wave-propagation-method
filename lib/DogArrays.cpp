// turn on CHECK_BOUNDS before including DogArrays.h
// so that the non-inline versions of get and set are declared.
// This way they are implemented in this file so that
// elsewhere in the code one can choose whether to use
// the in-line or bounds-checking versions of get and set
#ifndef CHECK_BOUNDS
#define CHECK_BOUNDS
#endif

#include "DogArrays.h"
#include "assert.h"
#include <cmath>

// --------------------------------------------------------------
// class IntArray
// --------------------------------------------------------------

// -------------------------------------------------------------------------- //
// Constructor 1-index
IntArray::IntArray(const int in_index_length1)
{
  assert_ge(in_index_length1,1);

  num_indeces = 1;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;

  compute_total_length();
  int tmp = in_index_length1;
  assert_eq(total_length,tmp);
  vec = new int[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Constructor 2-index
IntArray::IntArray(const int in_index_length1,
                   const int in_index_length2)
{
  assert_ge(in_index_length1,1);
  assert_ge(in_index_length2,1);

  num_indeces = 2;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;
  index_length[1] = in_index_length2;

  compute_total_length();
  int tmp = in_index_length1*in_index_length2;
  assert_eq(total_length,tmp);
  vec = new int[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Constructor 3-index
IntArray::IntArray(const int in_index_length1,
                   const int in_index_length2,
                   const int in_index_length3)
{
  assert_ge(in_index_length1,1);
  assert_ge(in_index_length2,1);
  assert_ge(in_index_length3,1);

  num_indeces = 3;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;
  index_length[1] = in_index_length2;
  index_length[2] = in_index_length3;

  compute_total_length();
  int tmp = in_index_length1*in_index_length2*in_index_length3;
  assert_eq(total_length,tmp);
  vec = new int[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Constructor 4-index
IntArray::IntArray(const int in_index_length1,
                   const int in_index_length2,
                   const int in_index_length3,
                   const int in_index_length4)
{
  assert_ge(in_index_length1,1);
  assert_ge(in_index_length2,1);
  assert_ge(in_index_length3,1);
  assert_ge(in_index_length4,1);

  num_indeces = 4;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;
  index_length[1] = in_index_length2;
  index_length[2] = in_index_length3;
  index_length[3] = in_index_length4;

  compute_total_length();
  int tmp = in_index_length1*in_index_length2*in_index_length3\
       *in_index_length4;
  assert_eq(total_length,tmp);
  vec = new int[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Constructor 5-index
IntArray::IntArray(const int in_index_length1,
                   const int in_index_length2,
                   const int in_index_length3,
                   const int in_index_length4,
                   const int in_index_length5)
{
  assert_ge(in_index_length1,1);
  assert_ge(in_index_length2,1);
  assert_ge(in_index_length3,1);
  assert_ge(in_index_length4,1);
  assert_ge(in_index_length5,1);

  num_indeces = 5;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;
  index_length[1] = in_index_length2;
  index_length[2] = in_index_length3;
  index_length[3] = in_index_length4;
  index_length[4] = in_index_length5;

  compute_total_length();
  int tmp = in_index_length1*in_index_length2*in_index_length3\
       *in_index_length4*in_index_length5;
  assert_eq(total_length,tmp);
  vec = new int[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Constructor 6-index
IntArray::IntArray(const int in_index_length1,
                   const int in_index_length2,
                   const int in_index_length3,
                   const int in_index_length4,
                   const int in_index_length5,
                   const int in_index_length6)
{
  assert_ge(in_index_length1,1);
  assert_ge(in_index_length2,1);
  assert_ge(in_index_length3,1);
  assert_ge(in_index_length4,1);
  assert_ge(in_index_length5,1);
  assert_ge(in_index_length6,1);

  num_indeces = 6;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;
  index_length[1] = in_index_length2;
  index_length[2] = in_index_length3;
  index_length[3] = in_index_length4;
  index_length[4] = in_index_length5;
  index_length[5] = in_index_length6;

  compute_total_length();
  int tmp = in_index_length1*in_index_length2*in_index_length3\
       *in_index_length4*in_index_length5*in_index_length6;
  assert_eq(total_length,tmp);
  vec = new int[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Helper routine to compute total_length value
void IntArray::compute_total_length()
{
  assert_ge(num_indeces,1);
  total_length = 1;
  for (int i=0; i<num_indeces; i++)
    { total_length = total_length*index_length[i]; }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Copy constructor
IntArray::IntArray(const IntArray& anotherIntArray)
{
  num_indeces = anotherIntArray.num_indeces;
  total_length = anotherIntArray.total_length;

  index_length = new int[num_indeces];
  vec = new int[total_length];

  for (int i=0; i<num_indeces; i++)
    { index_length[i] = anotherIntArray.index_length[i]; }

  for (int i=0; i<total_length; i++)
    { vec[i] = anotherIntArray.vec[i]; }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Destructor
IntArray::~IntArray()
{
  delete[] vec;
  delete[] index_length;
  num_indeces = 0;
  total_length = 0;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Number of indeces
int IntArray::get_num_ind() const
{
  return num_indeces;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Individual index length information
int IntArray::get_ind_length(const int n) const
{
  assert_ge(n,1);
  assert_le(n,num_indeces);
  return index_length[n-1];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Total length information
int IntArray::get_total_length() const
{
  return total_length;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Resize 1-index
void IntArray::resize(const int in_index_length1)
{
  assert_eq(num_indeces,1);

  delete[] index_length;
  delete[] vec;

  assert_ge(in_index_length1,1);

  num_indeces = 1;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;

  compute_total_length();
  vec = new int[in_index_length1];
}
// -------------------------------------------------------------------------- //

// *********************************************************
#ifdef CHECK_BOUNDS
// *********************************************************

// ----------------------------
// Direct get and set functions
// ----------------------------

// -------------------------------------------------------------------------- //
const int& IntArray::vget(const int k) const
{
  assert_ge(k,0);
  assert_lt(k,total_length);
  return vec[k];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void IntArray::vset(const int k, const int value)
{
  assert_ge(k,0);
  assert_lt(k,total_length);
  vec[k] = value;
}
// -------------------------------------------------------------------------- //

// ----------------------------
// Direct get and set functions - 1 indexed
// ----------------------------

// -------------------------------------------------------------------------- //
const int& IntArray::dget(const int k) const
{
  assert_ge(k,1);
  assert_le(k,total_length);
  return vec[k-1];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void IntArray::dset(const int k, const int value)
{
  assert_ge(k,1);
  assert_le(k,total_length);
  vec[k-1] = value;
}
// -------------------------------------------------------------------------- //

// -------------------
// Get index functions
// -------------------

// -------------------------------------------------------------------------- //
// 1-index
int IntArray::getidx(const int n1) const
{
  assert_eq(num_indeces,1);
  check_index(1,n1);

  int itmp = n1-1;

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// 2-index
int IntArray::getidx(const int n1,
                     const int n2) const
{
  assert_eq(num_indeces,2);
  check_index(1,n1);
  check_index(2,n2);

  int itmp = ((n1-1)*index_length[1] + (n2-1));

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// 3-index
int IntArray::getidx(const int n1,
                     const int n2,
                     const int n3) const
{
  assert_eq(num_indeces,3);
  check_index(1,n1);
  check_index(2,n2);
  check_index(3,n3);

  int itmp = ((n1-1)*index_length[1] + (n2-1));
  itmp = itmp*index_length[2] + (n3-1);

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// 4-index
int IntArray::getidx(const int n1,
                     const int n2,
                     const int n3,
                     const int n4) const
{
  assert_eq(num_indeces,4);
  check_index(1,n1);
  check_index(2,n2);
  check_index(3,n3);
  check_index(4,n4);

  int itmp = ((n1-1)*index_length[1] + (n2-1));
  itmp = itmp*index_length[2] + (n3-1);
  itmp = itmp*index_length[3] + (n4-1);

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// 5-index
int IntArray::getidx(const int n1,
                     const int n2,
                     const int n3,
                     const int n4,
                     const int n5) const
{
  assert_eq(num_indeces,5);
  check_index(1,n1);
  check_index(2,n2);
  check_index(3,n3);
  check_index(4,n4);
  check_index(5,n5);

  int itmp = ((n1-1)*index_length[1] + (n2-1));
  itmp = itmp*index_length[2] + (n3-1);
  itmp = itmp*index_length[3] + (n4-1);
  itmp = itmp*index_length[4] + (n5-1);

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// 6-index
int IntArray::getidx(const int n1,
                     const int n2,
                     const int n3,
                     const int n4,
                     const int n5,
                     const int n6) const
{
  assert_eq(num_indeces,6);
  check_index(1,n1);
  check_index(2,n2);
  check_index(3,n3);
  check_index(4,n4);
  check_index(5,n5);
  check_index(6,n6);

  int itmp = ((n1-1)*index_length[1] + (n2-1));
  itmp = itmp*index_length[2] + (n3-1);
  itmp = itmp*index_length[3] + (n4-1);
  itmp = itmp*index_length[4] + (n5-1);
  itmp = itmp*index_length[5] + (n6-1);

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Check index
void IntArray::check_index(const int index_number,
                           const int index) const
{
  assert_ge(index,1);
  assert_le(index,index_length[index_number-1]);
}
// -------------------------------------------------------------------------- //

// *********************************************************
#endif
// *********************************************************

// --------------------------------------------------------------
// class DblArray
// --------------------------------------------------------------

// -------------------------------------------------------------------------- //
// Constructor 1-index
DblArray::DblArray(const int in_index_length1)
{
  assert_ge(in_index_length1,1);

  num_indeces = 1;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;

  compute_total_length();
  int tmp = in_index_length1;
  assert_eq(total_length,tmp);
  vec = new double[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Constructor 2-index
DblArray::DblArray(const int in_index_length1,
                   const int in_index_length2)
{
  assert_ge(in_index_length1,1);
  assert_ge(in_index_length2,1);

  num_indeces = 2;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;
  index_length[1] = in_index_length2;

  compute_total_length();
  int tmp = in_index_length1*in_index_length2;
  assert_eq(total_length,tmp);
  vec = new double[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Constructor 3-index
DblArray::DblArray(const int in_index_length1,
                   const int in_index_length2,
                   const int in_index_length3)
{
  assert_ge(in_index_length1,1);
  assert_ge(in_index_length2,1);
  assert_ge(in_index_length3,1);

  num_indeces = 3;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;
  index_length[1] = in_index_length2;
  index_length[2] = in_index_length3;

  compute_total_length();
  int tmp = in_index_length1*in_index_length2*in_index_length3;
  assert_eq(total_length,tmp);
  vec = new double[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Constructor 4-index
DblArray::DblArray(const int in_index_length1,
                   const int in_index_length2,
                   const int in_index_length3,
                   const int in_index_length4)
{
  assert_ge(in_index_length1,1);
  assert_ge(in_index_length2,1);
  assert_ge(in_index_length3,1);
  assert_ge(in_index_length4,1);

  num_indeces = 4;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;
  index_length[1] = in_index_length2;
  index_length[2] = in_index_length3;
  index_length[3] = in_index_length4;

  compute_total_length();
  int tmp = in_index_length1*in_index_length2*in_index_length3\
       *in_index_length4;
  assert_eq(total_length,tmp);
  vec = new double[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Constructor 5-index
DblArray::DblArray(const int in_index_length1,
                   const int in_index_length2,
                   const int in_index_length3,
                   const int in_index_length4,
                   const int in_index_length5)
{
  assert_ge(in_index_length1,1);
  assert_ge(in_index_length2,1);
  assert_ge(in_index_length3,1);
  assert_ge(in_index_length4,1);
  assert_ge(in_index_length5,1);

  num_indeces = 5;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;
  index_length[1] = in_index_length2;
  index_length[2] = in_index_length3;
  index_length[3] = in_index_length4;
  index_length[4] = in_index_length5;

  compute_total_length();
  int tmp = in_index_length1*in_index_length2*in_index_length3\
       *in_index_length4*in_index_length5;
  assert_eq(total_length,tmp);
  vec = new double[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Constructor 6-index
DblArray::DblArray(const int in_index_length1,
                   const int in_index_length2,
                   const int in_index_length3,
                   const int in_index_length4,
                   const int in_index_length5,
                   const int in_index_length6)
{
  assert_ge(in_index_length1,1);
  assert_ge(in_index_length2,1);
  assert_ge(in_index_length3,1);
  assert_ge(in_index_length4,1);
  assert_ge(in_index_length5,1);
  assert_ge(in_index_length6,1);

  num_indeces = 6;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;
  index_length[1] = in_index_length2;
  index_length[2] = in_index_length3;
  index_length[3] = in_index_length4;
  index_length[4] = in_index_length5;
  index_length[5] = in_index_length6;

  compute_total_length();
  int tmp = in_index_length1*in_index_length2*in_index_length3\
       *in_index_length4*in_index_length5*in_index_length6;
  assert_eq(total_length,tmp);
  vec = new double[tmp];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Helper routine to compute total_length value
void DblArray::compute_total_length()
{
  assert_ge(num_indeces,1);
  total_length = 1;
  for (int i=0; i<num_indeces; i++)
    {
      total_length = total_length*index_length[i];
    }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Copy constructor
DblArray::DblArray(const DblArray& anotherDblArray)
{
  num_indeces = anotherDblArray.num_indeces;
  total_length = anotherDblArray.total_length;

  index_length = new int[num_indeces];
  vec = new double[total_length];

  for (int i=0; i<num_indeces; i++)
    { index_length[i] = anotherDblArray.index_length[i]; }

  for (int i=0; i<total_length; i++)
    { vec[i] = anotherDblArray.vec[i]; }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Destructor
DblArray::~DblArray()
{
  delete[] vec;
  delete[] index_length;
  num_indeces = 0;
  total_length = 0;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Number of indeces
int DblArray::get_num_ind() const
{
  return num_indeces;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Individual index length information
int DblArray::get_ind_length(const int n) const
{
  assert_ge(n,1);
  assert_le(n,num_indeces);
  return index_length[n-1];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Total length information
int DblArray::get_total_length() const
{
  return total_length;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void DblArray::assert_eq_size(const DblArray& anotherDblArray) const
{
  assert_eq(num_indeces, anotherDblArray.get_num_ind());
  for (int i=1; i<=num_indeces; i++)
    { assert_eq(get_ind_length(i), anotherDblArray.get_ind_length(i)); }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Check index
void DblArray::check_index(const int index_number,
                           const int index) const
{
  assert_ge(index,1);
  assert_le(index,index_length[index_number-1]);
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Resize 1-index
void DblArray::resize(const int in_index_length1)
{
  assert_eq(num_indeces,1);

  delete[] index_length;
  delete[] vec;

  assert_ge(in_index_length1,1);

  num_indeces = 1;
  index_length = new int[num_indeces];
  index_length[0] = in_index_length1;

  compute_total_length();
  vec = new double[in_index_length1];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Check for solution blow-up
void DblArray::integrity_check() const
{
  double maxval;
  for (int i=0; i<total_length; i++)
    {
      maxval = fabs(vec[i]);
      if (maxval > 1.0e111)
        {
          printf("\n");
          printf(" ERROR: DblArray contains a very large number.\n\n");
          exit(1);
        }
    }
}
// -------------------------------------------------------------------------- //

// *********************************************************
#ifdef CHECK_BOUNDS
// *********************************************************

// ----------------------------
// Direct get and set functions
// ----------------------------

// -------------------------------------------------------------------------- //
const double& DblArray::vget(const int k) const
{
  assert_ge(k,0);
  assert_lt(k,total_length);
  return vec[k];
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void DblArray::vset(const int k, const double value)
{
  assert_ge(k,0);
  assert_lt(k,total_length);
  vec[k] = value;
}
// -------------------------------------------------------------------------- //

// ----------------------------
// Direct get and set functions - 1 indexed
// ----------------------------
const double& DblArray::dget(const int k) const
{
  assert_ge(k,1);
  assert_le(k,total_length);
  return vec[k-1];
}

void DblArray::dset(const int k, const double value)
{
  assert_ge(k,1);
  assert_le(k,total_length);
  vec[k-1] = value;
}

// -------------------
// Get index functions
// -------------------

// -------------------------------------------------------------------------- //
// 1-index
int DblArray::getidx(const int n1) const
{
  assert_eq(num_indeces,1);
  check_index(1,n1);

  int itmp = n1-1;

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// 2-index
int DblArray::getidx(const int n1,
                     const int n2) const
{
  assert_eq(num_indeces,2);
  check_index(1,n1);
  check_index(2,n2);

  int itmp = ((n1-1)*index_length[1] + (n2-1));

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// 3-index
int DblArray::getidx(const int n1,
                     const int n2,
                     const int n3) const
{
  assert_eq(num_indeces,3);
  check_index(1,n1);
  check_index(2,n2);
  check_index(3,n3);

  int itmp = ((n1-1)*index_length[1] + (n2-1));
  itmp = itmp*index_length[2] + (n3-1);

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// 4-index
int DblArray::getidx(const int n1,
                     const int n2,
                     const int n3,
                     const int n4) const
{
  assert_eq(num_indeces,4);
  check_index(1,n1);
  check_index(2,n2);
  check_index(3,n3);
  check_index(4,n4);

  int itmp = ((n1-1)*index_length[1] + (n2-1));
  itmp = itmp*index_length[2] + (n3-1);
  itmp = itmp*index_length[3] + (n4-1);

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// 5-index
int DblArray::getidx(const int n1,
                     const int n2,
                     const int n3,
                     const int n4,
                     const int n5) const
{
  assert_eq(num_indeces,5);
  check_index(1,n1);
  check_index(2,n2);
  check_index(3,n3);
  check_index(4,n4);
  check_index(5,n5);

  int itmp = ((n1-1)*index_length[1] + (n2-1));
  itmp = itmp*index_length[2] + (n3-1);
  itmp = itmp*index_length[3] + (n4-1);
  itmp = itmp*index_length[4] + (n5-1);

  return itmp;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// 6-index
int DblArray::getidx(const int n1,
                     const int n2,
                     const int n3,
                     const int n4,
                     const int n5,
                     const int n6) const
{
  assert_eq(num_indeces,6);
  check_index(1,n1);
  check_index(2,n2);
  check_index(3,n3);
  check_index(4,n4);
  check_index(5,n5);
  check_index(6,n6);

  int itmp = ((n1-1)*index_length[1] + (n2-1));
  itmp = itmp*index_length[2] + (n3-1);
  itmp = itmp*index_length[3] + (n4-1);
  itmp = itmp*index_length[4] + (n5-1);
  itmp = itmp*index_length[5] + (n6-1);

  return itmp;
}
// -------------------------------------------------------------------------- //

// *********************************************************
#endif
// *********************************************************

// -------------------------------------------------------------------------- //
// Math functions
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// this = this + a
void DblArray::add(double a)
{
  for (int i=0; i<total_length; i++)
    { vec[i]+=a; }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// this = this + a
void DblArray::add(const DblArray& a)
{
  assert_eq(total_length, a.get_total_length());
  for (int i=0; i<total_length; i++)
    { vec[i]+=a.vget(i); }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// this = a + b
void DblArray::add(const DblArray& a, const DblArray& b)
{
  assert_eq(total_length, a.get_total_length());
  assert_eq(total_length, b.get_total_length());
  for (int i=0; i<total_length; i++)
    { vec[i] = a.vget(i) + b.vget(i); }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// this = this - a
void DblArray::subtract(double a)
{
  add(-1.0*a);
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// if same total length subtract element-wise
void DblArray::subtract(const DblArray& a)
{
  assert_eq(total_length, a.get_total_length());
  for (int i=0; i<total_length; i++)
    { vec[i] -= a.vget(i); }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// this = a - b
void DblArray::subtract(const DblArray& a, const DblArray& b)
{
  assert_eq(total_length, a.get_total_length());
  assert_eq(total_length, b.get_total_length());
  for (int i=0; i<total_length; i++)
    { vec[i] = a.vget(i) - b.vget(i); }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// this = a*this
void DblArray::multiply(const double a)
{
  for (int i=0; i<total_length; i++)
    { vec[i]*=a; }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// this = (a*this) element-wise
void DblArray::multiply(const DblArray& a)
{
  assert_eq(total_length, a.get_total_length());

  // multiply element-wise
  for (int i=0; i<total_length; i++)
    { vec[i] *= a.vget(i); }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// this = a*b element-wise if same total length
void DblArray::multiply(const DblArray& a, const DblArray& b)
{
  assert_eq(a.get_total_length(), b.get_total_length());

  // multiply elementwise
  assert_eq(total_length, a.get_total_length());
  for (int i=0; i<total_length; i++)
    { vec[i] = a.vget(i)*b.vget(i); }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// b = this*a
void DblArray::multiply(const DblArray& a, DblArray& b) const
{
  b.multiply(*this, a);
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// this = 1/a*this
void DblArray::divide(const double a)
{
  multiply(1.0/a);
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// this = this/a element wise if same total length
void DblArray::divide(const DblArray& a)
{
  assert_eq(total_length, a.get_total_length());
  for (int i=0; i<total_length; i++)
    { vec[i]/=a.vget(i); }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// return inner product <this, a>
double DblArray::dot(const DblArray& a) const
{
  assert_eq(total_length, a.get_total_length());
  double dot_product = 0.0;
  for (int i=0; i<total_length; i++)
    { dot_product += vec[i]*a.vget(i); }
  return dot_product;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
double DblArray::norm() const
{
  return sqrt(dot(*this));
}
// -------------------------------------------------------------------------- //
