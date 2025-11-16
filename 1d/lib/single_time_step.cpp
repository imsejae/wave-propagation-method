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
                                  const DblArray& x,
                                  DblArray& qsoln)
{
  /*
  const double dt       = params1D.get_dt();
  const double dx       = params1D.get_dx();
  const double dvx      = params1D.get_dvx();
  const double dtodx    = params1D.get_dtodx();
  const double Knudsen  = params1D.get_Knudsen();
  const int num_negative_velocities = params1D.get_num_negative_velocities();

  // --------------------
  //  microscopic update
  // --------------------
  update_micro(params1D,
               dt,
               dx,
               dvx,
               Knudsen,
               num_negative_velocities,
               time,
               x,
               vx,
               qmacro,
               helper.iminus1,
               helper.izero,
               helper.iplus1,
               helper.Zmicro,
               gmicro);

  // --------------------------------------------------
  //  compute heat flux from microscopic distribution
  // --------------------------------------------------
  compute_heat_flux(dvx,
                    vx,
                    gmicro,
                    helper.heatflux);

  // --------------------
  //  macroscopic update
  // --------------------
  if (params1D.get_additional_source()==1)
    {
      add_source_macro(Knudsen,
                       0.5*dtodx,
                       qmacro,
                       time,
                       x,
                       0.5*dt);
    }

  update_macro(params1D,
               Knudsen,
               dtodx,
               helper.iminus1,
               helper.izero,
               helper.iplus1,
               helper.heatflux,
               qmacro);

  if (params1D.get_additional_source()==1)
    {
      add_source_macro(Knudsen,
                       0.5*dtodx,
                       qmacro,
                       time,
                       x,
                       0.5*dt);
    }
    */
}
// -------------------------------------------------------------------------- //