#include "refractionselection.h"
#include "ui_refractionselection.h"
#include "refraction_model.h"

RefractionSelection::RefractionSelection(QWidget *parent)
    : QWidget(parent), ui(new Ui::RefractionSelection)
{
    ui->setupUi(this);
}

RefractionSelection::~RefractionSelection()
{
    delete ui;
}

int RefractionSelection::get_refr_index() const
{
    return ui->rev_ref_combo->currentIndex(); 
}

RefractionModel *RefractionSelection::create_refraction_model(int index)
{
    switch (index)
    {
    case 0:
        return new RefractionModelWithoutCurvature();
        /*
    case 1:
        return new RefractionModelK43();*/
    default:
        return new RefractionModelWithoutCurvature();
    }
}