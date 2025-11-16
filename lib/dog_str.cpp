#include <stdio.h>
#include <cstring> // for strcmp
#include <string>
#include "assert.h"
#include "dog_str.h"
#include "DogArrays.h"
#include "debug.h"

// C-style string operations.
//
// See also: dog_io.cpp

//////////////////////////////////////////////////////////////////////////////
// Test if two strings are equal.  This is simply a wrapper for "strcmp" found
// in <cstring>.
bool dog_str::str_eq(const char* str1,
                     const char* str2)
{
  // for case-insensitive matching change this to strcasecmp
  return !strcmp(str1,str2);
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// convert comma-separated list to array of integers.
//
// user is responsible to
// delete [] int_array;
//
int dog_str::new_array_from_str(const char* str_in,
                                int* &int_array,
                                int first_idx,
                                char field_sep)
{
  assert(first_idx==0 || first_idx==1);

  int_array = 0;
  char *str = (char*)str_in;
  char *ptr = str;
  if(ptr==0) return -1;
  if(*ptr==0) return 0;

  // allocate int_array
  int number_of_numbers=0;
    {
      // count number of commas in string
      int number_of_commas=0;
      for(char *ptr=str; *ptr; ptr++) if(*ptr == field_sep) number_of_commas++;
      number_of_numbers = number_of_commas+1;
      int array_size = first_idx+number_of_numbers;
      int_array=new int[array_size];
      for(int i=0;i<array_size;i++) int_array[i]=0;
    }

  // populate int_array with numbers from list
  ptr=str;
  int idx=first_idx;
  while(*ptr)
    {
      int val;
      int successful_match = sscanf(ptr,"%d",&val);
      if(!successful_match)
        {
          printf("problem: could not match %s as integer\n",ptr);
          delete [] int_array; int_array=0; return -1;
        }
      else
        {
          int_array[idx++]=val;
        }
      // advance ptr past next comma
      while(*ptr && *ptr++ != field_sep);
    }
  assert(idx==(first_idx+number_of_numbers));
  return number_of_numbers;
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// field_sep is typically ',' or '\n'
bool dog_str::str_into_tensor(const char* str,
                              IntArray& t,
                              char field_sep)
{
  int idx=0;
  bool ret=true;
  char* ptr = (char*)str;
  while(*ptr && idx < t.get_total_length())
    {
      int val;
      int successful_match = sscanf(ptr,"%d",&val);
      if(!successful_match)
        {
          Wprintf("could not match %s as integer\n",ptr);
          ret=false;
        }
      else
        {
          t.vset(idx++, val);
        }

      // advance ptr past next comma
      while(*ptr && *ptr++ != field_sep);
    }
  return ret;
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// field_sep is typically ',' or '\n'
bool dog_str::str_into_tensor(const char* str,
                              DblArray& t,
                              char field_sep)
{
  int idx=0;
  bool ret=true;
  char* ptr = (char*)str;
  while(*ptr && idx < t.get_total_length())
    {
      double val;
      int successful_match = sscanf(ptr,"%lf",&val);
      if(!successful_match)
        {
          Wprintf("could not match %s as double\n",ptr);
          ret=false;
        }
      else
        {
          t.vset(idx++, val);
        }
      // advance ptr past next comma
      while(*ptr && *ptr++ != field_sep);
    }
  return ret;
}
//////////////////////////////////////////////////////////////////////////////
