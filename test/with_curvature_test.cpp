#include <boost/test/unit_test.hpp>
#include "refraction_model.h"
#include "exp_atm_model_descend.h"
#include <cmath>

#include <QApplication>

#include "qcustomplot.h"

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(WithCurvature)

BOOST_AUTO_TEST_CASE(DefaultKValues) {
    // У базового класса k = 1.0 по умолчанию
    RefractionModelK43 m43;
    RefractionModelK1  m1;

    double h_a = 1000.0;
    double h_s = 1000.0;
    double R   = 2.1 * 1000.0;

    BOOST_CHECK_CLOSE(m43.K(h_a, h_s, R), 4.0 / 3.0, 1e-9);
    BOOST_CHECK_CLOSE(m1.K(h_a, h_s, R),  1.0,       1e-9);
}

BOOST_AUTO_TEST_CASE(SymmetricHeights) {
    RefractionModelK1 model;

    // При h_a == h_s: psi_d = -psi_g, d > 0
    auto res = model.calculate(1000.0, 1000.0, 5000.0);
    BOOST_CHECK(res.d > 0.0);
    BOOST_CHECK_CLOSE(res.psi_d, -res.psi_g, 1e-6);
}

BOOST_AUTO_TEST_CASE(DifferentK_DifferentResults) {
    RefractionModelK43 m43;
    RefractionModelK1  m1;

    double h_a = 1000.0;
    double h_s = 1000.0;
    double R   = 2.1 * 1000.0;

    auto r43 = m43.calculate(h_a, h_s, R);
    auto r1  = m1.calculate(h_a, h_s, R);

    BOOST_CHECK(r43.d > 0.0);
    BOOST_CHECK(r1.d  > 0.0);
    BOOST_CHECK(std::abs(r43.d - r1.d) > 1e-6);
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_analytical_kp_comparison, *utf::label("plot")) {
    // Plot 2.33 from booklet
    // Note: differs from booklet
    // Booklet assumes in models cos(phi_g) = 1
    // We use more accurate models.
    int argc = 1;
    char *argv[] = {"tests"};
    QApplication a(argc, argv);

    QCustomPlot customPlot = QCustomPlot();
    const int N = 1000;
    const double h_min = 300, h_max = 15000;
    QVector<double> x(N), y(N);
    ExpAtmModel15k atmosphere(313, 0.0);
    RefractionModelAnaliticalType1 model1(atmosphere);
    RefractionModelAnaliticalType2 model2(atmosphere);

    std::vector<RefractionModelWithCurvature*> models {&model1, &model2};
    std::vector<QColor> colors {Qt::blue, Qt::green};
    for(int last_graph = 0; last_graph < 2; last_graph++) {
        customPlot.addGraph();
        customPlot.graph(last_graph)->setPen(QPen(colors[last_graph]));
        for (int i = 0; i < N; ++i) {
            y[i] = h_min + i * (h_max - h_min) / (N - 1);
            x[i] = models[last_graph]->K(y[i], 0.0, 1.2*h_max);
        }
        // pass data points to graphs:
        customPlot.graph(last_graph)->setData(x, y);
        // let the ranges scale themselves so graph 0 fits perfectly in the visible
        // area:
        customPlot.graph(last_graph)->rescaleAxes();
    }
    // make y axis logarithmic
    customPlot.yAxis->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    customPlot.yAxis->setTicker(logTicker);

    customPlot.yAxis->setRange(h_min, 30000);
    customPlot.xAxis->setRange(1.05, 1.40);

    // add labels
    customPlot.xAxis->setLabel("k_avg");
    customPlot.yAxis->setLabel("Height, m");
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
    // graphs by clicking:
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);

    customPlot.show();
    customPlot.resize(640, 480);

    a.exec();
}
#endif

BOOST_AUTO_TEST_SUITE_END()
