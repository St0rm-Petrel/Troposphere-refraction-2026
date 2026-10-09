#include "geometryinput.h"
#include "ui_geometryinput.h"

GeometryInput::GeometryInput(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeometryInput)
{
    ui->setupUi(this);
}

GeometryInput::~GeometryInput()
{
    delete ui;
}
