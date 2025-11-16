#ifndef _DOGARRAYS_H_
#define _DOGARRAYS_H_

// --------------------------------------------------------------------------
// DogArrays.h defines DoGPack's multidimensional array classes.
//   Array indices increment in odometer order.
// --------------------------------------------------------------------------
//
// By default get and set methods are defined
//   inline without bounds checking.
// To perform bounds checking, compile with -DCHECK_BOUNDS
//   You can put #undef CHECK_BOUNDS immediately prior to
//   #include "DogArrays.h" in files that have already been
//   debugged.)
// --------------------------------------------------------------------------

// #############################################################################
class IntArray
{
  public:
    // Constructors
    IntArray(const int); // 1

    IntArray(const int,
             const int); // 2

    IntArray(const int,
             const int,
             const int); // 3

    IntArray(const int,
             const int,
             const int,
             const int); // 4

    IntArray(const int,
             const int,
             const int,
             const int,
             const int); // 5

    IntArray(const int,
             const int,
             const int,
             const int,
             const int,
             const int); // 6

    // Copy constructor
    IntArray(const IntArray& anotherIntArray);

    // Destructor
    ~IntArray();

    // Number of indeces
    int get_num_ind() const;

    // Individual index length information
    int get_ind_length(const int n) const;

    // Total length information
    int get_total_length() const;

    // Set all to a constant value
    void setall(const int inval)
    {
      for (int i=0; i<total_length; i++)
        { vec[i] = inval; }
    }

    // Resize 1-index
    void resize(const int); // 1

#ifndef CHECK_BOUNDS

    // ----------------------------
    // Direct get and set functions
    // ----------------------------
    const int& vget(const int k) const
    { return vec[k]; };

    void vset(const int k, const int value)
    { vec[k] = value; };

    // --------------------------------------------
    // Direct get and set functions - starting at 1
    // --------------------------------------------
    const int& dget(const int k) const
    { return vec[k-1]; };

    void dset(const int k, const int value)
    { vec[k-1] = value; };

    // -------------------
    // Get index functions
    // -------------------

    // ---------------------------------------------------------------------- //
    // 1-index
    int getidx(const int n1) const
    {
      int itmp = n1-1;
      return itmp;
    };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 2-index
    int getidx(const int n1,
               const int n2) const
    {
      int itmp = ((n1-1)*index_length[1] + (n2-1));
      return itmp;
    };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 3-index
    int getidx(const int n1,
               const int n2,
               const int n3) const
    {
      int itmp = ((n1-1)*index_length[1] + (n2-1));
      itmp = itmp*index_length[2] + (n3-1);
      return itmp;
    };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 4-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4) const
    {
      int itmp = ((n1-1)*index_length[1] + (n2-1));
      itmp = itmp*index_length[2] + (n3-1);
      itmp = itmp*index_length[3] + (n4-1);
      return itmp;
    };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 5-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4,
               const int n5) const
    {
      int itmp = ((n1-1)*index_length[1] + (n2-1));
      itmp = itmp*index_length[2] + (n3-1);
      itmp = itmp*index_length[3] + (n4-1);
      itmp = itmp*index_length[4] + (n5-1);
      return itmp;
    };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 6-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4,
               const int n5,
               const int n6) const
    {
      int itmp = ((n1-1)*index_length[1] + (n2-1));
      itmp = itmp*index_length[2] + (n3-1);
      itmp = itmp*index_length[3] + (n4-1);
      itmp = itmp*index_length[4] + (n5-1);
      itmp = itmp*index_length[5] + (n6-1);
      return itmp;
    };
    // ---------------------------------------------------------------------- //

#else

    // ----------------------------
    // Direct get and set functions
    // ----------------------------
    const int& vget(const int k) const;

    void vset(const int k, const int value);

    // ----------------------------
    // Direct get and set functions - 1 indexed
    // ----------------------------
    const int& dget(const int k) const;

    void dset(const int k, const int value);

    // -------------------
    // Get index functions
    // -------------------

    // 1-index
    int getidx(const int n1) const;

    // 2-index
    int getidx(const int n1,
               const int n2) const;

    // 3-index
    int getidx(const int n1,
               const int n2,
               const int n3) const;

    // 4-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4) const;

    // 5-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4,
               const int n5) const;

    // 6-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4,
               const int n5,
               const int n6) const;

