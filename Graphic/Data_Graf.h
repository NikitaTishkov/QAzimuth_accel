#ifndef COURSE_GRAF_H
#define COURSE_GRAF_H

#include <QWidget>
#include <QPaintEvent>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QGraphicsSceneMouseEvent>
#include "lib/NMEA_Struct.h"

class Data_Graf : public QWidget
{
    Q_OBJECT
public:
    explicit Data_Graf(quint32, quint32, qint16, qint16, const QString, const QString, QWidget *parent = 0);

    QStringList   Data_grad;

    QHBoxLayout  *qhb;

    void Set_Lenght(int );
    void Change_Shag(const int);
    void Slider_Move(const int);
    void Set_Brush(QBrush);
protected:
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
public slots:
    void Repaint(){repaint();}
    void animate(QVector<float> *, QVector<char> *);
    void Press_Cursor_Slot(const QPoint);
    void Move_Cursor_Slot(const QPoint);
    void Release_Cursor_Slot(const QPoint);
    void Show_Hide_Slot(const bool);
    void Calculation_Average(quint8);
    void Set_Max_Value(double);
    void Set_Min_Value(double);
    void Clear_Slot();
private:
    quint32 graf_lenght;
    const quint32 graf_height;
    double Min_Value, Max_Value;
    quint32 Shag;
    QPoint Kursor_Point;
    QPen Graph_Pen;

    void Move_Cursor();

    quint32 Size;

    int X0, X1;

    struct D_Vector
    {
        QVector<float>::const_iterator Data;
        QVector<char>::const_iterator  Status;
        double          Average;
        double          RMS;
        quint64         Size;
    };

    QLabel       *Data_label,       *Data_Vlabel;
    QLabel       *cData_label,      *cData_Vlabel;
    QLabel       *Average_label,    *Average_Vlabel;
    QLabel       *RMS_label,        *RMS_Vlabel;

    struct D_Vector D_Vector;
signals:
    void Press_Cursor_Signal(QPoint);
    void Move_Cursor_Signal(QPoint);
    void Release_Cursor_Signal(QPoint);
    void AverageRMS_Signal(double, double, double);
    void Data_Number_Signal(int);
};

#endif // COURSE_GRAF_H
