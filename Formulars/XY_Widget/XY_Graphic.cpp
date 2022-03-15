#include "XY_Graphic.h"

XY_Graphic::XY_Graphic(QWidget *parent) : QWidget(parent), graf_lenght(520), graf_height(520)
{
    setFixedSize(graf_lenght, graf_height);

    Koord.X_Left   = -50;
    Koord.X_Right  =  50;
    Koord.Y_Up     =  1000;
    Koord.Y_Down   = -1000;

    Koord.Center_X = (float)(Koord.X_Left + Koord.X_Right)/2.0;
    Koord.X_Mash   = (double)(500.0/(Koord.X_Right - Koord.X_Left));
    Koord.Center_Y = (float)(Koord.Y_Up + Koord.Y_Down)/2.0;
    Koord.Y_Mash   = (double)(500.0/(Koord.Y_Up   - Koord.Y_Down));
}


void XY_Graphic::paintEvent(QPaintEvent *event)
{
    QPainter pain;
        pain.begin(this);
            pain.fillRect(event->rect(), QBrush(QColor(0, 154, 225)));
        pain.end();

        qreal Translate_X = graf_lenght/2, Translate_Y = graf_height/2;
        qreal X_Left = -Translate_X+10, Y_Down = -Translate_Y+10;

        QPainter painter;
        painter.begin(this);
            painter.translate(Translate_X, Translate_Y);
            painter.setPen(QPen(QBrush(QColor(0, 240, 0)), 2));
            painter.drawLine(0,    -Y_Down,    0,    Y_Down);
            painter.drawLine(0-10,  Y_Down+10, 0,    Y_Down);
            painter.drawLine(0,     Y_Down,    0+10, Y_Down+10);

            painter.drawLine(-X_Left, 0, X_Left,      0);
            painter.drawLine(-X_Left, 0,-X_Left-10, -10);
            painter.drawLine(-X_Left, 0,-X_Left-10,  10);
        painter.end();

        QPainter net;
        net.begin(this);
            net.translate(Translate_X, Translate_Y);
            net.setPen(QPen(QBrush(QColor(0, 240, 0)), 1));

            net.drawLine(-X_Left/2, -Y_Down,  -X_Left/2, Y_Down);
            net.drawLine(X_Left/2,  -Y_Down,   X_Left/2, Y_Down);
            net.drawLine(-X_Left,   -Y_Down,  -X_Left,   Y_Down);
            net.drawLine(X_Left,    -Y_Down,   X_Left,   Y_Down);

            net.drawLine(-X_Left, -Y_Down,    X_Left, -Y_Down);
            net.drawLine(-X_Left,  Y_Down,    X_Left,  Y_Down);
            net.drawLine(-X_Left, -Y_Down/2,  X_Left, -Y_Down/2);
            net.drawLine(-X_Left,  Y_Down/2,  X_Left,  Y_Down/2);

        net.end();

        QPainter Graph_paint;
        Graph_paint.begin(this);

            Graph_paint.translate(Translate_X, Translate_Y);
            Graph_paint.setPen(QPen(QBrush(QColor(255, 255, 0)), 3));
            Graph_paint.setBrush(QBrush(QColor(255, 255, 0)));

            for(int i = 0; i<Koord.Y_List.size(); i++)
            {
                int y = int((Koord.Y_List[i] - Koord.Center_Y)*Koord.Y_Mash);
                int x = int((Koord.X_List[i] - Koord.Center_X)*Koord.X_Mash);

                Graph_paint.drawPoint(x, -y);
            }

        Graph_paint.end();

        QPainter number;
        number.begin(this);

            QFont Number_Font;
            Number_Font.setPixelSize(12);
            Number_Font.setBold(true);
            number.setFont(Number_Font);
            number.translate(Translate_X, Translate_Y);
            number.setPen(QPen(QBrush(Qt::black), 4));

            number.drawText(QRect(-20, 10, 35, 12),
                            Qt::AlignLeft, QString::number(Koord.Center_X));
            number.drawText(QRect(-20, 30, 35, 12),
                            Qt::AlignLeft, QString::number(Koord.Center_Y));

            number.drawText(QRect(X_Left/2-20, 10, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_X + Koord.X_Left)/2.0));
            number.drawText(QRect(X_Left/2-20, 30, 35, 12),
                            Qt::AlignLeft, QString::number(Koord.Center_Y));

            number.drawText(QRect(-X_Left/2-20, 10, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_X + Koord.X_Right)/2.0));
            number.drawText(QRect(-X_Left/2-20, 30, 35, 12),
                            Qt::AlignLeft, QString::number(Koord.Center_Y));

            number.drawText(QRect(-20, Y_Down/2+10, 35, 12),
                            Qt::AlignLeft, QString::number(Koord.Center_X));
            number.drawText(QRect(-20, Y_Down/2+30, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_Y + Koord.Y_Up)/2.0));

            number.drawText(QRect(-20, -Y_Down/2+10, 35, 12),
                            Qt::AlignLeft, QString::number(Koord.Center_X));
            number.drawText(QRect(-20, -Y_Down/2+30, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_Y + Koord.Y_Down)/2.0));

            number.drawText(QRect(X_Left/2-20, Y_Down/2+10, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_X + Koord.X_Left)/2.0));
            number.drawText(QRect(X_Left/2-20, Y_Down/2+30, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_Y + Koord.Y_Up)/2.0));

            number.drawText(QRect(-X_Left/2-20, Y_Down/2+10, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_X + Koord.X_Right)/2.0));
            number.drawText(QRect(-X_Left/2-20, Y_Down/2+30, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_Y + Koord.Y_Up)/2.0));

            number.drawText(QRect(X_Left/2-20, -Y_Down/2+10, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_X + Koord.X_Left)/2.0));
            number.drawText(QRect(X_Left/2-20, -Y_Down/2+30, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_Y + Koord.Y_Down)/2.0));

            number.drawText(QRect(-X_Left/2-20, -Y_Down/2+10, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_X + Koord.X_Right)/2.0));
            number.drawText(QRect(-X_Left/2-20, -Y_Down/2+30, 35, 12),
                            Qt::AlignLeft, QString::number((float)(Koord.Center_Y + Koord.Y_Down)/2.0));
        number.end();
}

