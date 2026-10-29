#ifndef EXP_ATM_MODEL_HEIRS_H
#define EXP_ATM_MODEL_HEIRS_H

#include "atm_model.h"
#include "exp_atm_model.h"
#include <cmath>

// auxiliary function for He definition
// SRC: (2.29) from citation
// N_s - refractive index at the Earth's surface, dimentionless quantity
inline double He(double N_s) {
  double delta_N = (0 - 0.00732) * std::exp(0.005577 * N_s);
  return 1000.0 / std::log(N_s / (N_s + 1000.0 * delta_N));
}

// auxiliary function for Hb definition
// SRC: (2.30) from citation
// h_s - the height of the target above the surface of the Earth, m
// N_s - refractive index at the Earth's surface, dimentionless quantity
// hb - a dimensionless constant depending on variant of exponentioal model
// Nb - a dimensionless constant depending on variant of exponentioal model
inline double Hb(double h_s, double N_s, double hb, double Nb) {
  return (hb - h_s) / std::log(N_s / Nb);
}

// H = He(N_s)
class ExpAtmModel3k final : public ExpAtmModel {
public:
  ExpAtmModel3k(double N_s, double h_s) : ExpAtmModel(N_s, h_s, He(N_s)) {}
};

// H = (hb10 - h_s)/ln(N_s/Nb10)
class ExpAtmModel10k final : public ExpAtmModel {
public:
  ExpAtmModel10k(double N_s, double h_s)
      : ExpAtmModel(N_s, h_s, Hb(h_s, N_s, hb10, Nb10)) {}
};

// H = (hb15 - h_s)/ln(N_s/Nb15)
class ExpAtmModel15k final : public ExpAtmModel {
public:
  ExpAtmModel15k(double N_s, double h_s)
      : ExpAtmModel(N_s, h_s, Hb(h_s, N_s, hb15, Nb15)) {}
};

#endif // EXP_ATM_MODEL_HEIRS_H