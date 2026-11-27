#include "angle_comp_calculator.h"
#include <cmath>

double AngleComputationalCalculator::integral_hs_ha(double h_s, double h_a,
                                                    double N_s) {

  double n_h_a = (AngleComputationalCalculator::model_.N_h(h_a) * 1e-6) + 1;
  double n_h_s = (AngleComputationalCalculator::model_.N_h(h_s) * 1e-6) + 1;

  return log(n_h_a / n_h_s);
}