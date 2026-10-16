#include "gost_atm_model.h"
#include "water_vapour.h"
#include <cmath>

double N_h(double h, double *ptr_P, double *ptr_T) {
  double e = (*ptr_P * rho_w(h)) / 126.68;
  return (double((77.6 / *ptr_T) * (*ptr_P + 4810 * e / *ptr_T)));
};