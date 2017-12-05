// Citing:
// http://conradsanderson.id.au/misc/sanderson_templates_lecture_uqcomp7305.pdf
#ifndef FACTORIAL_H
#define FACTORIAL_H

template <int N> struct Factorial {
  static const int value = N * Factorial<N - 1>::value;
};

template <> struct Factorial<0> { static const int value = 1; };
#endif
