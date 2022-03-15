#ifndef XY_GRAPHIC_H
#define XY_GRAPHIC_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QList>

class XY_Graphic : public QWidget
{
    Q_OBJECT
public:
    explicit XY_Graphic(QWidget *parent = 0);

signals:

public:
    void Get_Data(float, float);

public slots:
    void X_Left_Slot(int);
    void X_Right_Slot(int);
    void Y_UP_Slot(int);
    void Y_Down_Slot(int);
    void Clear();
protected:
    void paintEvent(QPaintEvent *event);
private:
    const int graf_lenght;
    const int graf_height;

    struct Koord{
        float        Center_X;
        float        Center_Y;
        int          X_Left;
        int          X_Right;
        int          Y_Up;
        int          Y_Down;
        double       X_Mash;
        double       Y_Mash;
        QList<float> X_List;
        QList<float> Y_List;
    }Koord;
};

#endif // XY_GRAPHIC_H
