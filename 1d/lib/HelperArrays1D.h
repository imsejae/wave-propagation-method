#ifndef _HELPERARRAYS1D_H_
#define _HELPERARRAYS1D_H_

class IntArray;
class DblArray;

class HelperArrays1D
{
  public:
    // Constructor
    HelperArrays1D();

    // Destructor
    ~HelperArrays1D();

    // Copy-constructor
    HelperArrays1D(const HelperArrays1D& anotherHelperArrays1D);

    // Initializer function
    void init(const int order_in, const int Nx_in, const int Neqn_in);

    // return smax
    const double get_smax() const {return smax; };

    // set smax
    void set_smax(const double smax_in) { smax = smax_in; };

  private:
    bool is_initialized;
    int order;
    int Nx;
    int Neqn;
    double smax;

  public:
    DblArray* im1;
    DblArray* iz0;
    DblArray* ip1;
    DblArray* s;
    DblArray* wave;
    DblArray* apdq;
    DblArray* amdq;
    DblArray* Ftilde;
    DblArray* dotwave;
};

#endif