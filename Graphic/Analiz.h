#ifndef ANALIZ_H
#define ANALIZ_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "Data_Graf.h"

class Analiz : public QWidget
{
    Q_OBJECT
private:
    QSpinBox        *Sigma;
    QDoubleSpinBox  *Average;
    QDoubleSpinBox  *RMS;

    QLabel *Brack_RMS, *Brack_VRMS;

public:
    explicit Analiz(qint16, qint16, QWidget *parent = 0);
signals:
    void Calculation(quint8);
private slots:
    void Calculation_Average_Slot();
public slots:
    void Show_Hide_Slot(bool);
    void AverageRMS_Slot(double, double, double);
};

#endif // ANALIZ_H