void XY_Graphic::Y_UP_Slot(int up)
{
    Koord.Y_Up = up;
    Koord.Center_Y = (float)(Koord.Y_Up + Koord.Y_Down)/2.0;
    Koord.Y_Mash   = (double)(500.0/(Koord.Y_Up   - Koord.Y_Down));
    repaint();
}

void XY_Graphic::Y_Down_Slot(int down)
{
    Koord.Y_Down = down;
    Koord.Center_Y = (float)(Koord.Y_Up + Koord.Y_Down)/2.0;
    Koord.Y_Mash   = (double)(500.0/(Koord.Y_Up   - Koord.Y_Down));
    repaint();
}

void XY_Graphic::X_Left_Slot(int left)
{
    Koord.X_Left = left;
    Koord.Center_X = (float)(Koord.X_Left + Koord.X_Right)/2.0;
    Koord.X_Mash   = (double)(500.0/(Koord.X_Right - Koord.X_Left));
    repaint();
}

void XY_Graphic::X_Right_Slot(int right)
{
    Koord.X_Right = right;
    Koord.Center_X = (float)(Koord.X_Left + Koord.X_Right)/2.0;
    Koord.X_Mash   = (double)(500.0/(Koord.X_Right - Koord.X_Left));
    repaint();
}

void XY_Graphic::Get_Data(float X, float Y)
{
    Koord.X_List.push_back(Y);
    Koord.Y_List.push_back(X);
    repaint();
}

void XY_Graphic::Clear()
{
    Koord.X_List.clear();
    Koord.Y_List.clear();
}
