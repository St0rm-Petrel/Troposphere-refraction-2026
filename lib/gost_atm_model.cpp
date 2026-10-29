#include "gost_atm_model.h"
#include "linear_interpolation.h"
#include "water_vapour.h"
#include <cmath>
#include <vector>

double GOSTAtmModel::N_h(double h) {
  Linear_interpolation Press_inter(hs_, P_);
  double P_inter = Press_inter(h);
  Linear_interpolation Temp_inter(hs_, T_);
  double T_inter = Temp_inter(h);
  double e = (P_inter * rho_w(h)) / 126.68;
  return (double(77.6 / T_inter) * (P_inter + 4810 * e / T_inter));
};