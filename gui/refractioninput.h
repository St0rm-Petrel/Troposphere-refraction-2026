#ifndef REFRACTIONINPUT_H
#define REFRACTIONINPUT_H

#include <QWidget>

namespace Ui {
class RefractionInput;
}

class RefractionInput : public QWidget
{
    Q_OBJECT

public:
    explicit RefractionInput(QWidget *parent = nullptr);
    ~RefractionInput();

public slots:
    void setRefractionPage(int index); 

private:
    Ui::RefractionInput *ui;
};

#endif // REFRACTIONINPUT_H
