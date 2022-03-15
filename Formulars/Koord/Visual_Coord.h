#ifndef VISUAL_KOORD_H
#define VISUAL_KOORD_H

#include <QWidget>
#include <QPaintEvent>
#include <QList>
#include "lib/NMEA_Struct.h"

#define Grad_to_M 60*1853.25
#define PI 3.1415926535897932384626433832795028841971
#define Grad_to_Rad PI/180

class Visual_Coord : public QWidget
{
    Q_OBJECT
public:
    explicit Visual_Coord(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
public slots:
    void Change_Mash_Slot(double);
    void Clear_Slot();
    void Set_Center_Lat_Slot(double);
    void Set_Center_Long_Slot(double);
    void Set_Average_Slot(double, double);
private:
    const int graf_lenght;
    const int graf_height;

    struct Koord{
        double Center_Lat;
        double Center_Long;
        double Average_Lat;
        double Average_Long;
        QList<double> Lat_List;
        QList<double> Long_List;
    }Koord;

    double Mash;
};

#endif // VISUAL_KOORD_H