#endif

    // -----------------------------
    // Get, fetch, and set functions
    // -----------------------------

    // ---------------------------------------------------------------------- //
    // 1-index: get, fetch, and set
    const int& get(const int n1) const
    { return vec[getidx(n1)]; };

    int& fetch(const int n1)
    { return vec[getidx(n1)]; };

    void set(const int n1,
             const int inval)
    { vec[getidx(n1)] = inval; };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 2-index: get, fetch, and set
    const int& get(const int n1,
                   const int n2) const
    { return vec[getidx(n1,n2)]; };

    int& fetch(const int n1,
               const int n2)
    {  return vec[getidx(n1,n2)]; };

    void set(const int n1,
             const int n2,
             const int inval)
    { vec[getidx(n1,n2)] = inval; };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 3-index: get, fetch, and set
    const int& get(const int n1,
                   const int n2,
                   const int n3) const
    { return vec[getidx(n1,n2,n3)]; };

    int& fetch(const int n1,
               const int n2,
               const int n3)
    { return vec[getidx(n1,n2,n3)]; };

    void set(const int n1,
             const int n2,
             const int n3,
             const int inval)
    { vec[getidx(n1,n2,n3)] = inval; };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 4-index: get, fetch, and set
    const int& get(const int n1,
                   const int n2,
                   const int n3,
                   const int n4) const
    { return vec[getidx(n1,n2,n3,n4)]; };

    int& fetch(const int n1,
               const int n2,
               const int n3,
               const int n4)
    { return vec[getidx(n1,n2,n3,n4)]; };

    void set(const int n1,
             const int n2,
             const int n3,
             const int n4,
             const int inval)
    { vec[getidx(n1,n2,n3,n4)] = inval; };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 5-index: get, fetch, and set
    const int& get(const int n1,
                   const int n2,
                   const int n3,
                   const int n4,
                   const int n5) const
    { return vec[getidx(n1,n2,n3,n4,n5)]; };

    int& fetch(const int n1,
               const int n2,
               const int n3,
               const int n4,
               const int n5)
    { return vec[getidx(n1,n2,n3,n4,n5)]; };

    void set(const int n1,
             const int n2,
             const int n3,
             const int n4,
             const int n5,
             const int inval)
    { vec[getidx(n1,n2,n3,n4,n5)] = inval; };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 6-index: get, fetch, and set
    const int& get(const int n1,
                   const int n2,
                   const int n3,
                   const int n4,
                   const int n5,
                   const int n6) const
    { return vec[getidx(n1,n2,n3,n4,n5,n6)]; };

    int& fetch(const int n1,
               const int n2,
               const int n3,
               const int n4,
               const int n5,
               const int n6)
    { return vec[getidx(n1,n2,n3,n4,n5,n6)]; };

    void set(const int n1,
             const int n2,
             const int n3,
             const int n4,
             const int n5,
             const int n6,
             const int inval)
    { vec[getidx(n1,n2,n3,n4,n5,n6)] = inval; };
    // ---------------------------------------------------------------------- //

  private:
    int* vec;
    int num_indeces;
    int total_length;
    int* index_length;

    void compute_total_length();

    void check_index(const int,const int) const;
};

// #################################################################################

class DblArray
{
  public:
    // Constructors
    DblArray(const int); // 1

    DblArray(const int,
             const int); // 2

    DblArray(const int,
             const int,
             const int); // 3

    DblArray(const int,
             const int,
             const int,
             const int); // 4

    DblArray(const int,
             const int,
             const int,
             const int,
             const int); // 5

    DblArray(const int,
             const int,
             const int,
             const int,
             const int,
             const int); // 6

    // Copy constructor
    DblArray(const DblArray& anotherDblArray);

    // Destructor
    ~DblArray();

    // Number of indeces
    int get_num_ind() const;

    // Individual index length information
    int get_ind_length(const int n) const;

    // Total length information
    int get_total_length() const;

    // Assert that array is same size as anotherDblArray
    void assert_eq_size(const DblArray& anotherDblArray) const;

    // Set all to a constant value
    void setall(const double inval)
    {
      for (int i=0; i<total_length; i++)
        {  vec[i] = inval; }
    }

    // Resize 1-index
    void resize(const int);

