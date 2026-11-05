#ifndef ANGLE_DIFF_CALCULATE
#define ANGLE_DIFF_CALCULATE
#include <cmath>

double Re = 6371000;

class AngleDifferenceCalculator {

public:
  virtual ~AngleDifferenceCalculator() = default;

  // function for calculation intergral of refractive index
  // SRC: (2.43) from citation
  // h_s - height of the target above the surface of the spherical Earth, m
  // h_a - flight altitude of the aircraft, m
  virtual double integral_hs_ha(double h_s, double h_a) = 0;

  // function for calculation intergral of refractive index
  // SRC: (2.42), (2.43), (2.46) and (2.47) from citation|
  // psi_d - declination angle, radians
  // h_s - height of the target above the surface of the spherical Earth, m
  // h_a - flight altitude of the aircraft, m
  double calculate_d_and_psi_g(double psi_d, double h_s, double h_a);

protected:
  AngleDifferenceCalculator(double psi_d, double h_s, double h_a) noexcept
      : psi_d_(psi_d), h_s_(h_s), h_a_(h_a) {}

private:
  double psi_d_;
  double h_s_;
  double h_a_;
};

#endif // ANGLE_DIFF_CALCULATE