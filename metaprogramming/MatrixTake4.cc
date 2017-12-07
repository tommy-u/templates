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
  Debug("About to run copy operator\n");

  int N = depth_lhs<Glue<T1, T2>>::num;
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
  Debug("Addition operator \n");
  return Glue<T1, T2>(A.get_ref(), B.get_ref());
}

// Need general copy constructor.
template <typename T1, typename T2> Matrix::Matrix(const Glue<T1, T2> &X) {
  Debug("Copy cons\n");
  operator=(X);
}

// Printer
void dumpMat(Matrix &X) {
  for (int i = 0; i < X.rows * X.cols; i++) {
    Debug(X.data[i] << " ");
  }
  Debug(std::endl);
}

void test1() {
  Debug("Example: Add 2 matrices \n\n");
  int rows = 2;
  int cols = 2;
  int elems = rows * cols;
  Matrix A(rows, cols);
  Matrix B(rows, cols);

  for (int i = 0; i < elems; i++) {
    A.data[i] = (double)i;
    B.data[i] = (double)i + 4;
  }

  Matrix X;
  X = A + B;

  Debug("X holds:\n");
  dumpMat(X);
}

void test2() {
  Debug("\nExample: Add 3 matrices\n");
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

  Debug("X holds:\n");
  dumpMat(X);
}

void test3() {
  Debug("\nExample: Add a bunch of matrices\n");
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

  Debug("X holds:\n");
  dumpMat(X);
}

void explore_glues(){
  int rows = 2;
  int cols = 2;
  int elems = rows * cols;

  Matrix A(rows, cols);
  Matrix B(rows, cols);

  Debug( "Glues:\n");

  Glue<Matrix, Matrix> MyGlue(A, B);

  int N = depth_lhs<Glue<Matrix, Matrix>>::num;

  Debug("N is: " << N << "\n");

}

int main() {
  // Can add any number of matrices with no overhead.
  test1();
  test2();
  test3();


}
