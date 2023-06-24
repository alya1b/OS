#include <iostream>
#include <omp.h>

int main() {
  int sum = 0;

  #pragma omp parallel num_threads(2)
  {
    for (int i = 0; i < 1000; i++) {
      #pragma omp critical
      {
        sum++;
      }

      #pragma omp barrier
    }
  }

  std::cout << "Sum: " << sum << std::endl;

  return 0;
}
