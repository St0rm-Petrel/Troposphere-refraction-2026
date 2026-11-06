#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // рассчитать
    connect(ui->count_button, &QPushButton::clicked,
            this, &MainWindow::Calculate);

    draw_plot();
}

void MainWindow::CalculateButton()
{
    int refr_index = ui->dir_refr_sel->get_refr_index();
    int atm_index = ui->dir_atm_sel->get_atm_index();

    //параметры геометрии
    double h_a = ui->dir_geom_input->get_h_a();
    double h_s = ui->dir_geom_input->get_h_s();
    double r = ui->dir_geom_input->get_r();

    //параметры атмосферы - пока для экп.модели
    double N_s = ui->dir_atm_sel->get_Ns();
    double H   = 12192.0;

    Calculate calc;
    RefractionModel *refrModel = ui->dir_refr_sel->create_refraction_model(refr_index);
    AtmModel *atmModel = ui->dir_atm_sel->create_atmospheric_model(atm_index, N_s, h_s, 12192.0);
    CalculationResult res = calc.calculate_direct(h_a, h_s, r, refrModel, atmModel);
    cout_dir_results(res);

    delete refrModel;
    delete atmModel;
}

void MainWindow::cout_dir_results(const CalculationResult &res)
{
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::number(res.psi_d)));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem(QString::number(res.psi_g)));
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem(QString::number(res.d)));
}

void MainWindow::draw_plot()
{

    QVector<double> x = {0, 80, 85};
    QVector<double> y = {0, 30, 25};

    ui->graph->addGraph();
    ui->graph->graph(0)->setData(
        {x[0], x[1]}, {y[0], y[1]});
    ui->graph->graph(0)->setScatterStyle(
    QCPScatterStyle(QCPScatterStyle::ssDisc, 10));

    ui->graph->addGraph();
    ui->graph->graph(1)->setData(
        {x[0], x[2]}, {y[0], y[2]});

    ui->graph->graph(1)->setScatterStyle(
    QCPScatterStyle(QCPScatterStyle::ssDisc, 10));

    ui->graph->xAxis->setRange(-5, 100);
    ui->graph->yAxis->setRange(-5, 45);

    ui->graph->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
