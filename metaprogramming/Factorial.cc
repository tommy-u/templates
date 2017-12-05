// Citing:
// http://conradsanderson.id.au/misc/sanderson_templates_lecture_uqcomp7305.pdf

#include <iostream>
#include <cassert>
#include "Factorial.h"

int factorial(int n) {
  if (n == 0) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}

int
main(){
  assert(factorial(4) == Factorial<4>::value);
  std::cout << "No problems." << std::endl;
}
