#include <iostream>

// Static polymorphism.
// Base<T>::get_ref() gives us a reference to T.
// Base<T> is a wrapper for T. T can be anything.
template <typename derived> struct Base {
  const derived &get_ref() const { return static_cast<const derived &>(*this); }
};

// class Glue;
// Holds ref to 2 types.
// A Glue<T1,T2> obj can be interpreted as a Base<Glue<T1,T2>> obj.
template <typename T1, typename T2> class Glue : public Base<Glue<T1, T2>> {
public:
  const T1 &A;
  const T2 &B;
  Glue(const T1 &in_A, const T2 &in_B) : A(in_A), B(in_B) {}
};

// Deriving Matrix from Base.
// A Matrix object can be interpreted as a Base<Matrix> object.
// Now Base<Matrix>::get_ref() can give a reference to our Matrix obj
class Matrix : public Base<Matrix> {
public:
  // Default cons.
  Matrix() { std::cout << "Default Constructor\n"; }

  // Parameterized cons.
  Matrix(int in_rows, int in_cols) : rows(in_rows), cols(in_cols) {
    std::cout << "Parameterized Constructor\n";
    data = new double[rows * cols];
  }
  void set_size(int in_rows, int in_cols);

  // For the base case, 2 matrices.
  Matrix(const Matrix &X) { std::cout << "Copy Constructor\n"; } // Copy cons.
  const Matrix &operator=(const Matrix &X); // Copy operator.

  // Copy constructor.
  template <typename T1, typename T2> Matrix(const Glue<T1, T2> &x);

  // Copy operator.
  template <typename T1, typename T2>
  const Matrix &operator=(const Glue<T1, T2> &X);

  int rows;
  int cols;
  double *data;
};

// These two structs are for getting the address of each matrix in a Glue
// instance.

// Base case, 0th pointer is current matrix.
template <typename T1> struct mat_ptrs {
  static const int num = 0;
  inline static void get_ptrs(const Matrix **ptrs, const T1 &X) {
    ptrs[0] = reinterpret_cast<const Matrix *>(&X);
  }
};

// Recurse.
template <typename T1, typename T2> struct mat_ptrs<Glue<T1, T2>> {
  static const int num = 1 + mat_ptrs<T1>::num;
  inline static void get_ptrs(const Matrix **in_ptrs, const Glue<T1, T2> &X) {
    // traverse the left node
    mat_ptrs<T1>::get_ptrs(in_ptrs, X.A);
    // Get address of the matrix on the right node
    in_ptrs[num] = reinterpret_cast<const Matrix *>(&X.B);
  }
};

// The next two structs are for counting number matrix instances in a Glue type.
// I don't understand this.

// Base case.
template <typename T1> struct depth_lhs {
  static const int num = 0; // Termination.
};

// Recurse.
template <typename T1, typename T2> struct depth_lhs<Glue<T1, T2>> {
  // Try to expand the lhs, could be a glue type.
  static const int num = 1 + depth_lhs<T1>::num;
};
