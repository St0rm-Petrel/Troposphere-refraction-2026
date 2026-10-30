#ifndef GOST_ATM_MODEL_H
#define GOST_ATM_MODEL_H
#include "atm_model.h"
#include <vector>

class GOSTAtmModel : public AtmModel {
public:
  GOSTAtmModel(std::vector<double> hs, std::vector<double> P,
               std::vector<double> T)
      : hs_(hs), P_(P), T_(T) {}

  // Get N(h) - refractive index depending on height according to GOST
  // SRC : (2.23) - (2.24) from citation
  // h - studied height, m
  // hs - vector of known heights, m
  // P - vector P(h), mbar
  // T - vector T(h), K
  double N_h(double h) override;

private:
  std::vector<double> hs_;
  std::vector<double> P_;
  std::vector<double> T_;
};

#endif // GOST_ATM_MODEL_H