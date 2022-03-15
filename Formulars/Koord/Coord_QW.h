#ifndef KOORD_QW_H
#define KOORD_QW_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QGridLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDoubleSpinBox>
#include <QSettings>
#include "Visual_Coord.h"

class Coord_QW : public QWidget
{
    Q_OBJECT
public:
    Coord_QW(QSettings &, QWidget *parent = 0);
    ~Coord_QW();
private:
    QSettings *Settings;
    QFont FON;
    Visual_Coord *visual_coord;

    QString Time;
    QString Long;
    QString Lat;
    QString Satelits;
    QString Dost;
    QString Average_Long;
    QString Average_Lat;

    QLabel *Time_VL;
    QLabel *Long_VL;
    QLabel *Lat_VL;
    QLabel *Satelits_VL;
    QLabel *Dost_VL;
    QLabel *Average_Long_VL;
    QLabel *Average_Lat_VL;
    QLabel *RMS_VL;

    QDoubleSpinBox *Lat_Spinbox;
    QDoubleSpinBox *Long_Spinbox;
    QDoubleSpinBox *Scale_Spinbox;

    double A_Lat;
    double A_Long;
    double RMS;
    unsigned size;

    void Read_Setting();
public slots:

private slots:
    void Clear_Slot();
    void Set_Center();
};

#endif // KOORD_QW_H
