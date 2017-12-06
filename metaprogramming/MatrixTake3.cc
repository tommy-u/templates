// Citing:
// http://conradsanderson.id.au/misc/sanderson_templates_lecture_uqcomp7305.pdf

#include "MatrixTake3.h"

void Matrix::set_size(int in_rows, int in_cols) {
  rows = in_rows;
  cols = in_cols;
  data = new double[rows * cols];
}

inline
const Glue<Matrix, Matrix>
operator+(const Matrix& A, const Matrix& B) {
  // Return result of running Glue constructor.
  return Glue<Matrix, Matrix>(A,B);
}

inline
const Glue<Glue<Matrix, Matrix>, Matrix>
operator+(const Glue<Matrix, Matrix> &P, const Matrix &Q) {
  return Glue<Glue<Matrix, Matrix>, Matrix>(P, Q);
}

// Copy Constructor.
Matrix::Matrix(const Glue<Matrix, Matrix>& X){
  std::cout << "Copy cons Matrix <= Glue<Matrix, Matrix>\n";
  operator=(X);
}

// Copy constructor.
Matrix::Matrix(const Glue<Glue<Matrix, Matrix>, Matrix>& X){
  std::cout << "Copy cons Matrix <= Glue<Glue<Matrix, Matrix>, Matrix>\n";
  operator=(X);
}

const Matrix&
Matrix::operator=(const Glue<Matrix,Matrix> &X){
  const Matrix& A = X.A; // first argument of first Glue
  const Matrix& B = X.B; // second argument of first Glue
  // Check same size.
  set_size(A.rows, A.cols);
  for(int i=0; i<A.rows * A.cols; i++){
    data[i] = A.data[i] + B.data[i];
  }
  return *this;
}

// copy operator
const Matrix&
Matrix::operator=(const Glue< Glue<Matrix,Matrix>, Matrix>& X)
{
  const Matrix& A = X.A.A; // first argument of first Glue
  const Matrix& B = X.A.B; // second argument of first Glue
  const Matrix& C = X.B; // second argument of second Glue
  // ... check if A, B and C have the same size ...
  set_size(A.rows, A.cols);

  for(int i=0; i < A.rows * A.cols; ++i) {
      data[i] = A.data[i] + B.data[i] + C.data[i];
    }
  return *this;
}

void dumpMat(Matrix &X){
  for (int i = 0; i < X.rows * X.cols; i++) {
    std::cout << X.data[i] << " ";
  }
  std::cout << std::endl;
}

void test1(){
  int rows = 2;
  int cols = 2;
  int elems = rows * cols;
  Matrix A(rows, cols);
  Matrix B(rows, cols);

  for (int i = 0; i < elems; i++) {
    A.data[i] = (double)i;
    B.data[i] = (double)i + 4;
  }

  std::cout << "About to add 2 matrices \n\n";

  Matrix X;
  X = A + B;
  // Matrix X = A + B;

  std::cout << "X holds:\n";
  dumpMat(X);
}
void test2(){
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

  std::cout << "About to add 3 matrices \n\n";
  // We can now do this without a temporary matrix!
  Matrix X;
  X= A + B + C;
  // Matrix X = A + B + C;
  std::cout << "X holds:\n";
  dumpMat(X);
}


int main() {
  test1();
  // test2();
  // Unfortunately, but it still sucks because we had to add special a case copy constructor and operator in the matrix class :(. What can we do?
}
