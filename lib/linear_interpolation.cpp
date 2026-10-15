#include "linear_interpolation.h"
#include <stdexcept>

double
calculator(double h, double *ptr_h, double *ptr_arg,
           int h_size, // do not sure about issue of sizes of this arrrays
           int arg_size) {
  int low = -1;
  int i = 0;
  while (i < h_size) {
    if (h >= ptr_h[i]) {
      low = ptr_h[i];
    }
    i++;
  }
  if ((low == -1) || (low == h_size - 1)) {
    throw std::runtime_error(
        "Interpolation process failed because of inapropriate data");
  }
  return ((ptr_arg[low]) + (ptr_arg[low + 1] - ptr_arg[low]) *
                               (h - ptr_h[low]) /
                               (ptr_h[low + 1] - ptr_h[low]));
}