// Citing:
// http://conradsanderson.id.au/misc/sanderson_templates_lecture_uqcomp7305.pdf

#include <iostream>

class Matrix {
public:
  Matrix();                         // Default cons.
  Matrix(int in_rows, int in_cols); // Parametrized cons.
  Matrix(const Matrix &X);          // Copy cons.

  const Matrix &operator=(const Matrix &X);

  Matrix operator+(const Matrix &B);

  void set_size(int in_rows, int in_cols);

  int rows;
  int cols;
  double *data;
};

Matrix::Matrix() { std::cout << "Default Constructor\n"; }

Matrix::Matrix(const Matrix &X) { std::cout << "Copy Constructor\n"; }

const Matrix &Matrix::operator=(const Matrix &X) {
  std::cout << "Copy operator\n";
  rows = X.rows;
  cols = X.cols;
  data = new double[rows * cols];
  for (int i = 0; i < (rows * cols); i++) {
    data[i] = X.data[i];
  }
}

Matrix::Matrix(int in_rows, int in_cols) : rows(in_rows), cols(in_cols) {
  std::cout << "Parameterized Constructor\n";
  data = new double[rows * cols];
}

Matrix Matrix::operator+(const Matrix &B) {
  // ... Check dimenstions ...
  Matrix X(rows, cols);
  for (int i = 0; i < rows * cols; ++i) {
    X.data[i] = data[i] + B.data[i];
  }
  return X;
}

class Glue{
public:
  const Matrix& A;
  const Matrix& B;

  Glue(const Matrix& in_A, const Matrix& in_B) : A(in_A), B(in_B){}
  // const Glue operator+(const Matrix& A, const Matrix& B){}
};

Glue operator+(const Matrix& A, const Matrix& B){
  return Glue(A,B);
}

int main() {
  int rows = 2;
  int cols = 2;
  int elems = rows * cols;

  Matrix A(rows, cols);
  Matrix B(rows, cols);

  for (int i = 0; i < elems; i++) {
    A.data[i] = (double)i;
    B.data[i] = (double)i + 4;
  }

  // This sucks becuse + operator makes a temporary and = copies it through.
  // 2x as much memory as optimal and 2x as long (two linear traversals).
  Matrix X;
  X = A + B;

  printf("X holds:\n");
  for (int i = 0; i < elems; i++) {
    std::cout << X.data[i] << " ";
  }
  std::cout << std::endl;
}
