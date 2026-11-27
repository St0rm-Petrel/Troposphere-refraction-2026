#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculate.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void draw_plot(double h_a,
                   double h_s,
                   double psi_d,
                   double psi_g,
                   double d,
                   double R,
                   QColor color);
    void draw_ray(double x_start, double y_start, double x_end, double y_end, QColor color);
    void draw_point(double x, double y, QColor color);
    void cout_results(const CalculatedResult &res, const CalculatedResult &res_rev);

private slots:
    void CalculateButton();
};
#endif // MAINWINDOW_H
