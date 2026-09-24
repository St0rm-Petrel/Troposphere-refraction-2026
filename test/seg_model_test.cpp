#include "../lib/seg_atm_model.h"
#include <QApplication>
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_seg_model)

BOOST_AUTO_TEST_CASE(h_and_hs_are_equal) { BOOST_TEST(N_h(10, 300, 10) == 300); }

BOOST_AUTO_TEST_CASE(Nh_hs_plus_1000m) {
  BOOST_TEST(N_h(2000, 300, 1000 + 1e-6) == N_h(2000, 300, 1000 - 1e-6), tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(h_9000m) {
  BOOST_TEST(N_h(9000 + 1e-6, 300, 1000) == N_h(9000 - 1e-6, 300, 1000), tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()