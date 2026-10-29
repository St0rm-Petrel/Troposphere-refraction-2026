#include "../lib/seg_atm_model.h"
#include "qcustomplot.h"
#include <QApplication>

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_seg_model)

struct SegAtmFixture10 {
  SegAtmModel model{300.0, 10.0};
};

struct SegAtmFixture1000 {
  SegAtmModel model{300.0, 1000.0};
};

BOOST_FIXTURE_TEST_CASE(h_and_hs_are_equal, SegAtmFixture10) {
  BOOST_TEST(model.N_h(10.0) == 300.0);
}

BOOST_FIXTURE_TEST_CASE(Nh_hs_plus_1000m, SegAtmFixture1000) {
  BOOST_TEST(model.N_h(2000.0 + 1e-6) == model.N_h(2000.0 - 1e-6),
             tt::tolerance(1e-6));
}

BOOST_FIXTURE_TEST_CASE(h_9000m, SegAtmFixture1000) {
  BOOST_TEST(model.N_h(9000.0 + 1e-6) == model.N_h(9000.0 - 1e-6),
             tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()