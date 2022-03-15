#include "Graphic_Widget.h"

Graphic_Widget::Graphic_Widget(quint16 graf_lenght, quint16 graf_height,
                               qint32 Value_min,    qint32 Value_max,
                               const QString Name,  QWidget *parent) : QWidget(parent), AN(0)
{
    Analiz_Data  = new Analiz(Value_min, Value_max);
    Control_Data = new Control_Graf(Value_min, Value_max);
    Data_graf    = new Data_Graf(graf_lenght, graf_height,
                                 Value_min,   Value_max,
                                 Name, "C_" + Name, this);

    this->setFixedHeight(140);
    QGridLayout *qgb = new QGridLayout;
        qgb->addWidget(Control_Data,        1, 0);
        qgb->addWidget(Data_graf,           1, 1);
        qgb->addWidget(Analiz_Data,         1, 2);
        qgb->addLayout(Data_graf->qhb,      2, 0, 1, 3);
        setLayout(qgb);

    connect(Data_graf, SIGNAL(Press_Cursor_Signal(QPoint)),     this, SLOT(Press_Cursor_PSlot(QPoint)));
    connect(Data_graf, SIGNAL(Move_Cursor_Signal(QPoint)),      this, SLOT(Move_Cursor_PSlot(QPoint)));
    connect(Data_graf, SIGNAL(Release_Cursor_Signal(QPoint)),   this, SLOT(Release_Cursor_PSlot(QPoint)));
    connect(Data_graf, SIGNAL(Data_Number_Signal(int)),         this, SLOT(Data_Number_Slot(int)));

    connect(Control_Data,  SIGNAL(Set_Max_Signal(double)), Data_graf,   SLOT(Set_Max_Value(double)));
    connect(Control_Data,  SIGNAL(Set_Min_Signal(double)), Data_graf,   SLOT(Set_Min_Value(double)));
    connect(Control_Data,  SIGNAL(Set_AN_Signal(int)),     this,        SLOT(Set_AN_Value(int)));

    connect(Analiz_Data,   SIGNAL(Calculation(quint8)), Data_graf,   SLOT(Calculation_Average(quint8)));
    connect(Data_graf,     SIGNAL(AverageRMS_Signal(double,double, double)),
            Analiz_Data,   SLOT(AverageRMS_Slot(double,double, double)));
}

Graphic_Widget::~Graphic_Widget()
{

}

void Graphic_Widget::setWidthGraphic(quint16 L)
{
    Data_graf->Set_Lenght(L);
}

void Graphic_Widget::BuildGraphic(float Data, char Status)
{
   double Average = Data;

   if(AN > 1)
   {
       AN_Vector.push_back(Data);
       quint16 AN_Size = (quint16)AN_Vector.size();

       if(AN_Size > AN)
       {
           AN_Vector.pop_front();
           AN_Size--;
       }

       for(int i=0; i<AN_Size; i++)
       {
           Average = (Average*i + AN_Vector[i])/(i+1);
       }
   }

   Data_Vector.Data.push_back(float(Average));
   Data_Vector.Status.push_back(Status);
   Data_graf->animate(&Data_Vector.Data, &Data_Vector.Status);
}

void Graphic_Widget::Change_Shag_Slot(const int S)
{
   Data_graf->Change_Shag(S);
}

void Graphic_Widget::Press_Cursor_Slot(const QPoint K)
{
   Data_graf->Press_Cursor_Slot(K);
}

void Graphic_Widget::Move_Cursor_Slot(const QPoint K)
{
   Data_graf->Move_Cursor_Slot(K);
}

void Graphic_Widget::Release_Cursor_Slot(const QPoint K)
{
   Data_graf->Release_Cursor_Slot(K);
}

void Graphic_Widget::Press_Cursor_PSlot(QPoint K)
{
    emit Press_Cursor_Signal(K);
}

void Graphic_Widget::Move_Cursor_PSlot(QPoint K)
{
    emit Move_Cursor_Signal(K);
}

void Graphic_Widget::Release_Cursor_PSlot(QPoint K)
{
    emit Release_Cursor_Signal(K);
}

void Graphic_Widget::Slider_Slot(const int S)
{
    Data_graf->Slider_Move(S);
}

void Graphic_Widget::Clear_Slot()
{
    Data_Vector.Data.clear();
    Data_Vector.Status.clear();
    Data_graf->animate(&Data_Vector.Data, &Data_Vector.Status);
    Data_graf->Clear_Slot();
}

int Graphic_Widget::Data_Size()
{
    return Data_Vector.Data.size();
}

void Graphic_Widget::Set_Brush(QBrush Brush)
{
    Data_graf->Set_Brush(Brush);
}

void Graphic_Widget::Data_Number_Slot(int Number)
{
    emit Data_Number_Signal(Number);
}

void Graphic_Widget::Set_AN_Value(int N)
{
    AN = (quint16)N;
}
