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

int AtmosphereSelection::get_exp_index() const
{
    return ui->exp_comboBox->currentIndex();
}

int AtmosphereSelection::get_gost_index() const
{
    return ui->int_model_combo->currentIndex();
}

double AtmosphereSelection::get_Ns_3() const { return ui->ns_exp_input_3->value(); }
double AtmosphereSelection::get_h_3() const { return ui->h_exp_input_3->value(); }

double AtmosphereSelection::get_Ns_10() const { return ui->ns_exp_input_10->value(); }
double AtmosphereSelection::get_h_10() const { return ui->h_exp_input_10->value(); }

double AtmosphereSelection::get_Ns_15() const { return ui->ns_exp_input_15->value(); }
double AtmosphereSelection::get_h_15() const { return ui->h_exp_input_15->value(); }

double AtmosphereSelection::get_Ns_seg() const { return ui->ns_seg_input->value(); }
double AtmosphereSelection::get_h_seg() const { return ui->h_seg_input->value(); }
double AtmosphereSelection::get_N1_seg() const { return ui->N1_seg_input->value(); }

double AtmosphereSelection::get_h_gost_1() const { return ui->h_exp_input_1->value(); }
double AtmosphereSelection::get_h_gost_2() const { return ui->h_exp_input_2->value(); }

AtmModel *AtmosphereSelection::create_atmospheric_model()
{
    int index = get_atm_index();
    if (index == 0)
    {
        int index_exp = get_exp_index();
        switch (index_exp)
        {
        case 0:
            return new ExpAtmModel3k(get_Ns_3(), get_h_3());
        case 1:
            return new ExpAtmModel10k(get_Ns_10(), get_h_10());
        case 2:
            return new ExpAtmModel15k(get_Ns_15(), get_h_15());
            /*
        case 3:
            */
        default:
            return new ExpAtmModel15k(get_Ns_15(), get_h_15());
        }
    }

    else if (index == 1)
    {
        return new SegAtmModel(get_Ns_seg(), get_h_seg(), get_N1_seg());
    }
    /*
    else if (index == 2)
    {
        int index_gost = get_gost_index();
        switch (index_gost)
        {
        case 0:

            return new GOSTAtmModel(); //аргументы - vector
        case 1:

            return new GOSTAtmModel();

        default:
            return new GOSTAtmModel();
        }
    }*/
}
