#include "linear_interpolation.h"
#include <stdexcept>

double Linear_interpolation::operator()(double h) {
  if (h < (*hs_)[0]) {
    throw std::runtime_error(
        "Interpolation process failed because of inapropriate data");
  }
  if (h > (*hs_)[hs_->size() - 1]) {
    throw std::runtime_error(
        "Interpolation process failed because of inapropriate data");
  }
  for (int i = 0; i < (hs_->size() - 2); i++) {
    if ((*hs_)[i] <= h <= (*hs_)[i + 1]) {
      return (((*hs_)[i]) + ((*hs_)[i + 1] - (*hs_)[i]) * (h - (*hs_)[i]) /
                                ((*hs_)[i + 1] - (*hs_)[i]));
    }
  }
}
