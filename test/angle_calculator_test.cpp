#include "../lib/angle_diff_calculator.h" // Укажите правильный путь к вашему заголовку

#include "qcustomplot.h"
#include <QApplication>

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#include <QString>
#include <algorithm>
#include <cmath>
#include <vector>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

#ifdef TEST_PLOTS

// Вспомогательная функция: находит psi_d, который дает целевой psi_g на высоте
// h
double find_psi_d_for_target_psi_g(double target_psi_g_rad, double h_a,
                                   double N_s,
                                   AngleDifferenceCalculator &calc) {
  double h_s = 0.0;
  // Из-за рефракции psi_d и psi_g очень близки. Ищем psi_d в небольшом
  // диапазоне вокруг target_psi_g
  double low = target_psi_g_rad;
  double high = target_psi_g_rad + 0.05; // + ~3 градуса, с запасом

  for (int iter = 0; iter < 30;
       ++iter) { // 30 итераций бинарного поиска дают точность ~1e-9 рад
    double mid = low + (high - low) / 2.0;
    double current_psi_g = calc.calculate_d_and_psi_g(mid, h_s, h_a, N_s);

    if (current_psi_g < target_psi_g_rad) {
      low = mid;
    } else {
      high = mid;
    }
  }
  return low + (high - low) / 2.0;
}

BOOST_AUTO_TEST_CASE(plot_angle_diff_vs_height, *utf::label("plot")) {
  int argc = 1;
  char *argv[] = {"tests"};
  QApplication a(argc, argv);

  QCustomPlot customPlot;
  customPlot.resize(900, 700);

  // Настройка легенды
  customPlot.legend->setVisible(true);
  customPlot.legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
  customPlot.legend->setFontSize(10);

  // Исходные данные из задания
  const std::vector<double> Ns_values = {250, 313, 400};
  const std::vector<double> psi_g_values_deg = {30, 10, 3, 1, 0.3, 0.1};

  const int N = 500; // Количество точек по высоте
  const double h_min = 0.0;
  const double h_max = 15000.0; // 15 км

  // Цвета для разных N_s
  const std::vector<QColor> colors = {Qt::blue, Qt::red, Qt::darkGreen};
  // Толщина и стиль линии для разных psi_g (чтобы график не сливался в кашу)
  const std::vector<double> line_widths = {2.0, 2.0, 1.5, 1.5, 1.0, 1.0};
  const std::vector<Qt::PenStyle> line_styles = {Qt::SolidLine, Qt::SolidLine,
                                                 Qt::SolidLine, Qt::DashLine,
                                                 Qt::DotLine,   Qt::DotLine};

  AngleDifferenceCalculator calc;
  int graph_idx = 0;
  const double pi = std::acos(-1.0);

  for (size_t i = 0; i < Ns_values.size(); ++i) {
    double N_s = Ns_values[i];
    QColor color = colors[i];

    for (size_t j = 0; j < psi_g_values_deg.size(); ++j) {
      double psi_g_deg = psi_g_values_deg[j];
      double psi_g_rad = psi_g_deg * pi / 180.0;

      QVector<double> x(N), y(N);
      for (int k = 0; k < N; ++k) {
        double h_a = h_min + k * (h_max - h_min) / (N - 1);
        y[k] = h_a; // Ось Y: Высота

        // Находим psi_d, соответствующий нашему целевому psi_g на данной высоте
        double psi_d_rad =
            find_psi_d_for_target_psi_g(psi_g_rad, h_a, N_s, calc);

        // Разность углов в градусах
        double diff_deg = std::abs(psi_d_rad - psi_g_rad) * 180.0 / pi;
        x[k] = diff_deg; // Ось X: |psi_d - psi_g|
      }

      customPlot.addGraph();
      customPlot.graph(graph_idx)->setData(x, y);

      QPen pen(color);
      pen.setWidthF(line_widths[j]);
      pen.setStyle(line_styles[j]);

      customPlot.graph(graph_idx)->setPen(pen);

      // Формирование подписи для легенды (символ \260 это градус в Qt)
      QString name = QString("Ns=%1, \\psi_g=%2\\260").arg(N_s).arg(psi_g_deg);
      customPlot.graph(graph_idx)->setName(name);

      graph_idx++;
    }
  }

  // Настройка осей
  customPlot.xAxis->setLabel("|\\psi_d - \\psi_g|, degrees");
  customPlot.yAxis->setLabel("Height, m");

  // Сетка
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);

  // Автоматическое масштабирование
  customPlot.graph(0)->rescaleAxes();
  customPlot.xAxis->setRangeLower(0.0); // Разность не может быть отрицательной
  customPlot.xAxis->setRangeUpper(customPlot.xAxis->range().upper *
                                  1.1); // +10% запаса справа

  // Взаимодействие с мышью
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);

  customPlot.show();
  a.exec();
}

#endif

BOOST_AUTO_TEST_SUITE_END()