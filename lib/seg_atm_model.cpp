#include "seg_atm_model.h"
#include <cmath>

double SegAtmModel::N_h(double h) {
  double delta_N = (0 - 0.00732) * std::exp(0.005577 * N_s_);
  double N1 = N_s_ + 1000.0 * delta_N;
  if (h <= (h_s_ + 1000)) {
    return (N_s_ + (h - h_s_) * delta_N);
  } else if (h_s_ + 1000 <= h && h <= 9000) {
    double H = (8000 - h_s_) / std::log(N1 / 105);
    return (N1 * std::exp(-(h - h_s_ - 1000) / H));
  } else {
    return (105 * std::exp(-(h - 9000) / 7023));
  }
}
