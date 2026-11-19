#ifndef SEG_ATM_MODEL_H
#define SEG_ATM_MODEL_H
#include "atm_model.h"

class SegAtmModel : public AtmModel {
public:
  SegAtmModel(double N_s, double h_s) : N_s_(N_s), h_s_(h_s) {}

  // Get N(h) - refractive index depending on height
  // SRC : (2.27) - (2.30) from citation
  // N_h : refractive index, dimensionless quantity
  // h : studied height, m
  // N_s : refractive index at the Earth's surface, dimensionless quantity
  // h_s : height of the target above the surface of the spherical Earth, m
  double N_h(double h) override;

private:
  double N_s_;
  double h_s_;
};

#endif // SEG_ATM_MODEL_H