#define BOOST_TEST_MODULE RefractionModelTests
#include <boost/test/included/unit_test.hpp>

#include "refraction_model.h"
#include <cmath>

// ─────────────────────────────────────────────────────────────
// SUITE 1: Модель без учёта кривизны Земли
// ─────────────────────────────────────────────────────────────

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

// ─────────────────────────────────────────────────────────────
// SUITE 2: Модель с учётом кривизны (базовый класс и полиморфизм)
// ─────────────────────────────────────────────────────────────

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

// ─────────────────────────────────────────────────────────────
// SUITE 3: Пресеты K43 и K1
// ─────────────────────────────────────────────────────────────

BOOST_AUTO_TEST_SUITE(Presets)

BOOST_AUTO_TEST_CASE(K43_HasCorrectK) {
    RefractionModelK43 model;
    BOOST_CHECK_CLOSE(model.K(), 4.0 / 3.0, 1e-9);
}

BOOST_AUTO_TEST_CASE(K1_HasCorrectK) {
    RefractionModelK1 model;
    BOOST_CHECK_CLOSE(model.K(), 1.0, 1e-9);
}

BOOST_AUTO_TEST_CASE(K43AndK1_DifferInResult) {
    RefractionModelK43 m43;
    RefractionModelK1  m1;

    double h_a = 1274.0;
    double h_s = 1274.0;
    double R   = 2.1 * 1274.0;

    auto r43 = m43.calculate(h_a, h_s, R);
    auto r1  = m1.calculate(h_a, h_s, R);

    BOOST_CHECK(r43.d > 0.0);
    BOOST_CHECK(r1.d  > 0.0);
    BOOST_CHECK(std::abs(r43.d - r1.d) > 1e-6);
}

BOOST_AUTO_TEST_SUITE_END()