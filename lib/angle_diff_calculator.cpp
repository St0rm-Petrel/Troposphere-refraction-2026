#include "angle_diff_calculator.h"
#include "seg_atm_model.h"
#include <cmath>

double Re = 6371000.0;
double dh = 100.0;

ReturnValue AngleDifferenceCalculator::calculate_d_and_psi_d(double psi_g,
                                                             double h_s,
                                                             double h_a,
                                                             double N_s) {
  ReturnValue result;

  double cospsi_d =
      cos(psi_g) * (Re + h_s) / (Re + h_a) / exp(integral_hs_ha(h_s, h_a, N_s));

  result.psi_d = std::acos(cospsi_d);

  result.d = log((sin(psi_g)) / (sin(result.psi_d)));

  return result;
}