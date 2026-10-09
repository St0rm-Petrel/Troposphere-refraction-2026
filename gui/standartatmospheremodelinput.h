#ifndef STANDARTATMOSPHEREMODELINPUT_H
#define STANDARTATMOSPHEREMODELINPUT_H

#include <QWidget>

namespace Ui {
class StandartAtmosphereModelInput;
}

class StandartAtmosphereModelInput : public QWidget
{
    Q_OBJECT

public:
    explicit StandartAtmosphereModelInput(QWidget *parent = nullptr);
    ~StandartAtmosphereModelInput();

private:
    Ui::StandartAtmosphereModelInput *ui;
};

#endif // STANDARTATMOSPHEREMODELINPUT_H
