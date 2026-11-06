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

int AtmosphereSelection::get_atm_index() const
{
    return ui->dir_atm_combo->currentIndex();
}

double AtmosphereSelection::get_Ns() const {return ui->ns_exp_input_15->value();}
double AtmosphereSelection::get_h() const {return ui->h_exp_input_15->value();}
double AtmosphereSelection::get_N1() const {return ui->N1_exp_input_15->value();}

AtmModel *AtmosphereSelection::create_atmospheric_model(int index, double N_s, double h_s, double H)
{
    switch (index)
    {
    case 0:
        return new ExpAtmModel15k(N_s, h_s);
    /*case 1:
        return new SegAtmModel();
    case 2:
        return new GOSTAtmModel();
*/
    default:
        return new ExpAtmModel15k(N_s, h_s);
    }
}
