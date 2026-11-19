#include "seg_atm_model.h"
#include "qcustomplot.h"
#include <QApplication>
#include <QColor>
#include <QPen>
#include <QSharedPointer>
#include <QString>
#include <QVector>
#include <cmath>
#include <vector>

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
  BOOST_TEST(model.N_h(10.0) == 300.0, tt::tolerance(1e-6));
}

BOOST_FIXTURE_TEST_CASE(Nh_at_hs_plus_1000m, SegAtmFixture1000) {
  double delta_N = -0.00732 * std::exp(0.005577 * 300.0);
  double expected = 300.0 + 1000.0 * delta_N;
  BOOST_TEST(model.N_h(2000.0) == expected, tt::tolerance(1e-6));
}

BOOST_FIXTURE_TEST_CASE(Nh_at_9000m, SegAtmFixture1000) {
  double delta_N = -0.00732 * std::exp(0.005577 * 300.0);
  double N_1km = 300.0 + 1000.0 * delta_N;

  double H = (8000.0 - 1000.0) / std::log(N_1km / 105.0);
  double expected = N_1km * std::exp(-(9000.0 - 1000.0 - 1000.0) / H);

  BOOST_TEST(model.N_h(9000.0) == expected, tt::tolerance(1e-6));
}

BOOST_FIXTURE_TEST_CASE(h_9000m_continuity, SegAtmFixture1000) {
  BOOST_TEST(model.N_h(9000.0 + 1e-6) == model.N_h(9000.0 - 1e-6),
             tt::tolerance(1e-3));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_refractive_index_profile, *utf::label("plot")) {
  int argc = 1;
  char *argv[] = {"tests"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.xAxis->setLabel("Refractive index N, N-units");
  customPlot.yAxis->setLabel("Height, km");

  customPlot.xAxis->setRange(0, 450);
  customPlot.yAxis->setRange(0, 15);

  customPlot.xAxis->grid()->setVisible(true);
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  customPlot.legend->setVisible(true);
  customPlot.legend->setFont(QFont("Helvetica", 10));

  std::vector<double> N_s_values = {250.0, 313.0, 400.0};
  std::vector<QColor> colors = {Qt::blue, Qt::red, Qt::darkGreen};

  const int N_points = 1000;
  const double h_min = 0.0;
  const double h_max = 15000.0;
  const double h_s = 0.0;

  for (size_t i = 0; i < N_s_values.size(); ++i) {
    double current_N_s = N_s_values[i];
    SegAtmModel model(current_N_s, h_s);

    QVector<double> x(N_points), y(N_points);

    for (int j = 0; j < N_points; ++j) {
      double h = h_min + j * (h_max - h_min) / (N_points - 1);
      double N_h = model.N_h(h);

      x[j] = N_h;
      y[j] = h / 1000.0;
    }

    customPlot.addGraph();
    customPlot.graph(i)->setPen(QPen(colors[i], 2));
    customPlot.graph(i)->setName(QString("N_s = %1").arg(current_N_s));
    customPlot.graph(i)->setData(x, y);
  }

  QSharedPointer<QCPAxisTickerFixed> xTicker(new QCPAxisTickerFixed);
  xTicker->setTickStep(50.0);
  xTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
  customPlot.xAxis->setTicker(xTicker);

  QSharedPointer<QCPAxisTickerFixed> yTicker(new QCPAxisTickerFixed);
  yTicker->setTickStep(3.0);
  yTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
  customPlot.yAxis->setTicker(yTicker);

  customPlot.resize(800, 600);
  customPlot.setWindowTitle("Refractive Index N vs Height (Segmented Model)");
  customPlot.show();

  a.exec();
}
#endif

BOOST_AUTO_TEST_SUITE_END()