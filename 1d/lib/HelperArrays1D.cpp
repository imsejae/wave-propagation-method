#include "HelperArrays1D.h"
#include "DogArrays.h"
#include "debug.h"
#include "assert.h"
#include <stdlib.h>
#include <cmath>

// -------------------------------------------------------------------------- //
// Constructor
HelperArrays1D::HelperArrays1D()
{
  is_initialized  = false;
  order           = -1;
  Nx              = -1;
  Neqn            = -1;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Destructor
HelperArrays1D::~HelperArrays1D()
{ 
  order           = -1;
  Nx              = -1;
  Neqn            = -1;

  is_initialized  = false;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Copy constructor
HelperArrays1D::HelperArrays1D(const HelperArrays1D& anotherHelperArrays1D)
{
  eprintf("\n  ERROR: HelperArrays1D copy constructor has been disabled.\n");
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void HelperArrays1D::init(const int order_in, const int Nx_in, const int Neqn_in)
{
  if(is_initialized == true)
    { return; }

  order = order_in;
  Nx    = Nx_in;
  Neqn  = Neqn_in;

  is_initialized = true;
}
// -------------------------------------------------------------------------- //