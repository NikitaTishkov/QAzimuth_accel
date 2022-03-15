#ifndef COM_ACCEL_H
#define COM_ACCEL_H

#include <QWidget>
#include <lib/NMEA_Struct.h>
#include "Com_Accel_Graphic.h"

namespace Ui {
class Com_Accel;
}

class Com_Accel : public QWidget
{
    Q_OBJECT

public:
    explicit Com_Accel(QWidget *parent = 0);
    ~Com_Accel();

private:
    Ui::Com_Accel *ui;
    Com_Accel_Graphic *CAG;
    float Com, Accel;
public slots:
    void Accel_Deg_SLOT(float, char);
    void Parse_POHPR_Slot(const struct POHPR &);
};

#endif // COM_ACCEL_H
