#include "refractioninput.h"
#include "ui_refractioninput.h"

RefractionInput::RefractionInput(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RefractionInput)
{
    ui->setupUi(this);

}

RefractionInput::~RefractionInput()
{
    delete ui;
}

void RefractionInput::setRefractionPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

