#ifndef REFRACTIONSELECTION_H
#define REFRACTIONSELECTION_H

#include <QWidget>

namespace Ui {
class RefractionSelection;
}

class RefractionSelection : public QWidget
{
    Q_OBJECT

public:
    explicit RefractionSelection(QWidget *parent = nullptr);
    ~RefractionSelection();


private:
    Ui::RefractionSelection *ui;
};

#endif // REFRACTIONSELECTION_H
