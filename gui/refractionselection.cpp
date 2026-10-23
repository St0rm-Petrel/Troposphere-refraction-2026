#include "refractionselection.h"
#include "ui_refractionselection.h"

RefractionSelection::RefractionSelection(QWidget *parent)
    : QWidget(parent), ui(new Ui::RefractionSelection)
{
    ui->setupUi(this);
}

RefractionSelection::~RefractionSelection()
{
    delete ui;
}

