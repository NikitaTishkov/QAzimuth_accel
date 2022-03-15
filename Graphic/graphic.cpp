#include "graphic.h"
#include <QBoxLayout>
#include <QGridLayout>

#define Min_H  220
#define HEIGHT 100

Graphic::Graphic() : graf_lenght(700), graf_height(100)
{
    Data_Spinbox    = new QSpinBox();
        Data_Spinbox->setMaximum(1000);
        Data_Spinbox->setMinimum(1);
        Data_Spinbox->setValue(1);
        Data_Spinbox->setMaximumWidth(100);

    Find_Button = new QPushButton(tr("Find"));
    connect(Find_Button, SIGNAL(clicked()), this, SLOT(Send_Find_Slot()));

    QPushButton  *Menu_Button = new QPushButton(tr("Menu"));

    Data_Slider = new QSlider(Qt::Horizontal);
    Data_Slider->setDisabled(true);
    Data_Slider->setValue(graf_lenght);

    QHB = new QHBoxLayout;
    QHB->addWidget(Menu_Button);
    QHB->addWidget(Find_Button);
    QHB->addWidget(Data_Slider);
    QHB->addWidget(Data_Spinbox);
    //setLayout(QHB);

    VFont.setBold(true);

    QLabel *N_Label  = new QLabel("N:");
            N_Label->setAlignment(Qt::AlignRight);
            N_Value  = new QLabel("?");
            N_Value->setFont(VFont);
            N_Value->setAlignment(Qt::AlignLeft);
            N_Value->setStyleSheet("QLabel { color : brown; }");
    QLabel *N_CLabel = new QLabel("C_N:");
            N_CLabel->setAlignment(Qt::AlignRight);
            N_CValue = new QLabel("?");
            N_CValue->setFont(VFont);
            N_CValue->setAlignment(Qt::AlignLeft);
            N_CValue->setStyleSheet("QLabel { color : brown; }");

    QHB_Data = new QHBoxLayout;
    QHB_Data->addWidget(N_Label);
    QHB_Data->addWidget(N_Value);
    QHB_Data->addWidget(N_CLabel);
    QHB_Data->addWidget(N_CValue);

    QGL = new QGridLayout;
    QGL->addLayout(QHB, 9, 0, 1, 1);
    setLayout(QGL);
}

void Graphic::Set_Brush(QBrush Brush, int G)
{
    GraphW_Vector[G]->Set_Brush(Brush);
}

Graphic::~Graphic()
{

}

void Graphic::Add_Graphic(qint32 Value_min, qint32 Value_max, QString Name)
{
    GraphW_Vector.push_back(new Graphic_Widget(graf_lenght, graf_height, Value_min,  Value_max, Name));

    connect(Data_Spinbox,          SIGNAL(valueChanged(int)),
            GraphW_Vector.last(),  SLOT(Change_Shag_Slot(int)));

    connect(Data_Slider,           SIGNAL(valueChanged(int)),
            GraphW_Vector.last(),  SLOT(Slider_Slot(int)));

    connect(GraphW_Vector.last(),  SIGNAL(Press_Cursor_Signal(QPoint)),
            this,                  SLOT(Press_Cursor_Slot(QPoint)));
    connect(GraphW_Vector.last(),  SIGNAL(Move_Cursor_Signal(QPoint)),
            this,                  SLOT(Move_Cursor_Slot(QPoint)));
    connect(GraphW_Vector.last(),  SIGNAL(Release_Cursor_Signal(QPoint)),
            this,                  SLOT(Release_Cursor_Slot(QPoint)));
    connect(GraphW_Vector.last(),  SIGNAL(Data_Number_Signal(int)),
            this,                  SLOT(Show_Data_Slot(int)));

    connect(this,                  SIGNAL(Press_Cursor_Signal(QPoint)),
            GraphW_Vector.last(),  SLOT(Press_Cursor_Slot(QPoint)));
    connect(this,                  SIGNAL(Move_Cursor_Signal(QPoint)),
            GraphW_Vector.last(),  SLOT(Move_Cursor_Slot(QPoint)));
    connect(this,                  SIGNAL(Release_Cursor_Signal(QPoint)),
            GraphW_Vector.last(),  SLOT(Release_Cursor_Slot(QPoint)));

    QGL->addWidget(GraphW_Vector.last(), GraphW_Vector.size()-1, 0, 1, 14);
}

