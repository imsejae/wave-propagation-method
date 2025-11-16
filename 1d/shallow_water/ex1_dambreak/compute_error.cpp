#include "micmac1D.h"
#include "DogArrays.h"
#include "constants.h"
#include <cmath>

// -------------------------------------------------------------------------- //
void micmac1D::compute_error(const char* outputdir,
                             const double time,
                             const double Knudsen,
                             const double dx,
                             const double dvx,
                             const DblArray& x,
                             const DblArray& vx,
                             const DblArray& qmacro,
                             const DblArray& gmicro)
{
   // if an exact solution is known, you can evaluate it here and then compute
   // an appropriate error
}
// -------------------------------------------------------------------------- //