    // Check for solution blow-up
    void integrity_check() const;

    // --------------
    // Math functions
    // --------------

    // this = this + a
    void add(double a);

    // this = this + a
    void add(const DblArray& a);

    // this = a + b
    void add(const DblArray& a,
             const DblArray& b);

    // this = this - a
    void subtract(double a);

    // this = this - a
    void subtract(const DblArray& a);

    // this = a - b
    void subtract(const DblArray& a,
                  const DblArray& b);

    // this = a*this
    void multiply(const double a);

    // this = (a*this) element-wise if same total length
    void multiply(const DblArray& a);

    // this = a*b element-wise if same total length
    void multiply(const DblArray& a,
                  const DblArray& b);

    // b = this*a
    void multiply(const DblArray& a,
                  DblArray& b) const;

    // this = 1/a*this
    void divide(const double a);

    // this = this/a element wise if same total length
    void divide(const DblArray& a);

    // return inner product <this, a>
    double dot(const DblArray& a) const;

    // return 2-norm of this
    double norm() const;

#ifndef CHECK_BOUNDS

    // ----------------------------
    // Direct get and set functions
    // ----------------------------
    const double& vget(const int k) const
    { return vec[k]; };

    void vset(const int k, const double value)
    { vec[k] = value; };

    // ----------------------------
    // Direct get and set functions - 1 indexed
    // ----------------------------
    const double& dget(const int k) const
    { return vec[k-1]; };

    void dset(const int k, const double value)
    { vec[k-1] = value; };

    // -------------------
    // Get index functions
    // -------------------

    // ---------------------------------------------------------------------- //
    // 1-index
    int getidx(const int n1) const
    {
      int itmp = n1-1;
      return itmp;
    };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 2-index
    int getidx(const int n1,
               const int n2) const
    {
      int itmp = ((n1-1)*index_length[1] + (n2-1));
      return itmp;
    };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 3-index
    int getidx(const int n1,
               const int n2,
               const int n3) const
    {
      int itmp = ((n1-1)*index_length[1] + (n2-1));
      itmp = itmp*index_length[2] + (n3-1);
      return itmp;
    };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 4-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4) const
    {
      int itmp = ((n1-1)*index_length[1] + (n2-1));
      itmp = itmp*index_length[2] + (n3-1);
      itmp = itmp*index_length[3] + (n4-1);
      return itmp;
    };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 5-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4,
               const int n5) const
    {
      int itmp = ((n1-1)*index_length[1] + (n2-1));
      itmp = itmp*index_length[2] + (n3-1);
      itmp = itmp*index_length[3] + (n4-1);
      itmp = itmp*index_length[4] + (n5-1);
      return itmp;
    };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 6-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4,
               const int n5,
               const int n6) const
    {
      int itmp = ((n1-1)*index_length[1] + (n2-1));
      itmp = itmp*index_length[2] + (n3-1);
      itmp = itmp*index_length[3] + (n4-1);
      itmp = itmp*index_length[4] + (n5-1);
      itmp = itmp*index_length[5] + (n6-1);
      return itmp;
    };
    // ---------------------------------------------------------------------- //

#else // Check Bounds

    // ----------------------------
    // Direct get and set functions
    // ----------------------------
    const double& vget(const int k) const;

    void vset(const int k, const double value);

    // ----------------------------
    // Direct get and set functions
    // ----------------------------
    const double& dget(const int k) const;

    void dset(const int k, const double value);

    // -------------------
    // Get index functions
    // -------------------

    // 1-index
    int getidx(const int n1) const;

    // 2-index
    int getidx(const int n1,
               const int n2) const;

    // 3-index
    int getidx(const int n1,
               const int n2,
               const int n3) const;

    // 4-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4) const;

    // 5-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4,
               const int n5) const;

    // 6-index
    int getidx(const int n1,
               const int n2,
               const int n3,
               const int n4,
               const int n5,
               const int n6) const;

