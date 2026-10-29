#include "../lib/linear_interpolation.h"
#include "qcustomplot.h"
#include <QApplication>

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#include <stdexcept>
#include <vector>

BOOST_AUTO_TEST_SUITE(linear_interpolation_test)

struct LinearInterpolationFixture {
  std::vector<double> hs{1000, 2000, 2500, 3000, 4500, 5000};
  std::vector<double> vs{300, 400, 550, 600, 700, 800};
  Linear_interpolation li{hs, vs};
};

BOOST_FIXTURE_TEST_CASE(exact_node, LinearInterpolationFixture) {
  std::vector<double> test_inputs{1000, 2500, 5000};
  std::vector<double> expected_outputs{300.0, 550.0, 800.0};

  for (size_t i = 0; i < test_inputs.size(); ++i) {
    BOOST_TEST(li(test_inputs[i]) == expected_outputs[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(midpoint, LinearInterpolationFixture) {
  std::vector<double> test_inputs{1500, 2750, 4750};
  std::vector<double> expected_outputs{350.0, 575.0, 750.0};

  for (size_t i = 0; i < test_inputs.size(); ++i) {
    BOOST_TEST(li(test_inputs[i]) == expected_outputs[i]);
  }
}

BOOST_AUTO_TEST_CASE(out_of_range) {
  std::vector<double> hs{1000, 2000, 3000};
  std::vector<double> vs{300, 400, 500};
  Linear_interpolation li(hs, vs);

  BOOST_CHECK_THROW(li(500), std::runtime_error);
  BOOST_CHECK_THROW(li(3500), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(size_mismatch) {
  std::vector<double> hs{1000, 2000, 3000};
  std::vector<double> vs{300, 400};
  BOOST_CHECK_THROW(Linear_interpolation(hs, vs), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()