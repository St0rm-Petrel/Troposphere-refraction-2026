#include "gost_atm_model.h"
#include "linear_interpolation.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#include <vector>

const std::vector<double> kHs = {0.0, 1000.0};
const std::vector<double> kP = {1013.25, 898.75};
const std::vector<double> kT = {288.15, 281.65};

struct GostModelFixture {
  GOSTAtmModel<LinearInterpolation> model{kHs, kP, kT};
};

BOOST_FIXTURE_TEST_SUITE(test_gost_model, GostModelFixture)
BOOST_AUTO_TEST_CASE(refractive_index_decreases_with_height) {
  BOOST_TEST(model.N_h(1000.0) < model.N_h(0.0));
}

BOOST_AUTO_TEST_SUITE_END()