#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // рассчитать
    connect(ui->count_button, &QPushButton::clicked,
            this, &MainWindow::Calculate);

    // тестовые точки графика

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
