#ifndef REFRACTIONMODELINPUT_H
#define REFRACTIONMODELINPUT_H

#include <QWidget>

namespace Ui {
class RefractionModelInput;
}

class RefractionModelInput : public QWidget
{
    Q_OBJECT

public:
    explicit RefractionModelInput(QWidget *parent = nullptr);
    ~RefractionModelInput();

private:
    Ui::RefractionModelInput *ui;
};

#endif // REFRACTIONMODELINPUT_H
