#include "angle_analyt_calculator.h"
#include <cmath>

double AngleAnalyticalCalculator::integral_hs_ha(double h_s, double h_a,
                                                 double N_s) {
  return (log(
      (1 + 1e-6 * N_s * exp(-(h_a - h_s) / model_.H()) / (1 + 1e-6 * N_s))));
}