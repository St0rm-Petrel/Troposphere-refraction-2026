#include "../lib/angle_comp_calculator.h"
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

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_angle_comp)

#ifdef TEST_PLOTS

BOOST_AUTO_TEST_CASE(plot_angle_diff_vs_height, *utf::label("plot")) {
  int argc = 1;
  char arg1[] = "tests";
  char *argv[] = {arg1, nullptr};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.resize(900, 700);
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.legend->setVisible(true);
  customPlot.legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
  QFont legendFont = QApplication::font();
  legendFont.setPointSize(10);
  customPlot.legend->setFont(legendFont);

  const std::vector<double> psi_g_values_deg = {30.0, 10.0, 3.0, 1.0, 0.3, 0.1};
  const std::vector<double> Ns_values = {250.0, 313.0, 400.0};

  const int N_points = 500;
  const double h_min = 0.0;
  const double h_max = 30000.0;
  const double h_s = 0.0;

  const std::vector<QColor> colors = {Qt::blue, Qt::red, Qt::darkGreen};
  const std::vector<double> line_widths = {2.5, 2.5, 2.0, 2.0, 1.5, 1.5};
  const std::vector<Qt::PenStyle> line_styles = {Qt::SolidLine, Qt::SolidLine,
                                                 Qt::DashLine,  Qt::DashLine,
                                                 Qt::DotLine,   Qt::DotLine};

  int graph_idx = 0;
  const double pi = std::acos(-1.0);

  for (size_t i = 0; i < Ns_values.size(); ++i) {
    double N_s = Ns_values[i];
    QColor color = colors[i];

    AngleComputationalCalculator calc(N_s, h_s);

    for (size_t j = 0; j < psi_g_values_deg.size(); ++j) {
      double psi_g_deg = psi_g_values_deg[j];
      double psi_g_rad = psi_g_deg * pi / 180.0;

      QVector<double> x(N_points), y(N_points);
      for (int k = 0; k < N_points; ++k) {
        double h_a = h_min + k * (h_max - h_min) / (N_points - 1);

        y[k] = h_a / 1000.0;

        double psi_d_rad = calc.calculate_d_and_psi_d(psi_g_rad, h_s, h_a, N_s);
        double psi_d_deg = psi_d_rad * 180.0 / pi;

        x[k] = std::abs(psi_d_deg - psi_g_deg);
      }

      customPlot.addGraph();
      customPlot.graph(graph_idx)->setData(x, y);

      QPen pen(color);
      pen.setWidthF(line_widths[j]);
      pen.setStyle(line_styles[j]);
      customPlot.graph(graph_idx)->setPen(pen);

      QString name =
          QString("Ns=%1, \u03C8_g=%2\u00B0").arg(N_s).arg(psi_g_deg);
      customPlot.graph(graph_idx)->setName(name);
      graph_idx++;
    }
  }

  customPlot.xAxis->setLabel("|\u03C8_d - \u03C8_g|, degrees");
  customPlot.yAxis->setLabel("Height, km");

  customPlot.xAxis->grid()->setVisible(true);
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  customPlot.xAxis->setRange(0.0, 6.0);
  customPlot.yAxis->setRange(0.0, 30.0);

  QSharedPointer<QCPAxisTickerFixed> xTicker(new QCPAxisTickerFixed);
  xTicker->setTickStep(1.0);
  xTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
  customPlot.xAxis->setTicker(xTicker);

  QSharedPointer<QCPAxisTickerFixed> yTicker(new QCPAxisTickerFixed);
  yTicker->setTickStep(5.0);
  yTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
  customPlot.yAxis->setTicker(yTicker);

  customPlot.setWindowTitle(
      "Angle Difference |ψ_d - ψ_g| vs Height (Computational)");
  customPlot.show();

  a.exec();
}

#endif

BOOST_AUTO_TEST_SUITE_END()