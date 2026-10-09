#include "integralatmospheremodelinput.h"
#include "ui_integralatmospheremodelinput.h"

IntegralAtmosphereModelInput::IntegralAtmosphereModelInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntegralAtmosphereModelInput)
{
    ui->setupUi(this);
}

IntegralAtmosphereModelInput::~IntegralAtmosphereModelInput()
{
    delete ui;
}
