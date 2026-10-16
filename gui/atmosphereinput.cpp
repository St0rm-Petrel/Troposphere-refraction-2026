#include "atmosphereinput.h"
#include "ui_atmosphereinput.h"

AtmosphereInput::AtmosphereInput(QWidget *parent)
    : QWidget(parent), ui(new Ui::AtmosphereInput)
{
    ui->setupUi(this);

}

AtmosphereInput::~AtmosphereInput()
{
    delete ui;
}

void AtmosphereInput::setAtmospherePage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

