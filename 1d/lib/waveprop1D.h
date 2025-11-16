#ifndef _MICMAC_1D_H_
#define _MICMAC_1D_H_

class Params1D;
class IntArray;
class DblArray;
class HelperArrays1D;

namespace waveprop1D
{
  void create_mesh(DblArray& x,
                   Params1D& params1D);

  void set_initial(const DblArray& x,
                   DblArray& qsoln);

  void output(const char* outputdir,
              const int nframe,
              const double time,
              const DblArray& qsoln);

  void single_time_step(const Params1D& params1D,
                        HelperArrays1D& helper,
                        const double time,
                        const DblArray& x,
                        DblArray& qsoln);
}
#endif