#ifndef DOG_MATH_H
#define DOG_MATH_H

class DblArray;

namespace dog_math
{
  // sgnum function.  undefined behavior for x near zero
  double sgn(double x);

  // max of two doubles
  double Max(double a, double b);

  // min of two doubles
  double Min(double a, double b);

  // max of two integers
  int iMax(int a, int b);

  // min of two integers
  int iMin(int a, int b);

  // n choose k
  int choose(int n, int k);

  // mod function: eturns n % m, where the result is between 0 and m-1.
  int iMod(int n, int m);

  // minimum modulus of two double a and b
  // returns 0 if a*b<0.
  double minmod(double a, double b);

  // minimum modulus of three doubles
  // returns 0 if a, b, and c do not all have same sign
  double minmod(double a, double b, double c);

  // maximum modulus of two double a and b
  // returns 0 if a*b<0.
  double maxmod(double a, double b);

  // minmod with total variation bounded adjustment (2 numbers)
  double minmodTVB(double a, double b, double M, double h);

  // minmod with total variation bounded adjustment (3 numbers)
  double minmodTVB(double a, double b, double c, double M, double h);

  // poor man's Factorial function
  // Note: if n < 0, this function returns 1.
  //
  // See: constants.h: factorial for a single access array of factorials
  // 0! through 10!
  int Factorial(int n);

  // returns true if |a-b|<epsilon
  bool almost_eq(double a, double b);

  // round double to nearest integer
  int round(double a);

  // Returns the maximum value of a single vector
  double MaxVector(const DblArray& vec);

  // Returns the maximum absolute value of a single vector
  double MaxAbsVector(const DblArray& vec);

  // Returns a vector containing the maximum value of each component
  // in vec1 and vec2
  void MaxVector(const DblArray& vec1, const DblArray& vec2, DblArray& max);

  // Returns a vector containing the maximum absolute value of each component
  // in vec1 and vec2
  void MaxAbsVector(const DblArray& vec1, const DblArray& vec2, DblArray& max);

  // Returns the maximum value found in Matrix A
  double MaxMatrix(const DblArray& A);

  // Returns the maximum absolute value found in Matrix A
  double MaxAbsMatrix(const DblArray& A);

  // Compute the matrix product: A*B. Save output in C
  void MatrixMultiply(const DblArray& A, const DblArray& B, DblArray& C);

  // Compute the product: A*v. Save output in b.
  void MatVecMultiply(const DblArray& A, const DblArray& v, DblArray& b);

  // Computes the factorial of an integer and then recasts it as a double
  double dfactorial(int n);
}

#endif  // DOG_MATH_H
