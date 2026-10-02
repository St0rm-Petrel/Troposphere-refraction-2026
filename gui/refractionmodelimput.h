#ifndef REFRACTIONMODELIMPUT_H
#define REFRACTIONMODELIMPUT_H

#include <QWidget>

namespace Ui {
class RefractionModelImput;
}

class RefractionModelImput : public QWidget
{
    Q_OBJECT

public:
    explicit RefractionModelImput(QWidget *parent = nullptr);
    ~RefractionModelImput();

private:
    Ui::RefractionModelImput *ui;
};

#endif // REFRACTIONMODELIMPUT_H
