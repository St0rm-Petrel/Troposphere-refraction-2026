#ifndef INTEGRALATMOSHEREMODELINPUT_H
#define INTEGRALATMOSHEREMODELINPUT_H

#include <QWidget>

namespace Ui {
class IntegralAtmosphereModelInput;
}

class IntegralAtmosphereModelInput : public QWidget
{
    Q_OBJECT

public:
    explicit IntegralAtmosphereModelInput(QWidget *parent = nullptr);
    ~IntegralAtmosphereModelInput();

private:
    Ui::IntegralAtmosphereModelInput *ui;
};

#endif // INTEGRALALMOSPHEREMODELINPUT_H

