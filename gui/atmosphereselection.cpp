#include "atmosphereselection.h"
#include "ui_atmosphereselection.h"

AtmosphereSelection::AtmosphereSelection(QWidget *parent)
    : QWidget(parent), ui(new Ui::AtmosphereSelection)
{
    ui->setupUi(this);

    connect(ui->dir_atm_combo,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &AtmosphereSelection::atmosphereChanged);

}

AtmosphereSelection::~AtmosphereSelection()
{
    delete ui;
}

