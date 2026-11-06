#ifndef ATMOSPHERESELECTION_H
#define ATMOSPHERESELECTION_H

#include <QWidget>
#include "atm_model.h"
#include "exp_atm_model.h"
#include "seg_atm_model.h"
#include "gost_atm_model.h"
#include "exp_atm_model_descend.h" 


namespace Ui
{
    class AtmosphereSelection;
}

class AtmosphereSelection : public QWidget
{
    Q_OBJECT

public:
    explicit AtmosphereSelection(QWidget *parent = nullptr);
    ~AtmosphereSelection();
    AtmModel *create_atmospheric_model(int index, double N_s, double h_s, double H);
    int get_atm_index() const;
    double get_Ns() const;
    double get_h() const;
    double get_N1() const;

private:
    Ui::AtmosphereSelection *ui;
};

#endif // ATMOSPHERESELECTION_H
