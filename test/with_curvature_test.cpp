#include <boost/test/unit_test.hpp>
#include "refraction_model.h"
#include <cmath>

BOOST_AUTO_TEST_SUITE(WithCurvature)

BOOST_AUTO_TEST_CASE(DefaultKIsOne) {
    // У базового класса k = 1.0 по умолчанию
    RefractionModelWithCurvature model;
    BOOST_CHECK_CLOSE(model.K(), 1.0, 1e-9);
}

BOOST_AUTO_TEST_CASE(SymmetricHeights) {
    RefractionModelWithCurvature model;

    // При h_a == h_s: psi_d = -psi_g, d > 0
    auto res = model.calculate(1000.0, 1000.0, 5000.0);
    BOOST_CHECK(res.d > 0.0);
    BOOST_CHECK_CLOSE(res.psi_d, -res.psi_g, 1e-6);
}

BOOST_AUTO_TEST_CASE(PolymorphicK_DifferentResults) {
    // Полиморфизм: разные k через виртуальный K() дают разные d
    RefractionModelK43 m43;
    RefractionModelK1  m1;

    BOOST_CHECK_CLOSE(m43.K(), 4.0 / 3.0, 1e-9);
    BOOST_CHECK_CLOSE(m1.K(),  1.0,       1e-9);

    double h_a = 1000.0;
    double h_s = 1000.0;
    double R   = 2.1 * 1000.0;

    auto r43 = m43.calculate(h_a, h_s, R);
    auto r1  = m1.calculate(h_a, h_s, R);

    BOOST_CHECK(r43.d > 0.0);
    BOOST_CHECK(r1.d  > 0.0);
    BOOST_CHECK(std::abs(r43.d - r1.d) > 1e-6);
}

BOOST_AUTO_TEST_SUITE_END()