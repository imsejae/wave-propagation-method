#include "waveprop1D.h"
#include "Params1D.h"
#include "HelperArrays1D.h"
#include "DogArrays.h"
#include "dog_math.h"
#include <cmath>
#include <stdio.h>
#include "assert.h"
#include "debug.h"
#include "constants.h"
#include "dog_str.h"
#include "Params1D.h"
#include "AppSolver.h"

// -------------------------------------------------------------------------- //
void waveprop1D::single_time_step(const Params1D& params1D,
                                  HelperArrays1D& helper,
                                  const double time,
                                  const double dt,
                                  const DblArray& x,
                                  DblArray& qsoln)
{
  const double dx    = params1D.get_dx();
  const double dtodx = dt/dx;
  const int Nx       = params1D.get_Nx();
  const int Neqn     = params1D.get_Neqn();
  double smax;  
  helper.set_smax(-100.0);

  // some local arrays
  DblArray QL(Neqn);
  DblArray QR(Neqn);
  DblArray s(Neqn);
  DblArray wave(Neqn,Neqn);
  DblArray apdq(Neqn);
  DblArray amdq(Neqn);

  // loop over all interfaces
  for (int i=1; i<=(Nx+1); i++)
    {
      // local left and right states
      for (int m=1; m<=Neqn; m++)
        {
          QL.fetch(m) = qsoln.get(helper.im1->get(i),m);
          QR.fetch(m) = qsoln.get(helper.iz0->get(i),m);
        }

      // application-specific wave propagation solver
      smax = AppSolver::Solver(params1D,
                               QL,
                               QR,
                               s,
                               wave,
                               amdq,
                               apdq);
      helper.set_smax(dog_math::Max(helper.get_smax(),smax)); 

      // globalize local results
      for (int m=1; m<=Neqn; m++)
        {
          helper.s->fetch(i,m)    = s.get(m);
          for (int n=1; n<=Neqn; n++)
            { helper.wave->fetch(i,m,n) = wave.get(m,n); }
          helper.amdq->fetch(i,m) = amdq.get(m);
          helper.apdq->fetch(i,m) = apdq.get(m);
        }
    }

  // loop over cells to update solution
  for (int i=1; i<=Nx; i++)
    for (int m=1; m<=Neqn; m++)
      {
        qsoln.fetch(i,m) += -dtodx*( helper.apdq->fetch(i,m) + helper.amdq->fetch(helper.ip1->get(i),m) );
      }
}
// -------------------------------------------------------------------------- //