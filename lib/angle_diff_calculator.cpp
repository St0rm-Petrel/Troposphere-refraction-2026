#include "angle_diff_calculator.h"
#include "seg_atm_model.h"
#include <cmath>

double Re = 6371000.0;
double dh = 100.0;

double AngleDifferenceCalculator::calculate_d_and_psi_d(double psi_g,
                                                        double h_s, double h_a,
                                                        double N_s) {
  double cospsi_d =
      cos(psi_g) * (Re + h_s) / (Re + h_a) / exp(integral_hs_ha(h_s, h_a, N_s));

  return std::acos(cospsi_d);
}

double AngleDifferenceCalculator::integral_hs_ha(double h_s, double h_a,
                                                 double N_s) {

  SegAtmModel model(N_s, h_s);

  double n_h_a = (model.N_h(h_a) * 1e-6) + 1;
  double n_h_s = (model.N_h(h_s) * 1e-6) + 1;

  return log(n_h_a / n_h_s);
}