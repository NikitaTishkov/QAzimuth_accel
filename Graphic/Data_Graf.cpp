#include "Data_Graf.h"
#include <QPainter>
#include <QPoint>
#include <QFont>
#include <math.h>

Data_Graf::Data_Graf(quint32 L, quint32 H, qint16 Min_V, qint16 Max_V, const QString Data,
                     const QString cData, QWidget *parent) :
    QWidget(parent), graf_lenght(L), graf_height(H),    Min_Value(Min_V), Max_Value(Max_V),
    Shag(1), Kursor_Point(0,0), Size(0), X0(0), X1(0)
{
    Graph_Pen.setBrush(QBrush(QColor(255, 255, 0)));
    Graph_Pen.setWidth(2);

    setFixedHeight(graf_height);
    setFixedWidth(700);

    D_Vector.Size = 0;
    D_Vector.RMS = 0;
    D_Vector.Average = 0;

    QFont VFont;
    VFont.setBold(true);

    Data_label    = new QLabel(Data);
        Data_label->setAlignment(Qt::AlignRight);
    Data_Vlabel   = new QLabel("?");
        Data_Vlabel->setFont(VFont);

    cData_label   = new QLabel(cData);
        cData_label->setAlignment(Qt::AlignRight);
    cData_Vlabel  = new QLabel("?");
    cData_Vlabel->setFont(VFont);

    Average_label = new QLabel(tr("Average:"));
        Average_label->setAlignment(Qt::AlignRight);
    Average_Vlabel = new QLabel("?");
        Average_Vlabel->setFont(VFont);

    RMS_label = new QLabel(tr("RMSD:"));
        RMS_label->setAlignment(Qt::AlignRight);
    RMS_Vlabel = new QLabel("?");
        RMS_Vlabel->setFont(VFont);

    qhb = new QHBoxLayout;
          qhb->addWidget(Data_label);
          qhb->addWidget(Data_Vlabel);
          qhb->addWidget(cData_label);
          qhb->addWidget(cData_Vlabel);
          qhb->addWidget(Average_label);
          qhb->addWidget(Average_Vlabel);
          qhb->addWidget(RMS_label);
          qhb->addWidget(RMS_Vlabel);
}

