#include "waveprop1D.h"
#include "DogArrays.h"
#include "constants.h"
#include <cmath>

// -------------------------------------------------------------------------- //
void waveprop1D::set_initial(const DblArray& x,
                             DblArray& qsoln)
{
  const int     Nx = x.get_ind_length(1);
  const int Nxhalf = Nx/2;

  const double   hl = 3.0;
  const double   ul = 0.0;

  const double   hr = 1.0;
  const double   ur = 0.0;

  // left half
  for (int i=1; i<=Nxhalf; i++)
    { 
      qsoln.fetch(i,1) = hl;
      qsoln.fetch(i,2) = hl*ul;
    }

  // right half
  for (int i=(Nxhalf+1); i<=Nx; i++)
    {
      qsoln.fetch(i,1) = hr;
      qsoln.fetch(i,2) = hr*ur;
    }
}
// -------------------------------------------------------------------------- //