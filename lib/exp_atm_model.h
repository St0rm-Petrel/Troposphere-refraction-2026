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
  virtual ~ExpAtmModel() = default;

  double N_h(double h) override { return N_s_ * std::exp(-(h - h_s_) / H_); }

  double H() const noexcept { return H_; }

protected:
  ExpAtmModel(double N_s, double h_s, double H) noexcept
      : N_s_(N_s), h_s_(h_s), H_(H) {}

private:
  double N_s_;
  double h_s_;
  double H_;
};

#endif // EXP_ATM_MODEL_H