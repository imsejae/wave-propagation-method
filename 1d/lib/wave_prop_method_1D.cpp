#include <stdlib.h>
#include <stdio.h>
#include "debug.h"
#include "assert.h"
#include "setup.h"
#include "Params1D.h"
#include "DogArrays.h"
#include "waveprop1D.h"
#include "HelperArrays1D.h"
#include <cmath>
 
 // -------------------------------------------------------------------------- //
int wave_prop_method_1D(int argc, char* argv[])
{
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

  // create mesh
  DblArray x(Nx);
  waveprop1D::create_mesh(x,params1D);

  // ------------------
  // initial conditions
  // ------------------

  // solution array (list of conserved variables)
  DblArray qsoln(Nx,Neqn);

  // initialize mass, momentum, energy, and micro distribution
  waveprop1D::set_initial(x,qsoln);

  // output initial conditions
  waveprop1D::output(outputdir,
                     0,
                     0.0,
                     qsoln);

  // time step
  double time = 0.0;
  double time_elapsed_per_frame = params1D.get_final_time()/params1D.get_numframes();
  int max_time_steps_per_frame = params1D.get_max_number_of_time_steps()/params1D.get_numframes();

  for (int frame=1; frame<=params1D.get_numframes(); frame++)
    {
      int step = 0; // number of steps per frame
      while (time<=(time_elapsed_per_frame*frame) && step<=(max_time_steps_per_frame))
        {
          /*waveprop1D::single_time_step(params1D,
                                       h1D,
                                       time,
                                       x,
                                       qsoln);*/
 
          double dt = (time_elapsed_per_frame)/10;
          double cfl = 0.95;
          time += dt; //params1D.get_dt();
          step++;
          if (params1D.get_verbosity()==1)
            {
              printf("WAVE-PROP-1D:  Step %5d"
                     "   CFL =%6.3f"
                     "   dt =%11.3e"
                     "   t =%11.3e\n",
                     step,cfl,dt,time);
            }
        }

      waveprop1D::output(outputdir,
                         frame,
                         time,
                         qsoln);

      printf("WAVE-PROP-1D: Frame %3d: at time t =%12.5e\n\n", frame, time);
    }

  // done
  return 0;
}
// -------------------------------------------------------------------------- //