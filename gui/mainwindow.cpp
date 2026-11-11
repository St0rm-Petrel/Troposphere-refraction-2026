#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    // параметры геометрии
    double h_a = ui->dir_geom_input->get_h_a();
    double h_s = ui->dir_geom_input->get_h_s();
    double r = ui->dir_geom_input->get_r();

    // параметры атмосферы - пока для экп.модели
    double N_s = ui->dir_atm_sel->get_Ns();
    double H = 12192.0;

    Calculate calc;
    RefractionModel *refrModel = ui->dir_refr_sel->create_refraction_model();
    AtmModel *atmModel = ui->dir_atm_sel->create_atmospheric_model();
    CalculatedResult res = calc.calculate_direct(h_a, h_s, r, refrModel, atmModel);
    cout_dir_results(res);

    draw_plot(r, h_a, h_s);

    delete refrModel;
    delete atmModel;
}

void MainWindow::cout_dir_results(const CalculatedResult &res)
{
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::number(res.psi_d)));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem(QString::number(res.psi_g)));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem(QString::number(res.psi_g)));
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem(QString::number(res.d)));
}

void MainWindow::draw_ray(double x_start, double y_start, double x_end, double y_end)
{
    double k = 0.2; // какую часть линии рисовать

    double stop_x = x_start + k * (x_end - x_start);
    double stop_y = y_start + k * (y_end - y_start);

    QCPItemLine *ray1 = new QCPItemLine(ui->graph);
    ray1->start->setCoords(x_start, y_start);
    ray1->end->setCoords(stop_x, stop_y);
    ray1->setHead(QCPLineEnding::esSpikeArrow);
}
void MainWindow::draw_plot(double r_p, double ha_p, double hs_p)
{

    // получить данные координат
    double x1 = 0.0;
    double y1 = ha_p;
    double dh = (hs_p - ha_p);
    double dx = std::sqrt(std::abs(r_p * r_p - dh * dh));
    double x2 = dx;
    double y2 = hs_p;
    draw_ray(x1, y1, x2, y2); // луч РЛС прямая
    draw_ray(x2, y2, x1, y1); // луч цель прямая

    // для обратной пока примерные:
    double x1_r = x1;
    double y1_r = y1;
    double x2_r = dx * 1.05;
    double y2_r = dh * 1.05;
    draw_ray(x1_r, y1_r, x2_r, y2_r); // луч РЛС обратная
    draw_ray(x2_r, y2_r, x1_r, y1_r); // луч цель обратная

    // оси
    double min_x = std::min(x1, x2);
    double max_x = std::max(x1, x2);
    double min_y = std::min(y1, y2);
    double max_y = std::max(y1, y2);
    ui->graph->xAxis->setRange(min_x - 100, max_x + 100);
    ui->graph->yAxis->setRange(min_y - 100, max_y + 100);

    ui->graph->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
