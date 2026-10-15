#include <boost/test/unit_test.hpp>
#include "refraction_model.h"
#include <cmath>

BOOST_AUTO_TEST_SUITE(WithoutCurvature)

BOOST_AUTO_TEST_CASE(Pythagoras) {
    RefractionModelWithoutCurvature model;

    // R = 5, h_a = 4, h_s = 1  ->  d = sqrt(25 - 9) = 4
    auto res = model.calculate(4.0, 1.0, 5.0);
    BOOST_CHECK_CLOSE(res.d, 4.0, 1e-6);

    // h_a == h_s  ->  d = R
    res = model.calculate(3.0, 3.0, 5.0);
    BOOST_CHECK_CLOSE(res.d, 5.0, 1e-6);
}

BOOST_AUTO_TEST_CASE(PsiEqual) {
    RefractionModelWithoutCurvature model;
    auto res = model.calculate(100.0, 200.0, 1000.0);

    // Без кривизны psi_d == psi_g
    BOOST_CHECK_CLOSE(res.psi_d, res.psi_g, 1e-9);
}

BOOST_AUTO_TEST_CASE(EqualHeights) {
    RefractionModelWithoutCurvature model;
    auto res = model.calculate(500.0, 500.0, 5000.0);

    BOOST_CHECK_SMALL(res.psi_d, 1e-9);
    BOOST_CHECK_CLOSE(res.d, 5000.0, 1e-9);
}

BOOST_AUTO_TEST_SUITE_END()