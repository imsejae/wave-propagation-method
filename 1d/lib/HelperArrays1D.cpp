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
  smax            = 0.0;
  
  s               = NULL;
  alpha           = NULL;
  wave            = NULL;
  apdq            = NULL;
  amdq            = NULL;
  Ftilde          = NULL;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Destructor
HelperArrays1D::~HelperArrays1D()
{ 
  order           = -1;
  Nx              = -1;
  Neqn            = -1;
  delete s;
  delete alpha;
  delete wave;
  delete apdq;
  delete amdq;
  delete Ftilde;
  s               = NULL;
  alpha           = NULL;
  wave            = NULL;
  apdq            = NULL;
  amdq            = NULL;
  Ftilde          = NULL;

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

  s      = new DblArray(Nx+1,Neqn);
  alpha  = new DblArray(Neqn);
  wave   = new DblArray(Nx+1,Neqn,Neqn);
  apdq   = new DblArray(Nx+1,Neqn);
  amdq   = new DblArray(Nx+1,Neqn);
  Ftilde = new DblArray(Nx+1,Neqn);

  is_initialized = true;
}
// -------------------------------------------------------------------------- //