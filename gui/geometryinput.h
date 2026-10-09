#ifndef GEOMETRYINPUT_H
#define GEOMETRYINPUT_H

#include <QWidget>

namespace Ui {
class GeometryInput;
}

class GeometryInput : public QWidget
{
    Q_OBJECT

public:
    explicit GeometryInput(QWidget *parent = nullptr);
    ~GeometryInput();

private:
    Ui::GeometryInput *ui;
};

#endif // GEOMETRYINPUT_H
