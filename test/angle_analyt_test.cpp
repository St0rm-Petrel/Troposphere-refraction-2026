#include "../lib/angle_analyt_calculator.h"
#include <boost/test/unit_test.hpp>
#include <cmath>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_angle_analytical_calculator)

BOOST_AUTO_TEST_CASE(integral_zero_height_diff) {
  double N_s = 313.0;
  double h_s = 0.0;
  double H = 8000.0;

  AngleAnalyticalCalculator calc(N_s, h_s, H);
  double result = calc.integral_hs_ha(h_s, h_s, N_s);

  BOOST_TEST(result == 0.0, tt::tolerance(1e-9));
}

BOOST_AUTO_TEST_CASE(integral_negative_for_positive_height) {
  double N_s = 313.0;
  double h_s = 0.0;
  double H = 8000.0;

  AngleAnalyticalCalculator calc(N_s, h_s, H);
  double result = calc.integral_hs_ha(h_s, 10000.0, N_s);

  BOOST_TEST(result < 0.0);
}

BOOST_AUTO_TEST_CASE(integral_exact_value_check) {
  double N_s = 313.0;
  double h_s = 0.0;
  double H = 8000.0;
  double h_a = 1000.0;

  AngleAnalyticalCalculator calc(N_s, h_s, H);
  double result = calc.integral_hs_ha(h_s, h_a, N_s);
  double n_hs = 1.0 + N_s * 1e-6;
  double n_ha = 1.0 + N_s * std::exp(-(h_a - h_s) / H) * 1e-6;
  double expected = std::log(n_ha / n_hs);

  BOOST_TEST(result == expected, tt::tolerance(1e-9));
}

BOOST_AUTO_TEST_CASE(integral_dependency_on_H) {
  double N_s = 313.0;
  double h_s = 0.0;
  double h_a = 5000.0;

  AngleAnalyticalCalculator calc_small_H(N_s, h_s, 7000.0);
  double res_small_H = calc_small_H.integral_hs_ha(h_s, h_a, N_s);

  AngleAnalyticalCalculator calc_large_H(N_s, h_s, 9000.0);
  double res_large_H = calc_large_H.integral_hs_ha(h_s, h_a, N_s);

  BOOST_TEST(std::abs(res_small_H) > std::abs(res_large_H));
}

BOOST_AUTO_TEST_CASE(integral_nonzero_surface_height) {
  double N_s = 313.0;
  double h_s = 1000.0;
  double H = 8000.0;
  double h_a = 5000.0;

  AngleAnalyticalCalculator calc(N_s, h_s, H);
  double result = calc.integral_hs_ha(h_s, h_a, N_s);
  double n_hs = 1.0 + N_s * std::exp(-(h_s - h_s) / H) * 1e-6;
  double n_ha = 1.0 + N_s * std::exp(-(h_a - h_s) / H) * 1e-6;
  double expected = std::log(n_ha / n_hs);

  BOOST_TEST(result == expected, tt::tolerance(1e-9));
}

BOOST_AUTO_TEST_SUITE_END()