#include "../lib/refraction_model.h"

#include <QApplication>

#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_constant_k_models)

BOOST_AUTO_TEST_CASE(creation) {
    RefractionModelK1  m1;
    RefractionModelK43 m43;

    //cout << "k1  = " << m1.count_d(1274.0, 1274.0, 2.1 * 1274.0)  << "\n";
    //std::cout << "k43 = " << m43.count_d(200.0, 200.0, 10.770)          << "\n";
    return;
}

BOOST_AUTO_TEST_SUITE_END()
