#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // рассчитать
    connect(ui->count_button, &QPushButton::clicked,
            this, &MainWindow::CalculateButton);
}

void MainWindow::CalculateButton()
{
    int refr_index = ui->dir_refr_sel->get_refr_index();
    int atm_index = ui->dir_atm_sel->get_atm_index();
    int refr_index_rev = ui->rev_refr_sel->get_refr_index();
    int atm_index_rev = ui->rev_atm_sel->get_atm_index();

    // параметры геометрии
    double h_a = ui->dir_geom_input->get_h_a();
    double h_s = ui->dir_geom_input->get_h_s();
    double r = ui->dir_geom_input->get_r();

    // параметры атмосферы - пока для экп.модели
    double H = 12192.0;

    Calculate calc;
    RefractionModel *refrModel = ui->dir_refr_sel->create_refraction_model();
    AtmModel *atmModel = ui->dir_atm_sel->create_atmospheric_model();
    CalculatedResult res = calc.calculate_direct(h_a, h_s, r, refrModel, atmModel);

    delete refrModel;
    delete atmModel;

    // обратная задача

    CalculatedResult res_rev;
    res_rev.psi_d = res.psi_d + 1.0;
    res_rev.psi_g = res.psi_g;
    res_rev.d = res.d + 10;

    // параметры геометрии (для графика)
    double x = res_rev.d * std::cos(res_rev.psi_d * M_PI / 180.0);
    double y = res_rev.d * std::sin(res_rev.psi_d * M_PI / 180.0);
    double h_s_rev = h_a + y;
    double r_rev = res_rev.d;

    // Calculate calc;
    RefractionModel *refrModelRev = ui->rev_refr_sel->create_refraction_model();
    AtmModel *atmModelRev = ui->rev_atm_sel->create_atmospheric_model();
    // CalculatedResult res = calc.calculate_direct(h_a, h_s, r, refrModel, atmModel);

    draw_plot(r, h_a, h_s, r_rev, h_a, h_s_rev);

    delete refrModelRev;
    delete atmModelRev;

    cout_results(res, res_rev);
};

void MainWindow::cout_results(const CalculatedResult &res, const CalculatedResult &res_rev)
{
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::number(res.psi_d)));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem(QString::number(res.psi_g)));
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem(QString::number(res.d)));

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(res_rev.psi_d)));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem(QString::number(res_rev.psi_g)));
    ui->tableWidget->setItem(2, 0, new QTableWidgetItem(QString::number(res_rev.d)));

    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(abs(res.psi_d-res_rev.psi_d))));
    ui->tableWidget->setItem(1, 2, new QTableWidgetItem(QString::number(abs(res.psi_g-res_rev.psi_g))));
    ui->tableWidget->setItem(2, 2, new QTableWidgetItem(QString::number(abs(res.d-res_rev.d))));
}

void MainWindow::draw_ray(double x_start, double y_start, double x_end, double y_end, QColor color)
{
    double k = 0.2; // какую часть линии рисовать

    double stop_x = x_start + k * (x_end - x_start);
    double stop_y = y_start + k * (y_end - y_start);

    QCPItemLine *ray1 = new QCPItemLine(ui->graph);
    ray1->start->setCoords(x_start, y_start);
    ray1->end->setCoords(stop_x, stop_y);

    // цвета
    QPen pen;
    pen.setWidth(2);
    pen.setColor(color);
    ray1->setPen(pen);

    ray1->setHead(QCPLineEnding::esSpikeArrow);
}

void MainWindow::draw_point(double x, double y, QColor color)
{
    double size = 10.0;

    QCPItemEllipse *point = new QCPItemEllipse(ui->graph);
    point->topLeft->setCoords(x - size, y + size);
    point->bottomRight->setCoords(x + size, y - size);

    QPen pen;
    pen.setColor(color);
    pen.setWidth(1);
    point->setPen(pen);

    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    point->setBrush(brush);
}

void MainWindow::draw_plot(double r_p, double ha_p, double hs_p, double r_r, double ha_r, double hs_r)
{
    ui->graph->clearItems();
    // получить данные координат
    double x1 = 0.0;
    double y1 = ha_p;
    double dh = (hs_p - ha_p);
    double dx = std::sqrt(std::abs(r_p * r_p - dh * dh));
    double x2 = dx;
    double y2 = hs_p;
    draw_ray(x1, y1, x2, y2, Qt::red); // луч РЛС прямая
    draw_ray(x2, y2, x1, y1, Qt::red); // луч цель прямая
    draw_point(x1, y1, Qt::black);
    draw_point(x2, y2, Qt::black);

    // для обратной пока примерные:
    double x1_r = x1;
    double y1_r = y1;
    double dh_r = (hs_r - ha_r);
    double dx_r = std::sqrt(std::abs(r_r * r_r - dh_r * dh_r));
    double x2_r = dx_r;
    double y2_r = hs_r;
    draw_ray(x1_r, y1_r, x2_r, y2_r, Qt::blue); // луч РЛС обратная
    draw_ray(x2_r, y2_r, x1_r, y1_r, Qt::blue); // луч цель обратная
    draw_point(x2_r, y2_r, Qt::black);

    // оси
    double min_x = std::min({x1, x2, x1_r, x2_r});
    double max_x = std::max({x1, x2, x1_r, x2_r});
    double min_y = std::min({y1, y2, y1_r, y2_r});
    double max_y = std::max({y1, y2, y1_r, y2_r});
    ui->graph->xAxis->setRange(min_x - 100, max_x + 100);
    ui->graph->yAxis->setRange(min_y - 100, max_y + 100);

    ui->graph->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
