#include "gost_atm_model.h"
#include "linear_interpolation.h"
#include "water_vapour.h"
#include <cmath>
#include <vector>

double N_h(double h, std::vector<double> *hs, std::vector<double> *P,
           std::vector<double> *T) {
  Linear_interpolation Press_inter(hs, P);
  double P_inter = Press_inter(h);
  Linear_interpolation Temp_inter(hs, T);
  double T_inter = Temp_inter(h);
  double e = ((*P)[0] * rho_w(h)) / 126.68;
  return (double(77.6 / (*T)[0]) * ((*P)[0] + 4810 * e / (*T)[0]));
};