void Graphic::Add_Label(QString Label_Text)
{
    Label_Vector.push_back(new struct Label);

    Label_Vector.last()->Data_Label = new QLabel(Label_Text);
    Label_Vector.last()->Data_Label->setAlignment(Qt::AlignRight);
    Label_Vector.last()->Data_Value = new QLabel("?");
    Label_Vector.last()->Data_Value->setAlignment(Qt::AlignLeft);
    Label_Vector.last()->Data_Value->setFont(VFont);
    Label_Vector.last()->C_Label    = new QLabel("C_" + Label_Text);
    Label_Vector.last()->C_Label->setAlignment(Qt::AlignRight);
    Label_Vector.last()->C_Value    = new QLabel("?");
    Label_Vector.last()->C_Value->setAlignment(Qt::AlignLeft);
    Label_Vector.last()->C_Value->setFont(VFont);

    QHB_Data->addWidget(Label_Vector.last()->Data_Label);
    QHB_Data->addWidget(Label_Vector.last()->Data_Value);
    QHB_Data->addWidget(Label_Vector.last()->C_Label);
    QHB_Data->addWidget(Label_Vector.last()->C_Value);

    QGL->addLayout(QHB_Data,  GraphW_Vector.size(), 0, 1, 14);
}

void Graphic::Add_Time_Label()
{
    Time_Label.Data_Label = new QLabel("Time: ");
    Time_Label.Data_Label->setAlignment(Qt::AlignRight);
    Time_Label.Data_Value = new QLabel("?");
    Time_Label.Data_Value->setAlignment(Qt::AlignLeft);
    Time_Label.Data_Value->setFont(VFont);
    Time_Label.Data_Value->setStyleSheet("QLabel { color : blue; }");
    Time_Label.C_Label    = new QLabel("C_Time: ");
    Time_Label.C_Label->setAlignment(Qt::AlignRight);
    Time_Label.C_Value    = new QLabel("?");
    Time_Label.C_Value->setAlignment(Qt::AlignLeft);
    Time_Label.C_Value->setFont(VFont);
    Time_Label.C_Value->setStyleSheet("QLabel { color : blue; }");

    QHB_Data->addWidget(Time_Label.Data_Label);
    QHB_Data->addWidget(Time_Label.Data_Value);
    QHB_Data->addWidget(Time_Label.C_Label);
    QHB_Data->addWidget(Time_Label.C_Value);

    QGL->addLayout(QHB_Data,  GraphW_Vector.size(), 0, 1, 14);
}

void Graphic::Add_Date_Label()
{

}

void Graphic::Build_Graphic(float Data, char Status, quint8 N)
{
    GraphW_Vector[N]->BuildGraphic(Data, Status);

    N_Value->setText(QString::number(GraphW_Vector[0]->Data_Size()));
}

void Graphic::Write_Data(int Data, quint8 N)
{
    Label_Vector[N]->Value.push_back(Data);
    Label_Vector[N]->Data_Value->setText(QString::number(Data));
}

QString Graphic::Time_QString(const float T)
{
    QString Time = QString::number(T);

    if(T < 100000)
        Time.push_front('0');
    if(T < 10000)
        Time.push_front('0');
    if(T < 1000)
        Time.push_front('0');
    if(T < 100)
        Time.push_front('0');

    Time.push_back("00");

    Time[7] = Time[5];
    Time[6] = Time[4];
    Time[5] = ':';
    Time[4] = Time[3];
    Time[3] = Time[2];
    Time[2] = ':';

    Time[8] = ' ';
    Time[9] = ' ';
    return Time;
}

