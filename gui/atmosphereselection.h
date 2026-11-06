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
    int get_atm_index() const;
    double get_Ns() const;
    double get_h() const;
    double get_N1() const;
    AtmModel *create_atmospheric_model();
    
private:
    Ui::AtmosphereSelection *ui;
};

#endif // ATMOSPHERESELECTION_H
