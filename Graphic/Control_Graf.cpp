#include "Control_Graf.h"
#include <QGridLayout>
#include <QLabel>

Control_Graf::Control_Graf(qint32 Min, qint32 Max, QWidget *parent) :
    QWidget(parent)
{
    QLabel *Up_Label    = new QLabel(tr("Max:"));
    Up_Spin             = new QDoubleSpinBox();
    Up_Spin->setMaximum(Max);
    Up_Spin->setMinimum(Min);
    Up_Spin->setValue(Max);

    QLabel *Down_Label  = new QLabel(tr("Min:"));
    Down_Spin           = new QDoubleSpinBox();
    Down_Spin->setMaximum(Max);
    Down_Spin->setMinimum(Min);
    Down_Spin->setValue(Min);

    QLabel *AN_Label  = new QLabel(tr("AN:"));
    AN                  = new QSpinBox();
    AN->setMaximum(100);
    AN->setMinimum(1);
    AN->setValue(1);

    QGridLayout *L = new QGridLayout;
    L->addWidget(Up_Label,      0, 0);
    L->addWidget(Up_Spin,       0, 1);
    L->addWidget(Down_Label,    1, 0);
    L->addWidget(Down_Spin,     1, 1);
    L->addWidget(AN_Label,      2, 0);
    L->addWidget(AN,            2, 1);
    setLayout(L);

    setFixedSize(110, 110);

    connect(Up_Spin,      SIGNAL(valueChanged(double)), this,  SLOT(Set_Max_Slot(double)));
    connect(Down_Spin,    SIGNAL(valueChanged(double)), this,  SLOT(Set_Min_Slot(double)));
    connect(AN,           SIGNAL(valueChanged(int)),    this,  SLOT(Set_AN_Slot(int)));
}

void Control_Graf::Set_Max_Slot(double Max)
{
    emit Set_Max_Signal(Max);
}

void Control_Graf::Set_Min_Slot(double Min)
{
    emit Set_Min_Signal(Min);
}

void Control_Graf::Set_AN_Slot(int N)
{
    emit Set_AN_Signal(N);
}
