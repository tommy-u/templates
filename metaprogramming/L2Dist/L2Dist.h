#ifndef L2DIST_H
#define L2DIST_H

#include <math.h>

// SFINAE: substitution failure is not an error.
template <typename T> struct restrictor {};
template <> struct restrictor<float> { typedef float result; };
template <> struct restrictor<double> { typedef double result; };

template <typename T>
typename restrictor<T>::result // This thing is specialized above.
    Distance(T a1, T a2, T b1, T b2) {
  std::cout << "Template distance\n";
  T tmp1 = a1 - b1;
  T tmp2 = a2 - b2;

  return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}

#endif
