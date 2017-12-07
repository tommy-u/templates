#include <iostream>

class Glue;

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

  Matrix(const Glue &X);                  // copy constructor
  const Matrix &operator=(const Glue &X); // copy operator

  int rows;
  int cols;
  double *data;
};

// Holds ref to 2 Matrices.
class Glue {
public:
  const Matrix &A;
  const Matrix &B;
  Glue(const Matrix &in_A, const Matrix &in_B) : A(in_A), B(in_B) {}
};
