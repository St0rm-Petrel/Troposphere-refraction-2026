#ifndef ATMOSPHEREINPUT_H
#define ATMOSPHEREINPUT_H

#include <QWidget>

namespace Ui
{
    class AtmosphereInput;
}

class AtmosphereInput : public QWidget
{
    Q_OBJECT

public:
    explicit AtmosphereInput(QWidget *parent = nullptr);
    ~AtmosphereInput();

public slots:
    void setAtmospherePage(int index);

private:
    Ui::AtmosphereInput *ui;
};

#endif // ATMOSPHEREINPUT_H
