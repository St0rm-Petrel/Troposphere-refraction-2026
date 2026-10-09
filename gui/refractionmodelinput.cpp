#include "refractionmodelinput.h"
#include "ui_refractionmodelinput.h"

RefractionModelInput::RefractionModelInput(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RefractionModelInput)
{
    ui->setupUi(this);
}

RefractionModelInput::~RefractionModelInput()
{
    delete ui;
}
