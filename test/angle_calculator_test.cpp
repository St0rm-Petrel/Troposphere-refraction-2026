#include "../lib/angle_diff_calculator.h"
#include "../lib/seg_atm_model.h"

#include "qcustomplot.h"
#include <QApplication>

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#include <QString>
#include <cmath>
#include <vector>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

namespace {
class TestAngleCalculator {
public:
  double integral_hs_ha(double h_s, double h_a, double N_s) {
    double h_curr = h_s;
    double result = 0.0;
    const double step_size = 100.0;

    while (h_curr < h_a) {
      double step = step_size;
      if ((h_a - h_curr) < step) {
        step = h_a - h_curr;
      }
      SegAtmModel model(N_s, h_curr);
      double n_max = (model.N_h(h_curr) * 1e-6) + 1.0;
      double n_min = (model.N_h(h_curr + step) * 1e-6) + 1.0;

      double dn = n_min - n_max;
      result += (2.0 / (n_max + n_min)) * dn;
      h_curr += step;
    }
    return result;
  }

  // Переименованный метод: вычисляет ψ_d из ψ_g напрямую
  double calculate_psi_d_from_psi_g(double psi_g, double h_s, double h_a,
                                    double N_s) {
    double integral_val = integral_hs_ha(h_s, h_a, N_s);

    constexpr double Re = 6371000.0;

    double cospsi_d =
        std::cos(psi_g) *
        std::exp(-(std::log((Re + h_a) / (Re + h_s)) + integral_val));

    if (cospsi_d > 1.0)
      cospsi_d = 1.0;
    if (cospsi_d < -1.0)
      cospsi_d = -1.0;

    return std::acos(cospsi_d);
  }
};
} // namespace

BOOST_AUTO_TEST_SUITE(test_angle_diff)

#ifdef TEST_PLOTS

BOOST_AUTO_TEST_CASE(plot_angle_diff_vs_height, *utf::label("plot")) {
  int argc = 1;
  const char *argv[] = {"tests"};
  QApplication a(argc, const_cast<char **>(argv));

  QCustomPlot customPlot;
  customPlot.resize(900, 700);

  customPlot.legend->setVisible(true);
  customPlot.legend->setBrush(QBrush(QColor(255, 255, 255, 230)));

  QFont legendFont = QApplication::font();
  legendFont.setPointSize(10);
  customPlot.legend->setFont(legendFont);

  const std::vector<double> Ns_values = {250, 313, 400};
  const std::vector<double> psi_g_values_deg = {30, 10, 3, 1, 0.3, 0.1};

  const int N = 500;
  const double h_min = 0.0, h_max = 15000.0;
  const double h_s = 0.0; // Объявлено здесь

  const std::vector<QColor> colors = {Qt::blue, Qt::red, Qt::darkGreen};
  const std::vector<double> line_widths = {2.0, 2.0, 1.5, 1.5, 1.0, 1.0};
  const std::vector<Qt::PenStyle> line_styles = {Qt::SolidLine, Qt::SolidLine,
                                                 Qt::SolidLine, Qt::DashLine,
                                                 Qt::DotLine,   Qt::DotLine};

  TestAngleCalculator calc; // Объявлено здесь
  int graph_idx = 0;
  const double pi = std::acos(-1.0);

  for (size_t i = 0; i < Ns_values.size(); ++i) {
    double N_s = Ns_values[i];
    QColor color = colors[i];

    for (size_t j = 0; j < psi_g_values_deg.size(); ++j) {
      double psi_g_rad = psi_g_values_deg[j] * pi / 180.0;

      QVector<double> x(N), y(N);
      for (int k = 0; k < N; ++k) {
        double h_a = h_min + k * (h_max - h_min) / (N - 1);
        y[k] = h_a;

        // Прямой вызов без бинарного поиска
        double psi_d_rad =
            calc.calculate_psi_d_from_psi_g(psi_g_rad, h_s, h_a, N_s);
        x[k] = std::abs(psi_d_rad - psi_g_rad) * 180.0 / pi;
      }

      customPlot.addGraph();
      customPlot.graph(graph_idx)->setData(x, y);

      QPen pen(color);
      pen.setWidthF(line_widths[j]);
      pen.setStyle(line_styles[j]);
      customPlot.graph(graph_idx)->setPen(pen);

      QString name =
          QString("Ns=%1, \\psi_g=%2\\260").arg(N_s).arg(psi_g_values_deg[j]);
      customPlot.graph(graph_idx)->setName(name);
      graph_idx++;
    }
  }

  customPlot.xAxis->setLabel("|\\psi_d - \\psi_g|, degrees");
  customPlot.yAxis->setLabel("Height, m");
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  customPlot.graph(0)->rescaleAxes();
  customPlot.xAxis->setRangeLower(0.0);
  customPlot.xAxis->setRangeUpper(customPlot.xAxis->range().upper * 1.1);

  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  a.exec();
}

#endif

BOOST_AUTO_TEST_SUITE_END()
