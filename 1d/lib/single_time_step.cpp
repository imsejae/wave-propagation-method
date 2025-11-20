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

  // loop over all interfaces to apply wave limiters
  if (params1D.get_order()>1)
    {
      if (params1D.get_use_limiter())
        {
          DblArray wave_now(Neqn);
          DblArray wave_other(Neqn);
          double theta,phival;
          for (int i=1; i<=(Nx+1); i++)
            {
              double dotwave,dotnumer;
              int im1 = helper.im1->get(i);
              int ip1 = helper.ip1->get(i);

              for (int m=1; m<=Neqn; m++)
                {
                  double s_now = helper.s->get(i,m);

                  for (int n=1; n<=Neqn; n++)
                    { wave_now.fetch(n) = helper.wave->get(i,n,m); }

                  dotwave = pow(wave_now.get(1),2);
                  for (int n=2; n<=Neqn; n++)
                    { dotwave += pow(wave_now.get(n),2); }

                  if (s_now>=0.0)
                    {
                      for (int n=1; n<=Neqn; n++)
                        { wave_other.fetch(n) = helper.wave->get(im1,n,m); }
                    }
                  else
                    {
                      for (int n=1; n<=Neqn; n++)
                        { wave_other.fetch(n) = helper.wave->get(ip1,n,m); }
                    }

                  dotnumer = wave_now.get(1)*wave_other.get(1);
                  for (int n=2; n<=Neqn; n++)
                    { dotnumer += wave_now.get(n)*wave_other.get(n); }

                  if (fabs(dotwave)>1.0e-12)
                    { theta = dotnumer/dotwave; }
                  else
                    { theta = 0.0; }
                  phival = limiter_function(theta);

                  // limit wave
                  for (int n=1; n<=Neqn; n++)
                    { helper.wave->fetch(i,n,m) *= phival; }
                }
            }
        }

      // compute high-resolution fluxes
      for (int i=1; i<=(Nx+1); i++)
        for (int n=1; n<=Neqn; n++)
          { 
            double tmp = 0.0;
            for (int m=1; m<=Neqn; m++)
              { 
                double asp = fabs(helper.s->get(i,m));
                tmp += 0.5*asp*(1.0-dtodx*asp)*helper.wave->get(i,n,m); 
              }
            helper.Ftilde->fetch(i,n) = tmp;
          }
    }

  // loop over cells to update solution
  for (int i=1; i<=Nx; i++)
    for (int m=1; m<=Neqn; m++)
      {
        // first order update
        qsoln.fetch(i,m) += -dtodx*( helper.apdq->fetch(i,m) \
                                   + helper.amdq->fetch(helper.ip1->get(i),m) );
      }
  if (params1D.get_order()>1)
    {
      for (int i=1; i<=Nx; i++)
        for (int m=1; m<=Neqn; m++)
          {
            // high-resolution corrections
            qsoln.fetch(i,m) += dtodx*( helper.Ftilde->fetch(i,m) \
                                      - helper.Ftilde->fetch(helper.ip1->get(i),m) );
          }
    }
}
// -------------------------------------------------------------------------- //