#include "waveprop1D.h"
#include "HelperArrays1D.h"
#include "DogArrays.h"
#include "Params1D.h"
#include "dog_math.h"
#include "constants.h"
#include "assert.h"
#include "dog_str.h"
#include <string>
#include <cmath>

// -------------------------------------------------------------------------- //
void waveprop1D::create_mesh(DblArray& x,
                             Params1D& params1D)
{
  const int       Nx = params1D.get_Nx();
  const double    dx = params1D.get_dx();
  const double  xlow = params1D.get_xlow();

  for (int i=1; i<=Nx; i++)
    { x.fetch(i) = xlow + (double(i)-0.5)*dx; }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void waveprop1D::output(const char* outputdir,
                        const int nframe,
                        const double time,
                        const DblArray& qsoln)
{
  assert_ge(nframe, 0);
  assert_le(nframe, 9999);
  char frame_num[5];
  snprintf(frame_num, 5, "%04d", nframe);
  std::string frame_filename = std::string(outputdir) + "/" + "soln" \
                             + frame_num + ".dat";

  FILE* file = fopen(frame_filename.c_str(),"w");

  fprintf(file,"%24.16e\n",time);
  for (int i2=1; i2<=qsoln.get_ind_length(2); i2++)
    for (int i1=1; i1<=qsoln.get_ind_length(1); i1++)
      { 
        const double qtmp = qsoln.get(i1,i2);
        fprintf(file,"%24.16e\n", qtmp ); 
      }

  fclose(file);
}
// -------------------------------------------------------------------------- //