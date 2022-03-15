#include "Analiz.h"
#include <math.h>
#include <QPushButton>

Analiz::Analiz(qint16 min, qint16 max, QWidget *parent) :
    QWidget(parent)
{

    setFixedSize(280, 110);

    QLabel *Average_Label = new QLabel(tr("Average: "));

    Sigma = new QSpinBox();
    Sigma->setValue(3);
    Sigma->setMinimum(1);
    Sigma->setMaximum(9);
    Sigma->setSuffix("x");
    Sigma->setMaximumWidth(40);

    Average = new QDoubleSpinBox();
    Average->setRange(min, max);
    Average->setDecimals(4);

    QLabel *RMS_Label     = new QLabel(tr("RMSD: "));
    RMS     = new QDoubleSpinBox();
    RMS->setRange(0, 999);
    RMS->setDecimals(4);

    Brack_RMS    = new QLabel(tr("Error RMSD:"));
        Brack_RMS->setAlignment(Qt::AlignRight);

    Brack_VRMS    = new QLabel("?");
        QFont font;
        font.setBold(true);
        Brack_VRMS->setFont(font);
        Brack_VRMS->setAlignment(Qt::AlignLeft);

    QPushButton *Calc_A = new QPushButton(tr("Calculate"));

    QGridLayout * QGL = new QGridLayout;
    QGL->addWidget(Average_Label,   0, 0, 1, 1);
    QGL->addWidget(Average,         0, 2, 1, 2);
    QGL->addWidget(RMS_Label,       1, 0, 1, 1);
    QGL->addWidget(Sigma,           1, 1, 1, 1);
    QGL->addWidget(RMS,             1, 2, 1, 2);
    QGL->addWidget(Calc_A,          2, 0, 1, 1);
    QGL->addWidget(Brack_RMS,       2, 1, 1, 2);
    QGL->addWidget(Brack_VRMS,      2, 3, 1, 1);
    setLayout(QGL);

    connect(Calc_A, SIGNAL(clicked()),          this, SLOT(Calculation_Average_Slot()));
    connect(Sigma,  SIGNAL(valueChanged(int)),  this, SLOT(Calculation_Average_Slot()));
}

void Analiz::Calculation_Average_Slot()
{
    emit Calculation((quint8)Sigma->value());
}


void Analiz::Show_Hide_Slot(bool clicked)
{
    if(clicked)
        show();
    else
        hide();
}

void Analiz::AverageRMS_Slot(double A, double R, double E)
{
    Average->setValue(A);
    RMS    ->setValue(R);
    Brack_VRMS->setText(QString::number(E, 'g', 4) + " %");
}
