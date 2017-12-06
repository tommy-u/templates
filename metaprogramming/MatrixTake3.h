#include <iostream>

// class Glue;
// Holds ref to 2 types.
template <typename T1, typename T2> class Glue {
public:
  const T1 &A;
  const T2 &B;
  Glue(const T1 &in_A, const T2 &in_B) : A(in_A), B(in_B) {}
};

class Matrix {
public:
  // Default cons.
  Matrix() { std::cout << "Default Constructor\n"; }

  // Parameterized cons.
  Matrix(int in_rows, int in_cols) : rows(in_rows), cols(in_cols) {
    std::cout << "Parameterized Constructor\n";
    data = new double[rows * cols];
  }
  void set_size(int in_rows, int in_cols);

  Matrix(const Matrix &X) { std::cout << "Copy Constructor\n"; } // Copy cons.
  const Matrix &operator=(const Matrix &X); // Copy operator.

  Matrix(const Glue<Matrix, Matrix> &X);                  // copy constructor
  const Matrix &operator=(const Glue<Matrix, Matrix> &X); // copy operator

  Matrix(const Glue<Glue<Matrix, Matrix>, Matrix> &X); // Copy cons.
  const Matrix &
  operator=(const Glue<Glue<Matrix, Matrix>, Matrix> &X); // Copy operator.

  int rows;
  int cols;
  double *data;
};
