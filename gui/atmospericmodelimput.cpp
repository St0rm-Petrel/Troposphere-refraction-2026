#include "atmospericmodelimput.h"
#include "ui_atmospericmodelimput.h"

AtmospericModelImput::AtmospericModelImput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AtmospericModelImput)
{
    ui->setupUi(this);
}

AtmospericModelImput::~AtmospericModelImput()
{
    delete ui;
}
