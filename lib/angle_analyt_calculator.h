#ifndef ANGLE_ANALYT_CALCULATOR
#define ANGLE_ANALYT_CALCULATOR

#include "angle_diff_calculator.h"
#include "exp_atm_model.h"

class AngleAnalyticalCalculator : public AngleDifferenceCalculator {
public:
  AngleAnalyticalCalculator(double N_s, double h_s, double H)
      : model_(N_s, h_s, H) {}

  double integral_hs_ha(double h_s, double h_a, double N_s) override;

private:
  ExpAtmModel model_;
};
#endif // ANGLE_ANALYT_CALCULATOR