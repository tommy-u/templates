#include <cassert>
#include <iostream>

#include "L2Dist.h"

float distance(float a1, float a2, float b1, float b2) {
  std::cout << "float distance\n";
  float tmp1 = a1 - b1;
  float tmp2 = a2 - b2;
  return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}

double distance(double a1, double a2, double b1, double b2) {
  std::cout << "double distance\n";
  double tmp1 = a1 - b1;
  double tmp2 = a2 - b2;
  return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}

int main() {
  std::cout << distance((float)1, (float)2, (float)3, (float)4) << std::endl;
  std::cout << distance((double)1, (double)2, (double)3, (double)4)
            << std::endl;

  std::cout << Distance((float)1, (float)2, (float)3, (float)4) << std::endl;
  std::cout << Distance((double)1, (double)2, (double)3, (double)4)
            << std::endl;

  // Compile time error because of SFINAE.
  // std::cout << Distance((int)1, (int)2, (int)3, (int)4) << std::endl;
}
