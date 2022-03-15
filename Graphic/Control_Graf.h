#ifndef CONTROL_GRAF_H
#define CONTROL_GRAF_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QPushButton>

class Control_Graf : public QWidget
{
    Q_OBJECT
public:
    explicit Control_Graf(qint32 Min, qint32 Max, QWidget *parent = 0);

signals:
    void Set_Max_Signal(double);
    void Set_Min_Signal(double);
    void Set_AN_Signal(int);
public slots:

private slots:
    void Set_Max_Slot(double);
    void Set_Min_Slot(double);
    void Set_AN_Slot(int);
private:
    QDoubleSpinBox    *Up_Spin;
    QDoubleSpinBox    *Down_Spin;
    QSpinBox          *AN;
};

#endif // CONTROL_GRAF_H