void Data_Graf::paintEvent(QPaintEvent *event)
{
    QPainter pain;
        pain.begin(this);
            pain.fillRect(event->rect(), QBrush(QColor(100, 154, 225)));
        pain.end();

    QPainter Sys_Koord;

    Sys_Koord.begin(this);

        Sys_Koord.translate(0, 5);

        quint8 g_height = (quint8)(graf_height-10);

        Sys_Koord.setPen(QPen(QBrush(QColor(0, 255, 0)), 2));
        Sys_Koord.drawLine(graf_lenght, g_height,   0,           g_height);
        Sys_Koord.drawLine(graf_lenght, 0,          graf_lenght, g_height);

        Sys_Koord.setPen(QPen(QBrush(QColor(0, 255, 0)), 1));
        Sys_Koord.drawLine(graf_lenght, 0,            0, 0);
        Sys_Koord.drawLine(graf_lenght, g_height/4,   0, g_height/4);
        Sys_Koord.drawLine(graf_lenght, g_height/2,   0, g_height/2);
        Sys_Koord.drawLine(graf_lenght, g_height*3/4, 0, g_height*3/4);

    Sys_Koord.end();

    QPainter Graph;
    Graph.begin(this);
        Graph.translate(0, 5);
        Graph.setBrush(QBrush(QColor(255, 255, 0)));

        int k;

        if(Size < graf_lenght*Shag)
            k = Size;
        else
            k = graf_lenght*Shag;

        QPoint points[k];

        if(Size < graf_lenght*Shag)
        {
            for(unsigned i = 0; i < Size; i++)
            {
                float K = float((double)g_height/(Max_Value-Min_Value));
                int Z = int(D_Vector.Data[i]*K - Min_Value*K);
                points[i] = QPoint((int)(i/Shag), (int)(g_height - Z));

                if(D_Vector.Status[i] == 'B' || D_Vector.Status[i] == 'A')
                    Graph.setPen(Graph_Pen);
                else
                    Graph.setPen(QPen(QBrush(QColor(200, 0, 0)), 2));

                if(i>0)
                    Graph.drawLine(points[i-1], points[i]);
            }
        }
        else
        {
            for(unsigned i = 0; i < graf_lenght*Shag; i++)
            {
                float K = float((double)g_height/(Max_Value-Min_Value));
                int Z = int(D_Vector.Data[i+Size-graf_lenght*Shag]*K - Min_Value*K);
                points[i] = QPoint((int)(i/Shag), (int)(g_height - Z));

                if(D_Vector.Status[i+Size-graf_lenght*Shag] == 'B'
                || D_Vector.Status[i+Size-graf_lenght*Shag] == 'A')
                    Graph.setPen(Graph_Pen);
                else
                    Graph.setPen(QPen(QBrush(QColor(200, 0, 0)), 2));

                if(i>0)
                    Graph.drawLine(points[i-1], points[i]);
            }
        }

    Graph.end();

    QPainter Kursor;
    Kursor.begin(this);
        Kursor.setPen(QPen(QBrush(QColor(100, 100, 200)), 4));
        Kursor.drawLine(Kursor_Point.x(), 0, Kursor_Point.x(), graf_height);
    Kursor.end();

    QPainter segment;
    segment.begin(this);
        segment.setPen(QPen(QBrush(QColor(0, 100, 200)), 4));
        segment.drawLine(X0, 0, X0, graf_height);
        segment.drawLine(X1, 0, X1, graf_height);
    segment.end();

    QPainter title;
        title.begin(this);

        int height = graf_height - 10;

        QFont Title_Font;
        Title_Font.setPixelSize(12);
        title.setFont(Title_Font);
        title.setPen(QPen(QBrush(Qt::black), 4));
        float Center = (float)(Max_Value+Min_Value)/2;
        float C_34 = (float)(Max_Value + Center)/2;
        float C_14 = (float)(Min_Value + Center)/2;
        title.drawText(QRect(0, 0,          40, 12),  Qt::AlignCenter, QString::number(Max_Value));
        title.drawText(QRect(0, height/4,   40, 12),  Qt::AlignCenter, QString::number(C_34, 'g', 4));
        title.drawText(QRect(0, height/2,   40, 12),  Qt::AlignCenter, QString::number(Center, 'g', 4));
        title.drawText(QRect(0, height*3/4, 40, 12),  Qt::AlignCenter, QString::number(C_14, 'g', 4));
        title.drawText(QRect(0, height,     40, 12),  Qt::AlignCenter, QString::number(Min_Value));
    title.end();

    if(Kursor_Point.x() != 0)
    {
        this->Move_Cursor();
    }
}

void Data_Graf::animate(QVector<float> *Data_V, QVector<char> *Status_V)
{
    D_Vector.Data   = Data_V->begin();
    D_Vector.Status = Status_V->begin();
    D_Vector.Size   = Data_V->size();
    Size = (quint32)D_Vector.Size;

    if(Size > 0)
    {
        float Data = D_Vector.Data[Size - 1];
        Data_Vlabel->setText(QString::number(Data));

        D_Vector.Average = double((D_Vector.Average*(double)(D_Vector.Size - 1) + (double)Data)/(double)D_Vector.Size);

        D_Vector.RMS = double((pow((double)Data - D_Vector.Average, 2)+D_Vector.RMS*(double)(D_Vector.Size - 1))/(double)D_Vector.Size);

        Average_Vlabel->setText(QString::number(D_Vector.Average, 'g', 4));
        RMS_Vlabel->setText(QString::number(sqrt(D_Vector.RMS), 'g', 4));
    }

    repaint();
}

void Data_Graf::Change_Shag(const int S)
{
    Shag = S;
    if(D_Vector.Size > quint64(graf_lenght*Shag))
        Size = graf_lenght*Shag;
    repaint();
}

void Data_Graf::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit Press_Cursor_Signal(event->pos());
}

void Data_Graf::mouseMoveEvent(QMouseEvent *event)
{
    emit Move_Cursor_Signal(event->pos());
}

void Data_Graf::mouseReleaseEvent(QMouseEvent *event)
{
    emit Release_Cursor_Signal(event->pos());
}

