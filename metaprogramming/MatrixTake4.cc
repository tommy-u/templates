// Citing:
// http://conradsanderson.id.au/misc/sanderson_templates_lecture_uqcomp7305.pdf

#include "MatrixTake4.h"

// Allocate Matrix after construction time.
void Matrix::set_size(int in_rows, int in_cols) {
  rows = in_rows;
  cols = in_cols;
  // ... Handle memory allocation ...
  data = new double[rows * cols];
}

// Manage adding all Matrices.
template <typename T1, typename T2>
const Matrix &Matrix::operator=(const Glue<T1, T2> &X) {
  int N = 1 + depth_lhs<Glue<T1, T2>>::num;
  const Matrix *ptrs[N];
  mat_ptrs<Glue<T1, T2>>::get_ptrs(ptrs, X);

  int r = ptrs[0]->rows;
  int c = ptrs[0]->cols;

  // ... check matrices have same size ...

  set_size(r, c);
  for (int j = 0; j < r * c; j++) {
    double sum = ptrs[0]->data[j];
    for (int i = 1; i < N; i++) {
      sum += ptrs[i]->data[j];
    }
    data[j] = sum;
  }
  return *this;
}

// Create a Glue combining Matrices or Glues w/ polymorphism.
template <typename T1, typename T2>
inline const Glue<T1, T2> operator+(const Base<T1> &A, const Base<T2> &B) {
  return Glue<T1, T2>(A.get_ref(), B.get_ref());
}

// Need general copy constructor.
template <typename T1, typename T2> Matrix::Matrix(const Glue<T1, T2> &X) {
  std::cout << "Copy cons\n";
  operator=(X);
}

// Printer
void dumpMat(Matrix &X) {
  for (int i = 0; i < X.rows * X.cols; i++) {
    std::cout << X.data[i] << " ";
  }
  std::cout << std::endl;
}

void test1() {
  std::cout << "Example: Add 2 matrices \n\n";
  int rows = 2;
  int cols = 2;
  int elems = rows * cols;
  Matrix A(rows, cols);
  Matrix B(rows, cols);

  for (int i = 0; i < elems; i++) {
    A.data[i] = (double)i;
    B.data[i] = (double)i + 4;
  }

  Matrix X = A + B;

  std::cout << "X holds:\n";
  dumpMat(X);
}

void test2() {
  std::cout << "\nExample: Add 3 matrices\n";
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

  // We can now do this without a temporary matrix!
  Matrix X = A + B + C;

  std::cout << "X holds:\n";
  dumpMat(X);
}

void test3() {
  std::cout << "\nExample: Add a bunch of matrices\n";
  int rows = 2;
  int cols = 2;
  int elems = rows * cols;

  Matrix A(rows, cols);
  Matrix B(rows, cols);
  Matrix C(rows, cols);
  Matrix D(rows, cols);
  Matrix E(rows, cols);
  Matrix F(rows, cols);

  for (int i = 0; i < elems; i++) {
    A.data[i] = (double)i;
    B.data[i] = (double)i;
    C.data[i] = (double)i;
    D.data[i] = (double)i;
    E.data[i] = (double)i;
    F.data[i] = (double)i;
  }

  // We can now do this without a temporary matrix!
  Matrix X = A + A + B + B + C + D + E + F;

  std::cout << "X holds:\n";
  dumpMat(X);
}

int main() {
  // Can add any number of matrices with no overhead.
  test1();
  test2();
  test3();
}
