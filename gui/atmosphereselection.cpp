#include "atmosphereselection.h"
#include "ui_atmosphereselection.h"

AtmosphereSelection::AtmosphereSelection(QWidget *parent)
    : QWidget(parent), ui(new Ui::AtmosphereSelection)
{
    ui->setupUi(this);


}

AtmosphereSelection::~AtmosphereSelection()
{
    delete ui;
}