void Data_Graf::Press_Cursor_Slot(const QPoint K)
{
    Kursor_Point = K;

    if(Kursor_Point.x() > int(Size/Shag))
        Kursor_Point.setX(Size/Shag);

    X0 = Kursor_Point.x();

    repaint();
}

void Data_Graf::Move_Cursor_Slot(const QPoint K)
{
    Kursor_Point = K;

    if(Kursor_Point.x() < 0)
        Kursor_Point.setX(0);

    if(Kursor_Point.x() > int(Size/Shag))
        Kursor_Point.setX(Size/Shag);

    if(Kursor_Point.x() >= (int)graf_lenght)
        Kursor_Point.setX(graf_lenght-1);

    repaint();
}

void Data_Graf::Release_Cursor_Slot(const QPoint K)
{
    if(Kursor_Point.x() > int(Size/Shag))
        Kursor_Point.setX(Size/Shag);

    if(X0 < K.x())
        X1 = Kursor_Point.x();
    else
    {
        X1 = X0;
        X0 = K.x();

        if(X0 < 0)
            X0 = 0;
    }

    repaint();
}


void Data_Graf::Move_Cursor()
{
    if(Kursor_Point.x()*Shag > Size)
        return;

    int Data_Number;

    if(Size < graf_lenght*Shag)
        Data_Number = Kursor_Point.x()*Shag;
    else
        Data_Number = Kursor_Point.x()*Shag + Size - graf_lenght*Shag;

    cData_Vlabel->setText(QString::number(D_Vector.Data[Data_Number-1]));

    emit Data_Number_Signal(Data_Number);
}

void Data_Graf::Slider_Move(const int Slider)
{
    Size = (unsigned)Slider;
    quint32 D_Size = (quint32)D_Vector.Size;

    if(Size < graf_lenght*Shag && Size < D_Size)
    {
        if(D_Size > graf_lenght*Shag)
            Size = graf_lenght*Shag;
        else
            Size = D_Size;
    }

    repaint();
}

void Data_Graf::Set_Brush(QBrush Brush)
{
    Graph_Pen.setBrush(Brush);
}

void Data_Graf::Show_Hide_Slot(const bool clicked)
{
    if(clicked)
    {
        Data_label    ->show();
        cData_label   ->show();
        Average_label ->show();
        RMS_label     ->show();
        show();
    }
    else
    {
        Data_label    ->hide();
        cData_label   ->hide();
        Average_label ->hide();
        RMS_label     ->hide();
        hide();
    }
}

void Data_Graf::Calculation_Average(quint8 Sigma)
{
    double Average = 0;
    double RMS = 0;
    double Error = 0;

    int S = 0;

    if(Size < graf_lenght*Shag)
    {
        for(quint32 i = X0*Shag; i<X1*Shag; i++)
        {
            Average = (Average*S + D_Vector.Data[i])/(S+1);
            RMS     = (pow(D_Vector.Data[i] - Average, 2) + RMS*S)/(S+1);
            S++;
        }
    }
    else
    {
        for(quint32 i=X0*Shag+Size-graf_lenght*Shag; i<X1*Shag+Size-graf_lenght*Shag; i++)
        {
            Average = (Average*S + D_Vector.Data[i])/(S+1);
            RMS     = (pow(D_Vector.Data[i] - Average, 2) + RMS*S)/(S+1);
            S++;
        }
    }

    RMS = sqrt(RMS);

        for(quint32 i = 0; i < Size; i++)
        {
            if((D_Vector.Data[i] > Average + RMS*Sigma) || (D_Vector.Data[i] < Average - RMS*Sigma))
                Error++;
        }

    emit AverageRMS_Signal(Average, RMS * Sigma, (Error*100)/Size);
}

void Data_Graf::Set_Lenght(int L)
{
    graf_lenght = L - 430;
    resize(graf_lenght, graf_height);

    if(D_Vector.Size > quint64(graf_lenght*Shag))
        Size = graf_lenght*Shag;
}

void Data_Graf::Set_Max_Value(double Max)
{
    Max_Value = Max;
    repaint();
}

void Data_Graf::Set_Min_Value(double Min)
{
    Min_Value = Min;
    repaint();
}

void Data_Graf::Clear_Slot()
{
    D_Vector.Average = 0;
    D_Vector.RMS = 0;
    D_Vector.Size = 0;
}
