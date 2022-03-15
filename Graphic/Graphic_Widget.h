#ifndef GRAPHIC_WIDGET_H
#define GRAPHIC_WIDGET_H

#include "Data_Graf.h"
#include "Analiz.h"
#include "Control_Graf.h"

#include <QWidget>

class Graphic_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Graphic_Widget(quint16,       quint16,           qint32, qint32,
                            const QString,  QWidget *parent = 0);
    ~Graphic_Widget();
    void setWidthGraphic(quint16);
    void BuildGraphic(float, char );
    int  Data_Size();
    void Set_Brush(QBrush);
public slots:
    void Change_Shag_Slot(const int);
    void Press_Cursor_Slot(const QPoint );
    void Move_Cursor_Slot(const QPoint);
    void Release_Cursor_Slot(const QPoint);
    void Slider_Slot(const int);
    void Clear_Slot();
private slots:
    void Press_Cursor_PSlot(QPoint);
    void Move_Cursor_PSlot(QPoint);
    void Release_Cursor_PSlot(QPoint);
    void Data_Number_Slot(int);
    void Set_AN_Value(int);
signals:
    void Move_Cursor_Signal(QPoint);
    void Press_Cursor_Signal(QPoint);
    void Release_Cursor_Signal(QPoint);
    void Data_Number_Signal(int);
private:
    Data_Graf    *Data_graf;
    Analiz       *Analiz_Data;
    Control_Graf *Control_Data;

    struct Data_Vector{
        QVector<float> Data;
        QVector<char>  Status;
    };

    struct Data_Vector Data_Vector;

    QVector<float> AN_Vector;
    quint16 AN;
};

#endif // GRAPHIC_WIDGET_H
