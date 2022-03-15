#ifndef COM_ACCEL_GRAPHIC_H
#define COM_ACCEL_GRAPHIC_H

#include <QWidget>
#include <QPaintEvent>

class Com_Accel_Graphic : public QWidget
{
    Q_OBJECT
public:
    explicit Com_Accel_Graphic(QWidget *parent = 0);
    ~Com_Accel_Graphic();
    void Com_animate(float Pitch, char Status);
    void Accel_animate(float Pitch, char Status);
signals:

public slots:
protected:
    void paintEvent(QPaintEvent *);
private:
    int X_Size; int Y_Size;
    qreal Com_Pitch, Accel_Pitch;
    char Com_Status, Accel_Status;
};

#endif // COM_ACCEL_GRAPHIC_H
