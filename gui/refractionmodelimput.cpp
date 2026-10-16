#include "refractionmodelimput.h"
#include "ui_refractionmodelimput.h"

RefractionModelImput::RefractionModelImput(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RefractionModelImput)
{
    ui->setupUi(this);
}

RefractionModelImput::~RefractionModelImput()
{
    delete ui;
}
