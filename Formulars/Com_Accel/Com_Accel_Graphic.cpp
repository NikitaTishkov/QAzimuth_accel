#include "Com_Accel_Graphic.h"
#include <QPainter>

Com_Accel_Graphic::Com_Accel_Graphic(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(parent->size());

    X_Size = parent->width();
    Y_Size = parent->height();
}

Com_Accel_Graphic::~Com_Accel_Graphic()
{

}

void Com_Accel_Graphic::paintEvent(QPaintEvent *event)
{
    QPainter pain;
        pain.begin(this);
            pain.fillRect(event->rect(), QBrush(QColor(12, 108, 134)));
        pain.end();

    qreal Translate_X = X_Size/2, Translate_Y = Y_Size/2;
    qreal X_Left = -Translate_X+10, Y_Down = -Translate_Y+10;
    qreal Round = 5;

    QPainter painter;

    painter.begin(this);

        painter.translate(Translate_X, Translate_Y);

        painter.setPen(QPen(QBrush(QColor(255, 255, 255)), 2));

        painter.drawChord(X_Left, Y_Down, -X_Left*2, -Y_Down*2, 90*16, -180*16);

        QFont Font;
        Font.setPixelSize(14);
        painter.setFont(Font);

        for(int i = 0; i<36; i++)
        {
            painter.setPen(QPen(QBrush(QColor(255, 255, 255)), 1));
            painter.drawLine(0, Y_Down, 0, Y_Down+5);
            painter.rotate(5);
        }

        painter.rotate(180);
        for(int i = 0; i<7; i++)
        {
            painter.setPen(QPen(QBrush(Qt::white), 1));
            painter.drawText(QRect(-13, Y_Down+8, 26, 12), Qt::AlignCenter,
                             QString::number(i * 30 - 90) );

            painter.setPen(QPen(QBrush(QColor(255, 255, 255)), 2));
            painter.drawLine(0, Y_Down-5,  0, Y_Down+5);
            painter.drawLine(0, Y_Down+20, 0, Y_Down+25);
            painter.rotate(30);
        }

    painter.end();

    QPainter Com;
        Com.begin(this);
            Com.translate(Translate_X, Translate_Y);
            Com.rotate(-Com_Pitch);
            QBrush Com_brush(QColor(250,0,250));
            if(Com_Status != 'B' && Com_Status != 'A')
                Com_brush.setColor(Qt::red);
            Com.setPen(QPen(Com_brush, 5));
            Com.drawLine(Round, 0, -X_Left-25, 0);
            Com.drawLine(-X_Left-40, -10, -X_Left-25, 0);
            Com.drawLine(-X_Left-40,  10, -X_Left-25, 0);
            Com.drawLine(-Round, 0, X_Left+25, 0);
            Com.setBrush(QBrush(QColor(12, 108, 134)));
            Com.drawEllipse(-Round, -Round, Round*2, Round*2);
        Com.end();

        QPainter Accel;
            Accel.begin(this);
                Accel.translate(Translate_X, Translate_Y);
                Accel.rotate(-Accel_Pitch);
                QBrush Accel_brush(Qt::white);
                if(Accel_Status != 'B' && Accel_Status != 'A')
                    Accel_brush.setColor(Qt::black);
                Accel.setPen(QPen(Accel_brush, 2));
                Accel.drawLine(Round, 0, -X_Left-25, 0);
                Accel.drawLine(-X_Left-40, -10, -X_Left-25, 0);
                Accel.drawLine(-X_Left-40,  10, -X_Left-25, 0);
                Accel.drawLine(-Round, 0, X_Left+25, 0);
                Accel.setBrush(QBrush(QColor(12, 108, 134)));
                Accel.drawEllipse(-Round, -Round, Round*2, Round*2);
            Accel.end();
}

void Com_Accel_Graphic::Com_animate(float Pitch, char Status)
{
    Com_Pitch = Pitch;
    Com_Status = Status;
    repaint();
}

void Com_Accel_Graphic::Accel_animate(float Pitch, char Status)
{
    Accel_Pitch = Pitch;
    Accel_Status = Status;
    repaint();
}
