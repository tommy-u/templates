// Citing:
// http://conradsanderson.id.au/misc/sanderson_templates_lecture_uqcomp7305.pdf

#include "MatrixTake2.h"

void Matrix::set_size(int in_rows, int in_cols) {
  rows = in_rows;
  cols = in_cols;
  data = new double[rows * cols];
}

const Glue operator+(const Matrix &A, const Matrix &B) {
  // Return result of running Glue constructor.
  std::cout << "Create Glue from mats.\n";

  std::cout << "Mat1[0] = " << A.data[0] << "\n";
  std::cout << "Mat2[0] = " << B.data[0] << "\n";
  return Glue(A, B);
}

// copy constructor Allows you to do: Matrix X = A + B;
Matrix::Matrix(const Glue &X) {
  std::cout << "Copy constructor Matrix = Glue\n";
  operator=(X);
}

// copy operator
const Matrix &Matrix::operator=(const Glue &X) {
  std::cout << "Run copy operator \n";
  const Matrix &A = X.A;
  const Matrix &B = X.B;
  // Assume this doesn't already have data.
  set_size(A.rows, A.cols);

  for (int i = 0; i < A.rows * A.cols; ++i) {
    data[i] = A.data[i] + B.data[i];
  }
  return *this;
}

void dumpMat(Matrix &X) {
  for (int i = 0; i < X.rows * X.cols; i++) {
    std::cout << X.data[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  int rows = 2;
  int cols = 2;
  int elems = rows * cols;

  Matrix A(rows, cols);
  Matrix B(rows, cols);
  Matrix C(rows, cols);

  for (int i = 0; i < elems; i++) {
    A.data[i] = (double)i;
    B.data[i] = (double)i + 4;
    C.data[i] = (double)i + 8;
  }

  // A + B creates a const Glue
  // = operator populates X it with result of addition of matrices pointed to by
  // glue.
  // No extra space or memory usage.
  std::cout << "About to add 2 matrices \n\n";

  Matrix X;
  X = A + B;

  printf("X holds:\n");
  dumpMat(X);

  // This still sucks because we make a temporary matrix for (A + B) to which we
  // add C.
  std::cout << "About to add 3 matrices \n\n";
  X = A + B + C;
  printf("X holds:\n");
  dumpMat(X);
}
