#ifndef EXP_ATM_MODEL_H
#define EXP_ATM_MODEL_H

#include "atm_model.h"
#include <cmath>

// SRC: (2.31) from citation:
constexpr double hb15 = 12192;
constexpr double Nb15 = 66.65;

// SRC: (2.32) from citation:
constexpr double hb10 = 9144;
constexpr double Nb10 = 102.9;

class ExpAtmModel : public AtmModel {
public:
  ExpAtmModel(double h_s, double N_s, double H) : h_s_(h_s), N_s_(N_s), H_(H) {}

  double N_h(double h, double, double, double = 318) override {
    return N_s_ * std::exp(-(h - h_s_) / H_);
  }

protected:
  double h_s_;
  double N_s_;
  double H_;
};

#endif // EXP_ATM_MODEL_H