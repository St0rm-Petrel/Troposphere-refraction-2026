#include "mainwindow.h"
    #include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->dir_atm_sel, &AtmosphereSelection::atmosphereChanged,
            ui->dir_atm_input, &AtmosphereInput::setAtmospherePage);

    connect(ui->dir_refr_sel, &RefractionSelection::refractionChanged,
            ui->dir_refr_input, &RefractionInput::setRefractionPage);
    
    connect(ui->rev_atm_sel, &AtmosphereSelection::atmosphereChanged,
            ui->rev_atm_input, &AtmosphereInput::setAtmospherePage);

    connect(ui->rev_refr_sel, &RefractionSelection::refractionChanged,
            ui->rev_refr_input, &RefractionInput::setRefractionPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
