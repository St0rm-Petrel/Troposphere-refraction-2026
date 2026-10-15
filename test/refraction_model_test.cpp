#define BOOST_TEST_MODULE RefractionModelTests
#include <boost/test/included/unit_test.hpp>

#include "refraction_model.h"
#include <cmath>

constexpr double EARTH_RADIUS = 6371.0;   // радиус Земли в км, как в модели

// ─────────────────────────────────────────────────────────────
// Тесты для RefractionModelWithoutCurvature
// ─────────────────────────────────────────────────────────────

BOOST_AUTO_TEST_CASE(WithoutCurvature_Pythagoras) {
    RefractionModelWithoutCurvature model;

    // Прямоугольный треугольник 3-4-5: d = sqrt(R² - (h_s - h_a)²)
    // R = 5, h_a = 4, h_s = 1  ->  d = sqrt(25 - 9) = 4
    auto res = model.calculate(4.0, 1.0, 5.0);
    BOOST_CHECK_CLOSE(res.d, 4.0, 1e-6);

    // Симметричный случай: h_a == h_s  ->  d = R
    res = model.calculate(3.0, 3.0, 5.0);
    BOOST_CHECK_CLOSE(res.d, 5.0, 1e-6);
}

BOOST_AUTO_TEST_CASE(WithoutCurvature_PsiEqual) {
    RefractionModelWithoutCurvature model;
    auto res = model.calculate(100.0, 200.0, 1000.0);

    // Без кривизны psi_d == psi_g (симметрия)
    BOOST_CHECK_CLOSE(res.psi_d, res.psi_g, 1e-9);
}

BOOST_AUTO_TEST_CASE(WithoutCurvature_EqualHeights) {
    RefractionModelWithoutCurvature model;
    // Если высоты равны, psi_d = asin(0) = 0, d = R
    auto res = model.calculate(500.0, 500.0, 5000.0);
    BOOST_CHECK_SMALL(res.psi_d, 1e-9);
    BOOST_CHECK_CLOSE(res.d, 5000.0, 1e-9);
}

// ─────────────────────────────────────────────────────────────
// Тесты для RefractionModelWithCurvature и сеттера k
// ─────────────────────────────────────────────────────────────

BOOST_AUTO_TEST_CASE(WithCurvature_SetK_GetK) {
    RefractionModelWithCurvature model;
    model.setK(4.0 / 3.0);
    BOOST_CHECK_CLOSE(model.getK(), 4.0 / 3.0, 1e-9);

    model.setK(1.5);
    BOOST_CHECK_CLOSE(model.getK(), 1.5, 1e-9);
}

BOOST_AUTO_TEST_CASE(WithCurvature_SymmetricHeights) {
    RefractionModelWithCurvature model;
    model.setK(4.0 / 3.0);

    // При h_a == h_s: psi_d = -psi_g, d > 0
    auto res = model.calculate(1000.0, 1000.0, 5000.0);
    BOOST_CHECK(res.d > 0.0);
    BOOST_CHECK_CLOSE(res.psi_d, -res.psi_g, 1e-6);
}

BOOST_AUTO_TEST_CASE(WithCurvature_DynamicK_ChangesResult) {
    RefractionModelWithCurvature model;

    // Одна и та же модель, но разные k — результаты должны отличаться
    model.setK(4.0 / 3.0);
    auto r1 = model.calculate(1000.0, 1000.0, 2.1 * 1000.0);

    model.setK(1.0);
    auto r2 = model.calculate(1000.0, 1000.0, 2.1 * 1000.0);

    BOOST_CHECK(r1.d > 0.0);
    BOOST_CHECK(r2.d > 0.0);
    BOOST_CHECK(std::abs(r1.d - r2.d) > 1e-6);   // значения должны отличаться
}

// ─────────────────────────────────────────────────────────────
// Тесты для пресетов K43 и K1
// ─────────────────────────────────────────────────────────────

BOOST_AUTO_TEST_CASE(K43Preset_HasCorrectK) {
    RefractionModelK43 model;
    BOOST_CHECK_CLOSE(model.getK(), 4.0 / 3.0, 1e-9);
}

BOOST_AUTO_TEST_CASE(K1Preset_HasCorrectK) {
    RefractionModelK1 model;
    BOOST_CHECK_CLOSE(model.getK(), 1.0, 1e-9);
}

BOOST_AUTO_TEST_CASE(K43AndK1_DifferInResult) {
    RefractionModelK43 m43;
    RefractionModelK1  m1;

    double h_a = 1274.0;
    double h_s = 1274.0;
    double R   = 2.1 * 1274.0;

    auto r43 = m43.calculate(h_a, h_s, R);
    auto r1  = m1.calculate(h_a, h_s, R);

    // Оба результата положительные и отличаются
    BOOST_CHECK(r43.d > 0.0);
    BOOST_CHECK(r1.d  > 0.0);
    BOOST_CHECK(std::abs(r43.d - r1.d) > 1e-6);
}