void Graphic::Write_Time(float T)
{
    Time_Label.Value.push_back(T);
    Time_Label.Data_Value->setText(Time_QString(T));
}

void Graphic::Write_Date(quint16)
{

}

void Graphic::Show_Data_Slot(int Numb)
{
    if(Time_Label.Value.size() >= Numb)
       Time_Label.C_Value->setText(Time_QString(Time_Label.Value[Numb-1]));

    Number = Numb;

    N_CValue->setText(QString::number(Numb));

    if(Label_Vector.size() <= 0)
        return;

    if(Label_Vector[0]->Value.size() <= Numb)
        Numb = Label_Vector[0]->Value.size()-1;

    for(int i=0; i< Label_Vector.size(); i++)
        Label_Vector[i]->C_Value->setText(QString::number(Label_Vector[i]->Value[Numb-1]));
}

void Graphic::Press_Cursor_Slot(QPoint point)
{
    emit Press_Cursor_Signal(point);
}

void Graphic::Move_Cursor_Slot(QPoint point)
{
    emit Move_Cursor_Signal(point);
}

void Graphic::Release_Cursor_Slot(QPoint point)
{
    emit Release_Cursor_Signal(point);
}

void Graphic::Clear_Slot()
{
    for(int i = 0; i < GraphW_Vector.size(); i++)
        GraphW_Vector[i]->Clear_Slot();
    for(int i = 0; i < Label_Vector.size(); i++)
        Label_Vector[i]->Data_Value->clear();
}

void Graphic::Push_Read_Buton_Slot(const bool clicked)
{
    if(clicked)
    {
        Data_Slider->setEnabled(false);
        Find_Button->setEnabled(false);
    }
    else
    {
        Find_Button->setEnabled(true);
        if(GraphW_Vector[0]->Data_Size() < graf_lenght*Data_Spinbox->value())
        {
            Data_Slider->setEnabled(false);
        }
        else
        {
            Data_Slider->setEnabled(true);
            Data_Slider->setRange(graf_lenght, GraphW_Vector[0]->Data_Size());
            Data_Slider->setValue(GraphW_Vector[0]->Data_Size());
        }
    }
}

void Graphic::Read_All_Button_Slot()
{
        Data_Slider->setEnabled(true);
        Data_Slider->setRange(graf_lenght, GraphW_Vector[0]->Data_Size());
        Data_Slider->setValue(GraphW_Vector[0]->Data_Size());
}

void Graphic::resizeEvent(QResizeEvent *)
{

}

void Graphic::Find_Point_Slot(int Numb)
{
    if(Numb > GraphW_Vector[0]->Data_Size())
        return;

    QPoint point(1,1);

    if(Numb < graf_lenght*Data_Spinbox->value())
    {
        point.setX(Numb/Data_Spinbox->value());
        Data_Slider->setValue(graf_lenght*Data_Spinbox->value());
    }
    else
    {
        if(Numb+graf_lenght*Data_Spinbox->value()/2 < GraphW_Vector[0]->Data_Size())
        {
            Data_Slider->setValue(Numb+graf_lenght*Data_Spinbox->value()/2);
            point.setX(graf_lenght*Data_Spinbox->value()/2);
        }
        else
        {
            Data_Slider->setValue(GraphW_Vector[0]->Data_Size());
            point.setX(graf_lenght - GraphW_Vector[0]->Data_Size() + Numb);
        }
    }

    emit Press_Cursor_Signal(point);
}

void Graphic::Send_Find_Slot()
{
    emit Find_Point_Signal(Number);

    double Cents = (double)Number/GraphW_Vector[0]->Data_Size();

    emit Find_Text_Signal(Cents);
}
