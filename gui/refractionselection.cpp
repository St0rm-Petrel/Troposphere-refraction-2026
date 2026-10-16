#include "refractionselection.h"
#include "ui_refractionselection.h"

RefractionSelection::RefractionSelection(QWidget *parent)
    : QWidget(parent), ui(new Ui::RefractionSelection)
{
    ui->setupUi(this);

    connect(ui->rev_ref_combo,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &RefractionSelection::refractionChanged);
}

RefractionSelection::~RefractionSelection()
{
    delete ui;
}

