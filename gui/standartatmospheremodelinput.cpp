#include "standartatmospheremodelinput.h"
#include "ui_standartatmospheremodelinput.h"

StandartAtmosphereModelInput::StandartAtmosphereModelInput(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StandartAtmosphereModelInput)
{
    ui->setupUi(this);
}

StandartAtmosphereModelInput::~StandartAtmosphereModelInput()
{
    delete ui;
}
