#include "angle_diff_calculator.h"
#include "seg_atm_model.h"
#include <cmath>

double AngleDifferenceCalculator::calculate_d_and_psi_g(double psi_d,
                                                        double h_s, double h_a,
                                                        double N_s) {
  double cospsi_g =
      cos(psi_d) /
      exp(-(log((Re + h_a) / (Re + h_s)) + integral_hs_ha(h_s, h_a, N_s)));

  return std::acos(cospsi_g);
}

double integral_hs_ha(double h_s, double h_a, double N_s) {

  double h_curr = h_s;
  double result = 0;

  while (h_curr < h_a) {
    double step = dh;
    if ((h_a - h_curr) < step) {
      step = h_a - h_curr;
    }
    SegAtmModel model(N_s, h_curr);
    double n_max = (model.N_h(h_curr) * 1e-6) + 1;
    double n_min = (model.N_h(h_curr + dh) * 1e-6) + 1;
    double dn = n_min - n_max;
    result += (2 / (n_max + n_min)) * dn;
    h_curr += dh;
  }
  return (result);
}