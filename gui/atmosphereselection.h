#ifndef ATMOSPHERESELECTION_H
#define ATMOSPHERESELECTION_H

#include <QWidget>

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


private:
    Ui::AtmosphereSelection *ui;
};

#endif // ATMOSPHERESELECTION_H
