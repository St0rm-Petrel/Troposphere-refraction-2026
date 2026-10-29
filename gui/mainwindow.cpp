#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // рассчитать
    connect(ui->count_button, &QPushButton::clicked,
            this, &MainWindow::Calculate);

    connect(ui->reverse_count_button, &QPushButton::clicked,
            this, &MainWindow::CalculateRev);
}

MainWindow::~MainWindow()
{
    delete ui;
}
