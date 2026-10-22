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

BOOST_AUTO_TEST_CASE(exact_node) {
  std::vector<double> hs{1000, 2000, 2500, 3000, 4500, 5000};
  std::vector<double> vs{300, 400, 550, 600, 700, 800};
  Linear_interpolation li(hs, vs);

  BOOST_TEST(li(1000) == 300.0);
  BOOST_TEST(li(2500) == 550.0);
  BOOST_TEST(li(5000) == 800.0);
}

BOOST_AUTO_TEST_CASE(midpoint) {
  std::vector<double> hs{1000, 2000, 2500, 3000, 4500, 5000};
  std::vector<double> vs{300, 400, 550, 600, 700, 800};
  Linear_interpolation li(hs, vs);

  BOOST_TEST(li(1500) == 350.0);
  BOOST_TEST(li(2750) == 575.0);
  BOOST_TEST(li(4750) == 750.0);
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
