#ifndef ATMOSPHERESELECTION_H
#define ATMOSPHERESELECTION_H

#include <QWidget>
#include "../lib/atm_model.h"
#include "../lib/exp_atm_model.h"
#include "../lib/seg_atm_model.h"
#include "../lib/gost_atm_model.h"
#include "../lib/exp_atm_model_descend.h"

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
    int get_exp_index() const;
    int get_gost_index() const;

    double get_Ns_3() const;
    double get_h_3() const;
    double get_Ns_10() const;
    double get_h_10() const;
    double get_Ns_15() const;
    double get_h_15() const;
    double get_Ns_seg() const;
    double get_h_seg() const;
    double get_N1_seg() const;
    double get_h_gost_1() const;
    double get_h_gost_2() const;

    AtmModel *create_atmospheric_model();

private:
    Ui::AtmosphereSelection *ui;
};

#endif // ATMOSPHERESELECTION_H
