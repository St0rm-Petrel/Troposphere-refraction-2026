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
    void draw_plot(double r_p, double ha_p, double hs_p);
    void draw_ray(double x_start, double y_start, double x_end, double y_end);
    void cout_dir_results(const CalculatedResult &res);

private slots:
    void CalculateButton();
};
#endif // MAINWINDOW_H
