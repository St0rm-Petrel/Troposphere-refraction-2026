#include "../lib/linear_interpolation.h"
#include "qcustomplot.h"
#include <QApplication>

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_linear_interpolation)

BOOST_AUTO_TEST_CASE(h_and_hs_are_equal) {
  arr_h = {1000, 2000, 2500, 3000, 4500, 5000};
  arr = {300, 400, 550, 600, 700, 800};
  double *ptr_h = arr_h;
  double *ptr_arr = arr;
  BOOST_TEST(calculator(1000, ptr_h, ptr_arr, 5, 5) == 300);
}

BOOST_AUTO_TEST_CASE(h_and_hs_are_equal) {
  arr_h = {1000, 2000, 2500, 3000, 4500, 5000};
  arr = {300, 300, 550, 600, 700, 800};
  double *ptr_h = arr_h;
  double *ptr_arr = arr;
  BOOST_TEST(calculator(1500, ptr_h, ptr_arr, 5, 5) == 300);
}

BOOST_AUTO_TEST_SUITE_END()
