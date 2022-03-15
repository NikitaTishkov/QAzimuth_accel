#include "Com_Accel.h"
#include "ui_Com_Accel.h"

Com_Accel::Com_Accel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Com_Accel)
{
    ui->setupUi(this);

    CAG = new Com_Accel_Graphic(ui->frame);
}

Com_Accel::~Com_Accel()
{
    delete ui;
}

void Com_Accel::Accel_Deg_SLOT(float Acc, char Status)
{
    this->Accel = Acc + (float)ui->DIF_Spin->value();
    ui->Accel_V->setText(QString::number(Accel));
    CAG->Accel_animate(Accel, Status);

    ui->Dif->setText(QString::number((double)this->Com-Accel));
}

void Com_Accel::Parse_POHPR_Slot(const struct POHPR &POHPR)
{
    ui->Compas_V->setText(QString::number(POHPR.pitch));
    CAG->Com_animate(POHPR.pitch, POHPR.status);
    this->Com = POHPR.pitch;
}
