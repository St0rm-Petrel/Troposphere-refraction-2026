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

AtmModel *AtmosphereSelection::create_atmospheric_model()
{
    int index = get_atm_index();
    double N_s = get_Ns();
    double h_s = get_h();

    switch (index)
    {
    case 0:
        return new ExpAtmModel15k(N_s, h_s);
    /*case 1:
        return new SegAtmModel(N_s, h_s);
    case 2:
        return new GOSTAtmModel(N_s, h_s);
*/
    default:
        return new ExpAtmModel15k(N_s, h_s);
    }
}
