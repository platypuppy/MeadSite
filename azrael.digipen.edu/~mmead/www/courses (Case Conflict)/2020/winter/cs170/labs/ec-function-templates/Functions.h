//---------------------------------------------------------------------------
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//---------------------------------------------------------------------------

// This *must* be put here, otherwise, it will be in the CS170 namespace
// and all kinds of bad things are going to happen.
#include <iostream>

namespace CS170
{
  template <typename T> void swap(T &left, T &right);
  
  /* 
   *  Other template function declarations for count, remove, replace, etc.
   *  go here. Make sure all of your declarations are sorted in alphabetical
   *  order. This includes putting the swap function above in the proper
   *  position.
   *
   */ 
  
  #include "Functions.cpp"
}

#endif
//---------------------------------------------------------------------------
