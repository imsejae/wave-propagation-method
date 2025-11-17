 #include "waveprop1D.h"
 #include "Params1D.h"
 #include "HelperArrays1D.h"
 #include "DogArrays.h"
 #include <cmath>
 #include <stdio.h>
 #include "assert.h"
 #include "debug.h"
 #include "constants.h"
 #include "dog_str.h"
 #include "Params1D.h"

// -------------------------------------------------------------------------- //
void waveprop1D::single_time_step(const Params1D& params1D,
                                  HelperArrays1D& helper,
                                  const double time,
                                  const double dt,
                                  const DblArray& x,
                                  DblArray& qsoln)
{
  //const double dx       = params1D.get_dx();
  //const double dtodx    = dt/dx;

}
// -------------------------------------------------------------------------- //