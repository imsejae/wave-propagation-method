#include <stdlib.h>
#include <stdio.h>
#include "debug.h"
#include "assert.h"
#include "setup.h"
#include "Params1D.h"
#include "DogArrays.h"
#include "waveprop1D.h"
#include "HelperArrays1D.h"
#include "dog_math.h"
#include "dog_str.h"
#include <cmath>
 
 // -------------------------------------------------------------------------- //
int wave_prop_method_1D(int argc, char* argv[])
{
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ------------------
  // setup
  // ------------------

  // print a welcome message
  setup::PrintWelcome();

  // parse input arguments (currently pulls a different output directory)
  char* outputdir = setup::ParseArguments(argc,argv);

  // create output directory
  setup::RunScript(outputdir);

  // create parameters (and read them from "parameters.ini")
  Params1D params1D;
  params1D.init(outputdir);
  const int  order = params1D.get_order();
  const int     Nx = params1D.get_Nx();
  const int   Neqn = params1D.get_Neqn();

  // create helper arrays
  HelperArrays1D h1D;
  h1D.init(order,Nx,Neqn);

  if (dog_str::str_eq(params1D.get_left_bc(),"extrapolation"))
    { h1D.im1->fetch(1) = 1; }
  else if (dog_str::str_eq(params1D.get_left_bc(),"periodic"))
    { h1D.im1->fetch(1) = Nx; }

  if (dog_str::str_eq(params1D.get_right_bc(),"extrapolation"))
    { h1D.iz0->fetch(Nx+1) = Nx; h1D.ip1->fetch(Nx+1) = Nx; }
  else if (dog_str::str_eq(params1D.get_right_bc(),"periodic"))
    { h1D.iz0->fetch(Nx+1) = 1; h1D.ip1->fetch(Nx+1) = 2; }

  // create mesh
  DblArray x(Nx);
  waveprop1D::create_mesh(x,params1D);
  const double dx = params1D.get_dx();
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ------------------
  // initial conditions
  // ------------------

  // solution array (list of conserved variables)
  DblArray qsoln(Nx,Neqn);
  DblArray qtmp(Nx,Neqn);

  // initialize solution
  waveprop1D::set_initial(x,qsoln);
  for (int i=1; i<=Nx; i++)
    for (int m=1; m<=Neqn; m++)
       { qtmp.fetch(i,m) = qsoln.get(i,m); }

  // output initial conditions
  waveprop1D::output(outputdir,
                     0,
                     0.0,
                     qsoln);

  // take a "fake time step" in order to estimate maximum wave speed
  waveprop1D::single_time_step(params1D,
                               h1D,
                               0.0,  // time
                               0.0,  // dt
                               x,
                               qtmp);
  double smax = dog_math::Max(h1D.get_smax(),1.0e-12);
  for (int i=1; i<=Nx; i++)
    for (int m=1; m<=Neqn; m++)
       { qtmp.fetch(i,m) = qsoln.get(i,m); }
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ------------------
  // time step
  // ------------------
  const double time_elapsed_per_frame = params1D.get_final_time()/params1D.get_numframes();
  const int max_time_steps_per_frame = params1D.get_max_number_of_time_steps()/params1D.get_numframes();
  const double cfl     = params1D.get_cfl();
  const double cfl_max = cfl*(1.01);

  // initial time
  double time = 0.0;

  // compute intial time step
  double dt = dog_math::Min(dx*cfl/smax,time_elapsed_per_frame);

  // loop over each frame
  for (int frame=1; frame<=params1D.get_numframes(); frame++)
    {
      int step = 0; // number of steps per frame
      double end_time = time_elapsed_per_frame*frame;
      
      // keep taking time steps until at the end of the frame
      bool done = false;
      while (!done)
        {
          // keep trying until dt satifies smax*dt/dx <= cfl_max
          double cfl_actual;
          bool accept = false;
          while (!accept)
            {
              // take time step
              waveprop1D::single_time_step(params1D,
                                           h1D,
                                           time,
                                           dt,
                                           x,
                                           qtmp);
              smax = dog_math::Max(h1D.get_smax(),1.0e-12);
              cfl_actual = smax*dt/dx;

              // check if we can accept this time step
              if (cfl_actual <= cfl_max)
                { 
                  accept = true;
                  time += dt;
                  step++;

                  // update solution
                  for (int i=1; i<=Nx; i++)
                    for (int m=1; m<=Neqn; m++)
                      { qsoln.fetch(i,m) = qtmp.get(i,m); }
                }
              else
                {
                  if (params1D.get_verbosity()==1)
                    { printf("  ... resetting time step and trying again ...\n"); }

                  for (int i=1; i<=Nx; i++)
                    for (int m=1; m<=Neqn; m++)
                      { qtmp.fetch(i,m) = qsoln.get(i,m); }
                }

              // report time step details
              if (params1D.get_verbosity()==1)
                {
                  printf("WAVE-PROP-1D:  Step %5d"
                        "   CFL =%6.3f"
                        "   dt =%11.3e"
                        "   t =%11.3e\n",
                        step,cfl_actual,dt,time);
                }

              // compute new time step based on new smax
              double dt_old = dt;
              dt = dog_math::Min(dx*cfl/smax, end_time-time);
              if (fabs(dt)<1.0e-14) { dt = dt_old; }
            }

          if  (step==max_time_steps_per_frame)
            { eprintf("\n  error: maximum number of time steps exceeded.\n"); }

          if (fabs(time-end_time)<1.0e-14)
           { done = true; }
        }

      waveprop1D::output(outputdir,
                         frame,
                         time,
                         qsoln);

      printf("WAVE-PROP-1D: Frame %3d: at time t =%12.5e\n\n", frame, time);
    }
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // done
  return 0;
}
// -------------------------------------------------------------------------- //