#include "Coord_QW.h"
#include <QFont>
#include <math.h>


Coord_QW::Coord_QW(QSettings &S, QWidget *parent) :
    QWidget(parent), A_Lat(0), A_Long(0), size(0)
{
    Settings = &S;
    QLabel *Time_L         = new QLabel(tr("Time:"));
    QLabel *Satelits_L     = new QLabel(tr("Satelits:"));
    QLabel *Current_Coord  = new QLabel(tr("Current coordinates: "));

            FON.setBold(true);
            Current_Coord->setFont(FON);
    QLabel *Lat_L          = new QLabel(tr("C_Lat: "));
    QLabel *Long_L         = new QLabel(tr("C_Long: "));
    QLabel *Average_Coord  = new QLabel(tr("Average coordinates: "));
            Average_Coord->setFont(FON);
    QLabel *Average_Long_L = new QLabel(tr("A_Long: "));
    QLabel *Average_Lat_L  = new QLabel(tr("A_Lat: "));
    QLabel *RMS_L          = new QLabel(tr("RMSD: "));
    QLabel *Scale          = new QLabel(tr("Scale: "));

    Time_VL         = new QLabel("0");
    Satelits_VL     = new QLabel("0");
    Dost_VL         = new QLabel("___________________");
    Long_VL         = new QLabel("0");
    Lat_VL          = new QLabel("0");
    Average_Long_VL = new QLabel("0");
    Average_Lat_VL  = new QLabel("0");
    RMS_VL          = new QLabel("0");

    QLabel *Lat_Spin_Label = new QLabel(tr("Lat:"));
    Lat_Spinbox = new QDoubleSpinBox();
        Lat_Spinbox->setMaximum(-90);
        Lat_Spinbox->setMaximum(90);
        Lat_Spinbox->setFixedWidth(110);
        Lat_Spinbox->setDecimals(7);
        Lat_Spinbox->setSingleStep(0.0000001);

    QLabel *Long_Spin_Label = new QLabel(tr("Long:"));
    Long_Spinbox = new QDoubleSpinBox();
        Long_Spinbox->setMaximum(-180);
        Long_Spinbox->setMaximum(180);
        Long_Spinbox->setFixedWidth(110);
        Long_Spinbox->setDecimals(7);
        Long_Spinbox->setSingleStep(0.0000001);

    QPushButton *Set_Center_Button = new QPushButton(tr("Set Center"));

    Scale_Spinbox    = new QDoubleSpinBox();
       Scale_Spinbox->setMaximum(100000);
       Scale_Spinbox->setMinimum(0.1);
       Scale_Spinbox->setValue(2);
       Scale_Spinbox->setFixedWidth(100);

    QPushButton *Clear_B = new QPushButton(tr("Clear"));

    QGridLayout *grid_l = new QGridLayout();
    grid_l->addWidget(Time_L,           1, 0);
    grid_l->addWidget(Time_VL,          1, 1);
    grid_l->addWidget(Satelits_L,       2, 0);
    grid_l->addWidget(Satelits_VL,      2, 1);
    grid_l->addWidget(Dost_VL,          3, 0, 1, 2);
    grid_l->addWidget(Current_Coord,    4, 0, 1, 2);
    grid_l->addWidget(Lat_L,            5, 0);
    grid_l->addWidget(Lat_VL,           5, 1);
    grid_l->addWidget(Long_L,           6, 0);
    grid_l->addWidget(Long_VL,          6, 1);
    grid_l->addWidget(Average_Coord,    7, 0, 1, 2);
    grid_l->addWidget(Average_Lat_L,    8, 0);
    grid_l->addWidget(Average_Lat_VL,   8, 1);
    grid_l->addWidget(Average_Long_L,   9, 0);
    grid_l->addWidget(Average_Long_VL,  9, 1);
    grid_l->addWidget(Set_Center_Button,10, 0);
    grid_l->addWidget(RMS_L,            11, 0);
    grid_l->addWidget(RMS_VL,           11, 1);
    grid_l->addWidget(Scale,            12, 0);
    grid_l->addWidget(Scale_Spinbox,    12, 1);
    grid_l->addWidget(Clear_B,          13, 0);

    visual_coord = new Visual_Coord();

    QGridLayout *grid_Graf = new QGridLayout();
        grid_Graf->addWidget(visual_coord,     0, 0, 1, 4);
        grid_Graf->addWidget(Lat_Spin_Label,   1, 0);
        grid_Graf->addWidget(Lat_Spinbox,      1, 1);
        grid_Graf->addWidget(Long_Spin_Label,  1, 2);
        grid_Graf->addWidget(Long_Spinbox,     1, 3);

    QHBoxLayout *qhb = new QHBoxLayout();
    qhb->addLayout(grid_Graf);
    qhb->addLayout(grid_l);
    setLayout(qhb);

    visual_coord->Set_Center_Lat_Slot(Lat_Spinbox->value());
    visual_coord->Set_Center_Long_Slot(Long_Spinbox->value());

    setFixedSize(525, 364);

    connect(Scale_Spinbox,  SIGNAL(valueChanged(double)),    visual_coord,  SLOT(Change_Mash_Slot(double)));
    connect(Clear_B,        SIGNAL(clicked()),               visual_coord,  SLOT(Clear_Slot()));
    connect(Clear_B,        SIGNAL(clicked()),               this,          SLOT(Clear_Slot()));
    connect(Lat_Spinbox,    SIGNAL(valueChanged(double)),    visual_coord,  SLOT(Set_Center_Lat_Slot(double)));
    connect(Long_Spinbox,   SIGNAL(valueChanged(double)),    visual_coord,  SLOT(Set_Center_Long_Slot(double)));
    connect(Set_Center_Button, SIGNAL(clicked()),            this,          SLOT(Set_Center()));

    Read_Setting();
}

Coord_QW::~Coord_QW()
{
    Settings->beginGroup("/Coord");
        Settings->setValue("/Lat",     Lat_Spinbox->value());
        Settings->setValue("/Long",    Long_Spinbox->value());
        Settings->setValue("/Scale",   Scale_Spinbox->value());
    Settings->endGroup();
}

void Coord_QW::Read_Setting()
{
    Settings->beginGroup("/Coord");
        Lat_Spinbox  ->setValue(Settings->value("/Lat").toDouble());
        Long_Spinbox ->setValue(Settings->value("/Long").toDouble());
        Scale_Spinbox->setValue(Settings->value("/Scale").toInt());
    Settings->endGroup();
}

void Coord_QW::Clear_Slot()
{
    this->A_Lat = 0;
    this->A_Long = 0;
    this->size = 0;

    Time_VL         ->setText("0");
    Long_VL         ->setText("0");
    Lat_VL          ->setText("0");
    Satelits_VL     ->setText("0");
    Dost_VL         ->setText(tr("___________________"));
    Average_Long_VL ->setText("0");
    Average_Lat_VL  ->setText("0");
    RMS_VL          ->setText("0");

    visual_coord->Set_Average_Slot(0, 0);
    visual_coord->repaint();
}

void Coord_QW::Set_Center()
{
    visual_coord->Set_Center_Lat_Slot(A_Lat);
    visual_coord->Set_Center_Long_Slot(A_Long);

    Lat_Spinbox ->setValue(A_Lat);
    Long_Spinbox->setValue(A_Long);
}
