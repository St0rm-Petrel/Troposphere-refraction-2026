#ifndef REFRACTIONSELECTION_H
#define REFRACTIONSELECTION_H

#include <QWidget>
#include "refraction_model.h"

namespace Ui
{
    class RefractionSelection;
}

class RefractionSelection : public QWidget
{
    Q_OBJECT

public:
    explicit RefractionSelection(QWidget *parent = nullptr);
    RefractionModel *create_refraction_model();
    int get_refr_index() const;
    ~RefractionSelection();

private:
    Ui::RefractionSelection *ui;
};

#endif // REFRACTIONSELECTION_H