#endif

    // ---------------------------------------------------------------------- //
    // For arranging DblArray into 1-dimensional vector
    // Useful when dealing with Linear Systems
    // same as for storing data in vec but start at index 1
    // ---------------------------------------------------------------------- //

    // 1-index
    int getVectorIdx(const int n1) const
    { return getidx(n1) + 1; }

    // 2-index
    int getVectorIdx(const int n1,
                     const int n2) const
    { return getidx(n1, n2) + 1; }

    // 3-index
    int getVectorIdx(const int n1,
                     const int n2,
                     const int n3) const
    { return getidx(n1, n2, n3) + 1; }

    // 4-index
    int getVectorIdx(const int n1,
                     const int n2,
                     const int n3,
                     const int n4) const
    { return getidx(n1, n2, n3, n4) + 1; }

    // 5-index
    int getVectorIdx(const int n1,
                     const int n2,
                     const int n3,
                     const int n4,
                     const int n5) const
    { return getidx(n1, n2, n3, n4, n5) + 1; }

    // 6-index
    int getVectorIdx(const int n1,
                     const int n2,
                     const int n3,
                     const int n4,
                     const int n5,
                     const int n6) const
    { return getidx(n1, n2, n3, n4, n5, n6) + 1; }

    // ---------------------------------------------------------------------- //

    // -----------------------------
    // Get, fetch, and set functions
    // -----------------------------

    // ---------------------------------------------------------------------- //
    // 1-index: get, fetch, and set
    const double& get(const int n1) const
    { return vec[getidx(n1)]; };

    double& fetch(const int n1)
    { return vec[getidx(n1)]; };

    void set(const int n1,
             const double inval)
    { vec[getidx(n1)] = inval; };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 2-index: get, fetch, and set
    const double& get(const int n1,
                      const int n2) const
    { return vec[getidx(n1,n2)]; };

    double& fetch(const int n1,
                  const int n2)
    { return vec[getidx(n1,n2)]; };

    void set(const int n1,
             const int n2,
             const double inval)
    { vec[getidx(n1,n2)] = inval; };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 3-index: get, fetch, and set
    const double& get(const int n1,
                      const int n2,
                      const int n3) const
    { return vec[getidx(n1,n2,n3)]; };

    double& fetch(const int n1,
                  const int n2,
                  const int n3)
    { return vec[getidx(n1,n2,n3)]; };

    void set(const int n1,
             const int n2,
             const int n3,
             const double inval)
    { vec[getidx(n1,n2,n3)] = inval; };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 4-index: get, fetch, and set
    const double& get(const int n1,
                      const int n2,
                      const int n3,
                      const int n4) const
    { return vec[getidx(n1,n2,n3,n4)]; };

    double& fetch(const int n1,
                  const int n2,
                  const int n3,
                  const int n4)
    { return vec[getidx(n1,n2,n3,n4)]; };

    void set(const int n1,
             const int n2,
             const int n3,
             const int n4,
             const double inval)
    { vec[getidx(n1,n2,n3,n4)] = inval; };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 5-index: get, fetch, and set
    const double& get(const int n1,
                      const int n2,
                      const int n3,
                      const int n4,
                      const int n5) const
    { return vec[getidx(n1,n2,n3,n4,n5)]; };

    double& fetch(const int n1,
                  const int n2,
                  const int n3,
                  const int n4,
                  const int n5)
    { return vec[getidx(n1,n2,n3,n4,n5)]; };

    void set(const int n1,
             const int n2,
             const int n3,
             const int n4,
             const int n5,
             const double inval)
    { vec[getidx(n1,n2,n3,n4,n5)] = inval; };
    // ---------------------------------------------------------------------- //

    // ---------------------------------------------------------------------- //
    // 6-index: get, fetch, and set
    const double& get(const int n1,
                      const int n2,
                      const int n3,
                      const int n4,
                      const int n5,
                      const int n6) const
    { return vec[getidx(n1,n2,n3,n4,n5,n6)]; };

    double& fetch(const int n1,
                  const int n2,
                  const int n3,
                  const int n4,
                  const int n5,
                  const int n6)
    { return vec[getidx(n1,n2,n3,n4,n5,n6)]; };

    void set(const int n1,
             const int n2,
             const int n3,
             const int n4,
             const int n5,
             const int n6,
             const double inval)
    { vec[getidx(n1,n2,n3,n4,n5,n6)] = inval; };
    // ---------------------------------------------------------------------- //

  private:
    double* vec;
    int num_indeces;
    int total_length;
    int* index_length;

    void compute_total_length();
    void check_index(const int,const int) const;
};

#endif
