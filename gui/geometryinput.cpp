#include "geometryinput.h"
#include "ui_geometryinput.h"

GeometryInput::GeometryInput(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeometryInput)
{
    ui->setupUi(this);
}

double GeometryInput::get_h_a() const { return ui->rev_ha->value(); }
double GeometryInput::get_h_s() const { return ui->rev_hs->value(); }
double GeometryInput::get_r() const { return ui->rev_r->value(); }

GeometryInput::~GeometryInput()
{
    delete ui;
}
