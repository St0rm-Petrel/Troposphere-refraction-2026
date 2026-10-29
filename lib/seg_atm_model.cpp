#include "seg_atm_model.h"
#include <cmath>

double SegAtmModel::N_h(double h) {
  if (h_s_ <= h && h <= (h_s_ + 1000)) {
    double delta_N = (0 - 0.00732) * std::exp(0.005577 * N_s_);
    return (N_s_ + (h - h_s_) * delta_N);
  } else if (h_s_ + 1000 <= h && h <= 9000) {
    double H = (8000 - h_s_) / std::log(N1_ / 105);
    return (N1_ * std::exp(-(h - h_s_ - 1000) / H));
  } else if (h > 9000) {
    return (105 * std::exp(-(h - 9000) / 7023));
  }
}
