#include "gost_atm_model.h"
#include "linear_interpolation.h"
#include "water_vapour.h"
#include <cmath>
#include <vector>

template <typename InterpolatorType>
double GOSTAtmModel<InterpolatorType>::N_h(double h) {

  double P_inter = interpolator_P(h);
  double T_inter = interpolator_T(h);
  double e = (P_inter * rho_w(h)) / 126.68;
  return (double(77.6 / T_inter) * (P_inter + 4810 * e / T_inter));
}