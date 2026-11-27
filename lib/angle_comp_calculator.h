#ifndef ANGLE_COMP_CALCULATOR
#define ANGLE_COMP_CALCULATOR
#include "angle_diff_calculator.h"
#include "seg_atm_model.h"

class AngleComputationalCalculator : public AngleDifferenceCalculator {
public:
  AngleComputationalCalculator(double N_s, double h_s) : N_s_(N_s), h_s_(h_s) {}

  double integral_hs_ha(double h_s, double h_a, double N_s) override;

  double N_s_;
  double h_s_;
  SegAtmModel model_{N_s_, h_s_};
};

#endif ANGLE_COMP_CALCULATOR