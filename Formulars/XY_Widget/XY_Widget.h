#ifndef XY_WIDGET_H
#define XY_WIDGET_H

#include <QWidget>
#include <QVector>
#include "XY_Graphic.h"
#include <lib/NMEA_Struct.h>

namespace Ui {
class XY_Widget;
}

class XY_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit XY_Widget(QString, QWidget *parent = 0);
    ~XY_Widget();
    void Get_Data(float AC_X, float AC_Y);
public slots:
    void Clear();
private:
    Ui::XY_Widget  *ui;
    XY_Graphic     *Graphic;

    struct Data_Struct{
        QList<float> X;
        QList<float> Y;
    };

    struct Data_Struct Data;
};

#endif // XY_WIDGET_H
