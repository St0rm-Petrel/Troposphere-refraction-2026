#ifndef ANGLE_DIFF_CALCULATOR
#define ANGLE_DIFF_CALCULATOR
#include <cmath>

class ReturnValue {
public:
  double psi_d;
  double d;
};

class AngleDifferenceCalculator {

public:
  virtual ~AngleDifferenceCalculator() = default;

  // function for calculation intergral of refractive index
  // SRC: (2.43) from citation
  // h_s - height of the target above the surface of the spherical Earth, m
  // h_a - flight altitude of the aircraft, m
  virtual double integral_hs_ha(double h_s, double h_a, double N_s) = 0;

  // function for calculation intergral of refractive index
  // SRC: (2.42), (2.43), (2.46) and (2.47) from citation|
  // psi_d - declination angle, radians
  // h_s - height of the target above the surface of the spherical Earth, m
  // h_a - flight altitude of the aircraft, m
  ReturnValue calculate_d_and_psi_d(double psi_g, double h_s, double h_a,
                                    double N_s);
};

#endif // ANGLE_DIFF_CALCULATOR