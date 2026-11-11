#ifndef SEG_ATM_MODEL_H
#define SEG_ATM_MODEL_H
#include "atm_model.h"

class SegAtmModel : public AtmModel {
public:
  SegAtmModel(double N_s, double h_s, double N1 = 318.0)
      : N_s_(N_s), h_s_(h_s), N1_(N1) {}

  // Get N(h) - refractive index depending on height
  // SRC : (2.27) - (2.30) from citation
  // N_h : refractive index, dimensionless quantity
  // h : studied height, m
  // N_s : refractive index at the Earth's surface, dimensionless quantity
  // h_s : height of the target above the surface of the spherical Earth, m
  // N1 : refractive index at a height of 1 km above the Earth's surface,
  // dimensionless quantity
  double N_h(double h) override;

private:
  double N_s_;
  double h_s_;
  double N1_;
};

#endif // SEG_ATM_MODEL_H