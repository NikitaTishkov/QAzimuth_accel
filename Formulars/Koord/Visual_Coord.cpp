#include "Visual_Coord.h"
#include <QPainter>
#include <math.h>

Visual_Coord::Visual_Coord(QWidget *parent) :
    QWidget(parent), graf_lenght(320), graf_height(320), Mash(50)
{
    setFixedSize(graf_lenght, graf_height);
}

void Visual_Coord::paintEvent(QPaintEvent *event)
{
    QPainter pain;
        pain.begin(this);
            pain.fillRect(event->rect(), QBrush(QColor(0, 154, 225)));
        pain.end();

    qreal Translate_X = graf_lenght/2, Translate_Y = graf_height/2;
    qreal X_Left = -Translate_X+10, Y_Down = -Translate_Y+10;
    qreal X_Lenght = -X_Left*2, Y_Lenght = -Y_Down*2;

    QPainter painter;
    painter.begin(this);
        painter.translate(Translate_X, Translate_Y);
        painter.setPen(QPen(QBrush(QColor(0, 240, 0)), 2));
        painter.drawEllipse(X_Left, Y_Down, X_Lenght, Y_Lenght);
        painter.drawEllipse(X_Left*2/3, Y_Down*2/3, X_Lenght*2/3, Y_Lenght*2/3);
        painter.drawEllipse(X_Left*1/3, Y_Down*1/3, X_Lenght*1/3, Y_Lenght*1/3);

        painter.drawLine(0, -Y_Down,  0, Y_Down);
        painter.drawLine(-X_Left, 0,  X_Left, 0);
    painter.end();

    QPainter title;

    title.begin(this);

        QFont Title_Font;
        Title_Font.setPixelSize(15);
        Title_Font.setBold(true);
        title.setFont(Title_Font);
        title.translate(Translate_X, Translate_Y);
        title.setPen(QPen(QBrush(Qt::black), 4));

        title.drawText(QRect(-5,        -Translate_Y,   12, 20), Qt::AlignCenter, tr("N"));
        title.drawText(QRect(-5,        Translate_Y-18, 12, 20), Qt::AlignCenter, tr("S"));
        title.drawText(QRect(X_Left-8,  -8,             15, 20), Qt::AlignCenter, tr("W"));
        title.drawText(QRect(-X_Left-4, -10,            12, 20), Qt::AlignCenter, tr("E"));

    title.end();

    QPainter Koord_paint;
    Koord_paint.begin(this);

        Koord_paint.translate(Translate_X, Translate_Y);
        Koord_paint.setPen(QPen(QBrush(QColor(255, 255, 0)), 3));
        Koord_paint.setBrush(QBrush(QColor(255, 255, 0)));

        for(int i = 0; i<Koord.Lat_List.size(); i++)
        {
            int y = int((Koord.Lat_List[i]  - Koord.Center_Lat)*Grad_to_M*Mash);
            int x = int((Koord.Long_List[i] - Koord.Center_Long)
                           *Grad_to_M*cos(Koord.Center_Lat*Grad_to_Rad)*Mash);

            Koord_paint.drawPoint(x, -y);
        }

    Koord_paint.end();

    QPainter Average;
    Average.begin(this);
        Average.translate(Translate_X, Translate_Y);
        Average.setPen(QPen(QBrush(QColor(240, 100, 0)), 1));
        Average.setBrush(QColor(240, 0, 240));

        int y = int((Koord.Average_Lat  - Koord.Center_Lat)*Grad_to_M*Mash);
        int x = int((Koord.Average_Long - Koord.Center_Long)
                       *Grad_to_M*cos(Koord.Center_Lat*Grad_to_Rad)*Mash);

        Average.drawEllipse(x-5, -y-5, 10, 10);
    Average.end();

    QPainter Current;
    Current.begin(this);
        Current.translate(Translate_X, Translate_Y);
        Current.setPen(QPen(QBrush(QColor(100, 240, 0)), 1));
        Current.setBrush(QColor(240, 240, 0));

        if(Koord.Lat_List.size() > 0)
        {
            y = int((Koord.Lat_List.last()  - Koord.Center_Lat)*Grad_to_M*Mash);
            x = int((Koord.Long_List.last() - Koord.Center_Long)
                     *Grad_to_M*cos(Koord.Center_Lat*Grad_to_Rad)*Mash);

        }
        Current.drawEllipse(x-5, -y-5, 10, 10);
    Current.end();

    QPainter number;

    number.begin(this);

        QFont Number_Font;
        Number_Font.setPixelSize(12);
        Number_Font.setBold(true);
        number.setFont(Number_Font);
        number.translate(Translate_X, Translate_Y);
        number.setPen(QPen(QBrush(Qt::black), 4));

        number.drawText(QRect(-X_Left*1/3, -6,   35, 12),
                        Qt::AlignLeft, QString::number(-X_Left*1/(3*Mash)));
        number.drawText(QRect(-X_Left*2/3, -6,   45, 12),
                        Qt::AlignLeft, QString::number(-X_Left*2/(3*Mash)));

    number.end();
}

void Visual_Coord::Set_Center_Lat_Slot(double Lat)
{
    Koord.Center_Lat  = Lat;

    repaint();
}

void Visual_Coord::Set_Center_Long_Slot(double Long)
{
    Koord.Center_Long = Long;

    repaint();
}

void Visual_Coord::Set_Average_Slot(double Lat, double Long)
{
    Koord.Average_Lat  = Lat;
    Koord.Average_Long = Long;
}

void Visual_Coord::Change_Mash_Slot(double M)
{
    Mash = 100.0/M;
    repaint();
}

void Visual_Coord::Clear_Slot()
{
    Koord.Lat_List.clear();
    Koord.Long_List.clear();
}
