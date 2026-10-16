#ifndef ATMOSPERICMODELIMPUT_H
#define ATMOSPERICMODELIMPUT_H

#include <QWidget>

namespace Ui {
class AtmospericModelImput;
}

class AtmospericModelImput : public QWidget
{
    Q_OBJECT

public:
    explicit AtmospericModelImput(QWidget *parent = nullptr);
    ~AtmospericModelImput();

private:
    Ui::AtmospericModelImput *ui;
};

#endif // ATMOSPERICMODELIMPUT_H
