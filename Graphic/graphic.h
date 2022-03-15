#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QWidget>
#include <QPaintEvent>
#include <QVector>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QMenu>
#include <QAction>
#include <QSettings>
#include <QScrollArea>

#include <lib/NMEA_Struct.h>
#include <Graphic/Data_Graf.h>
#include <Formulars/NMEA_DIALOG/dialog.h>
#include <Graphic/Analiz.h>
#include <Graphic/Control_Graf.h>
#include <Graphic/Graphic_Widget.h>

class Graphic : public QWidget
{
    Q_OBJECT
public:
    explicit Graphic();
    ~Graphic();
    void Set_Brush(QBrush, int);
private:
    const int graf_lenght, graf_height;
    QSpinBox     *Data_Spinbox;
    QSlider      *Data_Slider;
    QFont         VFont;
    QPushButton  *Find_Button;

    QHBoxLayout *QHB, *QHB_Data;
    QGridLayout *QGL;

    QVector<Graphic_Widget*> GraphW_Vector;

    struct Label{
        QLabel  *Data_Label, *Data_Value, *C_Label, *C_Value;
        QVector<int> Value;
    };
    QVector<struct Label*>   Label_Vector;

    struct Time_Label{
        QLabel  *Data_Label, *Data_Value, *C_Label, *C_Value;
        QVector<float> Value;
    };
    struct Time_Label Time_Label;

    struct Date_Label{
        QLabel  *Data_Label, *Data_Value, *C_Label, *C_Value;
        QVector<int> Value;
    };
    struct Date_Label Date_Label;

    int Number;

    QLabel *N_Value, *N_CValue;

    QString Time_QString(const float);
private slots:
    void Send_Find_Slot();
    void Show_Data_Slot(int);
protected:
    void Add_Graphic(qint32, qint32, QString);
    void Add_Label(QString);
    void Add_Time_Label();
    void Add_Date_Label();
    void Build_Graphic(float, char, quint8);
    void Write_Data(int, quint8);
    void Write_Time(float);
    void Write_Date(quint16);
    void resizeEvent(QResizeEvent *);
signals:
    void Press_Cursor_Signal(QPoint);
    void Move_Cursor_Signal(QPoint);
    void Release_Cursor_Signal(QPoint);
    void Find_Point_Signal(int);
    void Find_Text_Signal(double);
protected slots:
    virtual void Find_Slot(){};
    void Press_Cursor_Slot(QPoint);
    void Move_Cursor_Slot(QPoint);
    void Release_Cursor_Slot(QPoint);
public slots:
    void Clear_Slot();
    void Push_Read_Buton_Slot(const bool);
    void Read_All_Button_Slot();
    void Find_Point_Slot(int);
};

#endif // GRAPHIC_H
