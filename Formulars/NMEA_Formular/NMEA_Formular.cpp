#include "NMEA_Formular.h"

#define Button_Size 80
#define ComboBox_Size 90
#define GButton_Size 70

NMEA_Formular::NMEA_Formular()
{
    setFixedHeight(900);
    Label_Font.setBold(true);

    ReqInst_List << tr("Request") << tr("Install");

    QPushButton *PORZA_Button   = new QPushButton("PORZA");
        PORZA_Button->setFixedWidth(Button_Size);
    QComboBox *PORZA_CBox       = new QComboBox;
        PORZA_CBox->setFixedWidth(ComboBox_Size);
        PORZA_CBox->addItems(ReqInst_List);
    QLabel *PORZA_PortSpeed     = new QLabel(tr("NMEA Boudrate: "));
        PORZA_PortSpeed->setAlignment(Qt::AlignRight);

    QStringList Port_Speed_List;
        Port_Speed_List << "9600" << "19200" << "38400" << "115200";

    PORZA_PortSpeed_CBox        = new QComboBox();
        PORZA_PortSpeed_CBox->addItems(Port_Speed_List);
        PORZA_PortSpeed_CBox->hide();
    PORZA_Port_Label            = new QLabel("?");
        PORZA_Port_Label->setFont(Label_Font);
        PORZA_Port_Label->setAlignment(Qt::AlignLeft);

    QPushButton *PNVGUSB_Button     = new QPushButton("PNVGUSB");
        PNVGUSB_Button->setFixedWidth(Button_Size);
    QStringList PNVGUSB_List;
        PNVGUSB_List << tr("Mass Storage") << tr("Ethernet") << tr("None");
    PNVGUSB_CB = new QComboBox;
        PNVGUSB_CB->addItems(PNVGUSB_List);

    QPushButton *PNVGRST_Button     = new QPushButton("PNVGRST");
        PNVGRST_Button->setFixedWidth(Button_Size);
    QStringList PNVGRST_List;
        PNVGRST_List << tr("Application") << tr("System");
    PNVGRST_CB = new QComboBox;
        PNVGRST_CB->addItems(PNVGRST_List);

    QGridLayout *GridL = new QGridLayout;
    GridL->addLayout(PODST_GridLayout(),        0,  0, 2, 6);
    GridL->addWidget(PONGL_GroupBox(),          3,  0, 3, 6);
    GridL->addLayout(PONDM_GridLayout(),        6,  0, 2, 6);
    GridL->addWidget(PORZA_Button,              8,  0, 1, 1);
    GridL->addWidget(PORZA_CBox,                8,  1, 1, 1);
    GridL->addWidget(PORZA_PortSpeed,           8,  2, 1, 2);
    GridL->addWidget(PORZA_PortSpeed_CBox,      8,  4, 1, 2);
    GridL->addWidget(PORZA_Port_Label,          8,  4, 1, 2);
    GridL->addWidget(this->PORZB_GroupBox(),    9,  0, 4, 6);
    GridL->addLayout(this->PNVGO_GridLayout(),  13,  0, 2, 6);
    GridL->addWidget(this->PNVGVER_GroupBox(),  15,  0, 4, 6);
    GridL->addWidget(PNVGUSB_Button,            19,  0, 1, 1);
    GridL->addWidget(PNVGUSB_CB,                19,  1, 1, 1);
    GridL->addWidget(PNVGRST_Button,            20, 0, 1, 1);
    GridL->addWidget(PNVGRST_CB,                20, 1, 1, 1);
    GridL->addLayout(PNVGS_GridLayout(),        21, 0, 2, 6);
    GridL->addWidget(PNVGR_GridLayout(),        23, 0, 2, 6);
    this->setLayout(GridL);

    connect(PORZA_CBox,     SIGNAL(currentIndexChanged(int)), this, SLOT(PORZA_CBox_Slot(int)));

    connect(PORZA_Button,   SIGNAL(clicked()), this, SLOT(Send_PORZA_Slot()));
    connect(PNVGUSB_Button, SIGNAL(clicked()), this, SLOT(Send_PNVGUSB_Slot()));
    connect(PNVGRST_Button, SIGNAL(clicked()), this, SLOT(Send_PNVGRST_Slot()));
}

QGridLayout* NMEA_Formular::PODST_GridLayout(void)
{
    QPushButton *PODST_Button   = new QPushButton("PODST");
        PODST_Button->setFixedWidth(Button_Size);
    QComboBox *PODST_CBox       = new QComboBox;
        PODST_CBox->setFixedWidth(ComboBox_Size);
        PODST_CBox->addItem(tr("Calibrate"));
        PODST_CBox->addItem(tr("Install"));

    PODST_Label_0 = new QLabel(tr("Status:"));
        PODST_Label_0->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    PODST_Distance_Label_0 = new QLabel("?");
        PODST_Distance_Label_0->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        PODST_Distance_Label_0->setFont(Label_Font);

    PODST_Label_1 = new QLabel(tr("Length №1:"));
        PODST_Label_1->setAlignment(Qt::AlignRight);
        PODST_Label_1->hide();
    PODST_Spin_1 = new QDoubleSpinBox();
        PODST_Spin_1->setValue(50);
        PODST_Spin_1->setMaximum(99999);
        PODST_Spin_1->setMinimum(0);
        PODST_Spin_1->setDecimals(1);
        PODST_Spin_1->setSuffix(tr(" mm"));
        PODST_Spin_1->setAlignment(Qt::AlignRight);
        PODST_Spin_1->hide();

    PODST_Label_2 = new QLabel(tr("Length №2:"));
        PODST_Label_2->setAlignment(Qt::AlignRight);
        PODST_Label_2->hide();
    PODST_Spin_2 = new QDoubleSpinBox();
        PODST_Spin_2->setMaximum(99999);
        PODST_Spin_2->setMinimum(0);
        PODST_Spin_2->setDecimals(1);
        PODST_Spin_2->setSuffix(tr(" mm"));
        PODST_Spin_2->setAlignment(Qt::AlignRight);
        PODST_Spin_2->hide();

    PODST_Label_3 = new QLabel(tr("Length №3:"));
        PODST_Label_3->setAlignment(Qt::AlignRight);
        PODST_Label_3->hide();
    PODST_Spin_3 = new QDoubleSpinBox();
        PODST_Spin_3->setMaximum(99999);
        PODST_Spin_3->setMinimum(0);
        PODST_Spin_3->setDecimals(1);
        PODST_Spin_3->setSuffix(tr(" mm"));
        PODST_Spin_3->setAlignment(Qt::AlignRight);
        PODST_Spin_3->hide();

    QGridLayout *PODST_GL = new QGridLayout;
        PODST_GL->addWidget(PODST_Button,              0, 0, 3, 1);
        PODST_GL->addWidget(PODST_CBox,                0, 1, 3, 1);
        PODST_GL->addWidget(PODST_Label_0,             0, 2, 3, 1);
        PODST_GL->addWidget(PODST_Distance_Label_0,    0, 3, 3, 1);
        PODST_GL->addWidget(PODST_Label_1,             0, 2, 1, 1);
        PODST_GL->addWidget(PODST_Spin_1,              0, 3, 1, 1);
        PODST_GL->addWidget(PODST_Label_2,             1, 2, 1, 1);
        PODST_GL->addWidget(PODST_Spin_2,              1, 3, 1, 1);
        PODST_GL->addWidget(PODST_Label_3,             2, 2, 1, 1);
        PODST_GL->addWidget(PODST_Spin_3,              2, 3, 1, 1);

    connect(PODST_CBox,     SIGNAL(currentIndexChanged(int)), this, SLOT(PODST_CBox_Slot(int)));
    connect(PODST_Button,   SIGNAL(clicked()), this, SLOT(Send_PODST_Slot()));

    return PODST_GL;
}

QGroupBox* NMEA_Formular::PONGL_GroupBox(void)
{
    QPushButton *PONGL_Button   = new QPushButton("PONGL");
        PONGL_Button->setFixedWidth(70);
    QLabel *PONGL_Course_L      = new QLabel(tr("Course correct: "));
        PONGL_Course_L->setAlignment(Qt::AlignRight);
    PONGL_Course_SBox           = new QDoubleSpinBox();
        PONGL_Course_SBox->setDecimals(2);
        PONGL_Course_SBox->setMinimum(-90);
        PONGL_Course_SBox->setMaximum(90);
        PONGL_Course_SBox->setSuffix(tr(" deg"));
    QLabel *PONGL_Pitch_L      = new QLabel(tr("Pitch correct: "));
        PONGL_Pitch_L->setAlignment(Qt::AlignRight);
    PONGL_Pitch_SBox           = new QDoubleSpinBox();
        PONGL_Pitch_SBox->setDecimals(2);
        PONGL_Pitch_SBox->setMinimum(-90);
        PONGL_Pitch_SBox->setMaximum(90);
        PONGL_Pitch_SBox->setSuffix(tr(" deg"));
    QLabel *PONGL_Roll_L      = new QLabel(tr("Roll correct: "));
        PONGL_Roll_L->setAlignment(Qt::AlignRight);
    PONGL_Roll_SBox           = new QDoubleSpinBox();
        PONGL_Roll_SBox->setDecimals(2);
        PONGL_Roll_SBox->setMinimum(-90);
        PONGL_Roll_SBox->setMaximum(90);
        PONGL_Roll_SBox->setSuffix(tr(" deg"));

    QGridLayout *PONGL_GL = new QGridLayout();
        PONGL_GL->addWidget(PONGL_Button,          0, 0, 3, 1);
        PONGL_GL->addWidget(PONGL_Course_L,        0, 1, 1, 1);
        PONGL_GL->addWidget(PONGL_Course_SBox,     0, 2, 1, 1);
        PONGL_GL->addWidget(PONGL_Roll_L,          1, 1, 1, 1);
        PONGL_GL->addWidget(PONGL_Roll_SBox,       1, 2, 1, 1);
        PONGL_GL->addWidget(PONGL_Pitch_L,         2, 1, 1, 1);
        PONGL_GL->addWidget(PONGL_Pitch_SBox,      2, 2, 1, 1);

    QGroupBox *PONGL_Box = new QGroupBox();
        PONGL_Box->setLayout(PONGL_GL);

    connect(PONGL_Button,   SIGNAL(clicked()), this, SLOT(Send_PONGL_Slot()));

    return PONGL_Box;
}

QGridLayout* NMEA_Formular::PONDM_GridLayout(void)
{
    QPushButton *PONDM_Button   = new QPushButton("PONDM");
        PONDM_Button->setFixedWidth(80);
    QLabel *PONDM_Course   = new QLabel(tr("Course: "));
        PONDM_Course->setAlignment(Qt::AlignRight);
    PONDM_Course_Label     = new QLabel("?");
        PONDM_Course_Label->setFont(Label_Font);
        PONDM_Course_Label->setAlignment(Qt::AlignLeft);
    QLabel *PONDM_Pitch    = new QLabel(tr("Pitch: "));
        PONDM_Pitch->setAlignment(Qt::AlignRight);
    PONDM_Pitch_Label      = new QLabel("?");
        PONDM_Pitch_Label->setFont(Label_Font);
        PONDM_Pitch_Label->setAlignment(Qt::AlignLeft);
    QLabel *PONDM_Roll     = new QLabel(tr("Roll: "));
        PONDM_Roll->setAlignment(Qt::AlignRight);
    PONDM_Roll_Label       = new QLabel("?");
        PONDM_Roll_Label->setFont(Label_Font);
        PONDM_Roll_Label->setAlignment(Qt::AlignLeft);
    QLabel *PONDM_Distance_1 = new QLabel(tr("Distanse №1: "));
        PONDM_Distance_1->setAlignment(Qt::AlignRight);
    PONDM_Distance_Label_1   = new QLabel("?");
        PONDM_Distance_Label_1->setFont(Label_Font);
        PONDM_Distance_Label_1->setAlignment(Qt::AlignLeft);
    QLabel *PONDM_Distance_2 = new QLabel(tr("Distanse №2: "));
        PONDM_Distance_2->setAlignment(Qt::AlignRight);
    PONDM_Distance_Label_2   = new QLabel("?");
        PONDM_Distance_Label_2->setFont(Label_Font);
        PONDM_Distance_Label_2->setAlignment(Qt::AlignLeft);
    QLabel *PONDM_Distance_3 = new QLabel(tr("Distanse №3: "));
         PONDM_Distance_3->setAlignment(Qt::AlignRight);
    PONDM_Distance_Label_3   = new QLabel("?");
         PONDM_Distance_Label_3->setFont(Label_Font);
         PONDM_Distance_Label_3->setAlignment(Qt::AlignLeft);

    QGridLayout *PONDM_GL = new QGridLayout();
        PONDM_GL->addWidget(PONDM_Button,           0, 0, 3, 1);
        PONDM_GL->addWidget(PONDM_Course,           0, 1, 1, 2);
        PONDM_GL->addWidget(PONDM_Course_Label,     0, 3, 1, 1);
        PONDM_GL->addWidget(PONDM_Distance_1,       0, 4, 1, 1);
        PONDM_GL->addWidget(PONDM_Distance_Label_1, 0, 5, 1, 1);
        PONDM_GL->addWidget(PONDM_Roll,             1, 1, 1, 2);
        PONDM_GL->addWidget(PONDM_Roll_Label,       1, 3, 1, 1);
        PONDM_GL->addWidget(PONDM_Distance_2,       1, 4, 1, 1);
        PONDM_GL->addWidget(PONDM_Distance_Label_2, 1, 5, 1, 1);
        PONDM_GL->addWidget(PONDM_Pitch,            2, 1, 1, 2);
        PONDM_GL->addWidget(PONDM_Pitch_Label,      2, 3, 1, 1);
        PONDM_GL->addWidget(PONDM_Distance_3,       2, 4, 1, 1);
        PONDM_GL->addWidget(PONDM_Distance_Label_3, 2, 5, 1, 1);

    connect(PONDM_Button,   SIGNAL(clicked()), this, SLOT(Send_PONDM_Slot()));
    return PONDM_GL;
}

QGroupBox* NMEA_Formular::PORZB_GroupBox()
{
    QPushButton *PORZB_Button   = new QPushButton("PORZB");
        PORZB_Button->setFixedWidth(70);
    QStringList PORZB_Period;

    PORZB_Period << "0.1" << "0.2" << "0.5" << "0" << "1" << "2" << "5" << "10";

    QLabel *PORZB_PORZV_L       = new QLabel("PORZV: ");
        PORZB_PORZV_L->setAlignment(Qt::AlignRight);
    PORZB_PORZV_CBox            = new QComboBox();
        PORZB_PORZV_CBox->addItem("0");
        PORZB_PORZV_CBox->addItem("1");

    QLabel *PORZB_GGA_L         = new QLabel("GGA: ");
        PORZB_GGA_L->setAlignment(Qt::AlignRight);
    PORZB_GGA_CBox              = new QComboBox();
        PORZB_GGA_CBox->addItems(PORZB_Period);
        PORZB_GGA_CBox->setCurrentIndex(3);

    QLabel *PORZB_POUGC_L       = new QLabel("POUGC: ");
        PORZB_POUGC_L->setAlignment(Qt::AlignRight);
    PORZB_POUGC_CBox            = new QComboBox();
        PORZB_POUGC_CBox->addItems(PORZB_Period);
        PORZB_POUGC_CBox->setCurrentIndex(3);

    QLabel *PORZB_ZDA_L         = new QLabel("ZDA: ");
        PORZB_ZDA_L->setAlignment(Qt::AlignRight);
    PORZB_ZDA_CBox              = new QComboBox();
        PORZB_ZDA_CBox->addItem("0");
        PORZB_ZDA_CBox->addItem("1");

    QLabel *PORZB_POHPR_L       = new QLabel("POHPR: ");
        PORZB_POHPR_L->setAlignment(Qt::AlignRight);
    PORZB_POHPR_CBox            = new QComboBox();
        PORZB_POHPR_CBox->addItems(PORZB_Period);
        PORZB_POHPR_CBox->setCurrentIndex(3);

    QLabel *PORZB_RMC_L         = new QLabel("RMC: ");
        PORZB_RMC_L->setAlignment(Qt::AlignRight);
    PORZB_RMC_CBox              = new QComboBox();
        PORZB_RMC_CBox->addItems(PORZB_Period);
        PORZB_RMC_CBox->setCurrentIndex(3);

    QLabel *PORZB_HDT_L         = new QLabel("HDT: ");
        PORZB_HDT_L->setAlignment(Qt::AlignRight);
    PORZB_HDT_CBox              = new QComboBox();
        PORZB_HDT_CBox->addItems(PORZB_Period);
        PORZB_HDT_CBox->setCurrentIndex(3);

    QLabel *PORZB_GLL_L         = new QLabel("GLL: ");
         PORZB_GLL_L->setAlignment(Qt::AlignRight);
    PORZB_GLL_CBox              = new QComboBox();
        PORZB_GLL_CBox->addItems(PORZB_Period);
        PORZB_GLL_CBox->setCurrentIndex(3);

    QLabel *PORZB_POUGT_L       = new QLabel("POUGT: ");
        PORZB_POUGT_L->setAlignment(Qt::AlignRight);
    PORZB_POUGT_CBox            = new QComboBox();
        PORZB_POUGT_CBox->addItems(PORZB_Period);
        PORZB_POUGT_CBox->setCurrentIndex(3);

    QGridLayout *PORZB_GL = new QGridLayout();
        PORZB_GL->addWidget(PORZB_Button,       0, 0, 4, 1);
        PORZB_GL->addWidget(PORZB_PORZV_L,      0, 1, 1, 1);
        PORZB_GL->addWidget(PORZB_PORZV_CBox,   0, 2, 1, 1);
        PORZB_GL->addWidget(PORZB_GGA_L,        0, 3, 1, 1);
        PORZB_GL->addWidget(PORZB_GGA_CBox,     0, 4, 1, 1);
        PORZB_GL->addWidget(PORZB_POUGC_L,      0, 5, 1, 1);
        PORZB_GL->addWidget(PORZB_POUGC_CBox,   0, 6, 1, 1);
        PORZB_GL->addWidget(PORZB_ZDA_L,        1, 1, 1, 1);
        PORZB_GL->addWidget(PORZB_ZDA_CBox,     1, 2, 1, 1);
        PORZB_GL->addWidget(PORZB_POHPR_L,      1, 3, 1, 1);
        PORZB_GL->addWidget(PORZB_POHPR_CBox,   1, 4, 1, 1);
        PORZB_GL->addWidget(PORZB_RMC_L,        2, 1, 1, 1);
        PORZB_GL->addWidget(PORZB_RMC_CBox,     2, 2, 1, 1);
        PORZB_GL->addWidget(PORZB_HDT_L,        2, 3, 1, 1);
        PORZB_GL->addWidget(PORZB_HDT_CBox,     2, 4, 1, 1);
        PORZB_GL->addWidget(PORZB_GLL_L,        3, 1, 1, 1);
        PORZB_GL->addWidget(PORZB_GLL_CBox,     3, 2, 1, 1);
        PORZB_GL->addWidget(PORZB_POUGT_L,      3, 3, 1, 1);
        PORZB_GL->addWidget(PORZB_POUGT_CBox,   3, 4, 1, 1);

    QGroupBox *PORZB_Box = new QGroupBox();
        PORZB_Box->setLayout(PORZB_GL);

    connect(PORZB_Button,   SIGNAL(clicked()), this, SLOT(Send_PORZB_Slot()));

    return PORZB_Box;
}

QGridLayout* NMEA_Formular::PNVGO_GridLayout(void)
{
    QPushButton *PNVGO_Button   = new QPushButton("PNVGO");
        PNVGO_Button->setFixedWidth(Button_Size);
    QComboBox *PNVGO_CBox       = new QComboBox();
        PNVGO_CBox->setFixedWidth(ComboBox_Size);
        PNVGO_CBox->addItems(ReqInst_List);
    QLabel *PNVGO_Pitch_L       = new QLabel(tr("Pitch: "));
        PNVGO_Pitch_L->setAlignment(Qt::AlignRight);
    PNVGO_Pitch_Spin            = new QDoubleSpinBox();
        PNVGO_Pitch_Spin->setDecimals(2);
        PNVGO_Pitch_Spin->setValue(35);
        PNVGO_Pitch_Spin->setMaximum(90);
        PNVGO_Pitch_Spin->setMinimum(-90);
        PNVGO_Pitch_Spin->setSuffix(tr(" deg"));
        PNVGO_Pitch_Spin->hide();
    PNVGO_Pitch_Label = new QLabel("?");
        PNVGO_Pitch_Label->setAlignment(Qt::AlignLeft);
        PNVGO_Pitch_Label->setFont(Label_Font);
    QLabel *PNVGO_PitchI_L        = new QLabel(tr("Primary pitch: "));
        PNVGO_PitchI_L->setAlignment(Qt::AlignRight);
    PNVGO_PitchI_Spin             = new QDoubleSpinBox();
        PNVGO_PitchI_Spin->setDecimals(2);
        PNVGO_PitchI_Spin->setMaximum(90);
        PNVGO_PitchI_Spin->setMinimum(-90);
        PNVGO_PitchI_Spin->setSuffix(tr(" deg"));
        PNVGO_PitchI_Spin->hide();
    PNVGO_PitchI_Label = new QLabel("?");
        PNVGO_PitchI_Label->setAlignment(Qt::AlignLeft);
        PNVGO_PitchI_Label->setFont(Label_Font);

    QGridLayout *PNVGO_GL = new QGridLayout();
        PNVGO_GL->addWidget(PNVGO_Button,          0, 0, 2, 1);
        PNVGO_GL->addWidget(PNVGO_CBox,            0, 1, 2, 1);
        PNVGO_GL->addWidget(PNVGO_Pitch_L,         0, 2, 1, 1);
        PNVGO_GL->addWidget(PNVGO_Pitch_Spin,      0, 3, 1, 1);
        PNVGO_GL->addWidget(PNVGO_Pitch_Label,     0, 3, 1, 1);
        PNVGO_GL->addWidget(PNVGO_PitchI_L,        1, 2, 1, 1);
        PNVGO_GL->addWidget(PNVGO_PitchI_Spin,     1, 3, 1, 1);
        PNVGO_GL->addWidget(PNVGO_PitchI_Label,    1, 3, 1, 1);

        connect(PNVGO_CBox,   SIGNAL(currentIndexChanged(int)), this, SLOT(PNVGO_CBox_Slot(int)));
        connect(PNVGO_Button, SIGNAL(clicked()),                this, SLOT(Send_PNVGO_Slot()));

        return PNVGO_GL;
}

QGroupBox* NMEA_Formular::PNVGVER_GroupBox(void)
{
    QPushButton *PNVGVER_Button     = new QPushButton("PNVGVER");
        PNVGVER_Button->setFixedWidth(Button_Size-5);
    QLabel *PNVGVER_S               = new QLabel(tr("Software version: "));
        PNVGVER_S->setAlignment(Qt::AlignRight);
    PNVGVER_Soft                    = new QLabel("?");
        PNVGVER_Soft->setAlignment(Qt::AlignLeft);
        PNVGVER_Soft->setFont(Label_Font);
    QLabel *PNVGVER_NS_1            = new QLabel(tr("Navigation receiver №1: "));
        PNVGVER_NS_1->setAlignment(Qt::AlignRight);
    PNVGVER_NSoft_1                 = new QLabel("?");
        PNVGVER_NSoft_1->setAlignment(Qt::AlignLeft);
        PNVGVER_NSoft_1->setFont(Label_Font);
    QLabel *PNVGVER_NS_2            = new QLabel(tr("Navigation receiver №2: "));
        PNVGVER_NS_2->setAlignment(Qt::AlignRight);
    PNVGVER_NSoft_2                 = new QLabel("?");
        PNVGVER_NSoft_2->setAlignment(Qt::AlignLeft);
        PNVGVER_NSoft_2->setFont(Label_Font);
    QLabel *PNVGVER_NS_3            = new QLabel(tr("Navigation receiver №3: "));
        PNVGVER_NS_3->setAlignment(Qt::AlignRight);
    PNVGVER_NSoft_3                 = new QLabel("?");
        PNVGVER_NSoft_3->setAlignment(Qt::AlignLeft);
        PNVGVER_NSoft_3->setFont(Label_Font);
    QLabel *PNVGVER_Linux_K         = new QLabel(tr("Linux Kernel:"));
        PNVGVER_Linux_K->setAlignment(Qt::AlignRight);
    PNVGVER_Linux_Kernel                    = new QLabel("?");
        PNVGVER_Linux_Kernel->setAlignment(Qt::AlignLeft);
        PNVGVER_Linux_Kernel->setFont(Label_Font);

    QGridLayout *PNVGVER_GL = new QGridLayout();
        PNVGVER_GL->addWidget(PNVGVER_Button,        0, 0, 5, 1);
        PNVGVER_GL->addWidget(PNVGVER_S,             0, 1, 1, 1);
        PNVGVER_GL->addWidget(PNVGVER_Soft,          0, 2, 1, 1);
        PNVGVER_GL->addWidget(PNVGVER_NS_1,          1, 1, 1, 1);
        PNVGVER_GL->addWidget(PNVGVER_NSoft_1,       1, 2, 1, 1);
        PNVGVER_GL->addWidget(PNVGVER_NS_2,          2, 1, 1, 1);
        PNVGVER_GL->addWidget(PNVGVER_NSoft_2,       2, 2, 1, 1);
        PNVGVER_GL->addWidget(PNVGVER_NS_3,          3, 1, 1, 1);
        PNVGVER_GL->addWidget(PNVGVER_NSoft_3,       3, 2, 1, 1);
        PNVGVER_GL->addWidget(PNVGVER_Linux_K,       4, 1, 1, 1);
        PNVGVER_GL->addWidget(PNVGVER_Linux_Kernel,  4, 2, 1, 1);

    QGroupBox *PNVGVER_Box = new QGroupBox();
        PNVGVER_Box->setLayout(PNVGVER_GL);

    connect(PNVGVER_Button, SIGNAL(clicked()), this, SLOT(Send_PNVGVER_Slot()));

    return PNVGVER_Box;
}

QGridLayout* NMEA_Formular::PNVGS_GridLayout(void)
{
    QPushButton *PNVGS_Button       = new QPushButton("PNVGS");
        PNVGS_Button->setFixedWidth(Button_Size);
            QPalette p = PNVGS_Button->palette();
            p.setColor(QPalette::Button, QColor(Qt::red));
        PNVGS_Button->setPalette(p);
    PNVGS_CB = new QComboBox;
        PNVGS_CB->addItems(ReqInst_List);

    QLabel *Loss_Label = new QLabel(tr("Loss solutions: "));
    PNVGS_Loss_Label = new QLabel("?");
        PNVGS_Loss_Label->setFont(Label_Font);
    PNVGS_Loss = new QDoubleSpinBox();
        PNVGS_Loss->setRange(0.001,0.999);
        PNVGS_Loss->setSingleStep(0.01);
        PNVGS_Loss->setDecimals(3);
        PNVGS_Loss->setSuffix(" m");
        PNVGS_Loss->hide();

    QLabel *Seach_Label = new QLabel(tr("Seach solutions: "));
    PNVGS_Seach_Label = new QLabel("?");
        PNVGS_Seach_Label->setFont(Label_Font);
    PNVGS_Seach = new QDoubleSpinBox();
        PNVGS_Seach->setRange(0.001,0.999);
        PNVGS_Seach->setSingleStep(0.01);
        PNVGS_Seach->setDecimals(3);
        PNVGS_Seach->setSuffix(" m");
        PNVGS_Seach->hide();

    QGridLayout *PNVGS_GL = new QGridLayout();
        PNVGS_GL->addWidget(PNVGS_Button,           0, 0, 2, 1);
        PNVGS_GL->addWidget(PNVGS_CB,               0, 1, 2, 1);
        PNVGS_GL->addWidget(Loss_Label,             0, 2, 1, 1);
        PNVGS_GL->addWidget(PNVGS_Loss_Label,       0, 3, 1, 1);
        PNVGS_GL->addWidget(PNVGS_Loss,             0, 3, 1, 1);
        PNVGS_GL->addWidget(Seach_Label,            1, 2, 1, 1);
        PNVGS_GL->addWidget(PNVGS_Seach_Label,      1, 3, 1, 1);
        PNVGS_GL->addWidget(PNVGS_Seach,            1, 3, 1, 1);

    connect(PNVGS_Button, SIGNAL(clicked()), this, SLOT(Send_PNVGS_Slot()));

    connect(PNVGS_CB, SIGNAL(currentIndexChanged(int)), this, SLOT(PNVGS_CBox_Slot(int)));

    return PNVGS_GL;
}

QGroupBox* NMEA_Formular::PNVGR_GridLayout(void)
{
    QPushButton *PNVGR_Button = new QPushButton("PNVGR");
        PNVGR_Button->setFixedWidth(Button_Size);
            QPalette p = PNVGR_Button->palette();
            p.setColor(QPalette::Button, QColor(Qt::red));
        PNVGR_Button->setPalette(p);

    PNVGR_CB = new QComboBox();
        PNVGR_CB->addItems(ReqInst_List);

    PNVGR_Roll_CBox      = new QCheckBox(tr("Roll"));
        PNVGR_Roll_CBox->hide();
    PNVGR_Roll_Label = new QLabel("?");
        PNVGR_Roll_Label->setFont(Label_Font);

    PNVGR_Course_CBox    = new QCheckBox(tr("Course"));
        PNVGR_Course_CBox->hide();
    PNVGR_Course_Label = new QLabel("?");
        PNVGR_Course_Label->setFont(Label_Font);

    PNVGR_TimeSoul_CBox  = new QCheckBox(tr("Time Solution"));
        PNVGR_TimeSoul_CBox->hide();
    PNVGR_TimeSoul_Label = new QLabel("?");
        PNVGR_TimeSoul_Label->setFont(Label_Font);

    PNVGR_Regimen_CBox   = new QCheckBox(tr("Test"));
        PNVGR_Regimen_CBox->hide();
    PNVGR_Regimen_Label = new QLabel("?");
        PNVGR_Regimen_Label->setFont(Label_Font);

    QGridLayout *PNVGR_GL = new QGridLayout();
        PNVGR_GL->addWidget(PNVGR_Button,           0, 0, 2, 1);
        PNVGR_GL->addWidget(PNVGR_CB,               0, 1, 2, 1);
        PNVGR_GL->addWidget(PNVGR_Roll_Label,       0, 2, 1, 1);
        PNVGR_GL->addWidget(PNVGR_Roll_CBox,        0, 2, 1, 1);
        PNVGR_GL->addWidget(PNVGR_Course_Label,     0, 3, 1, 1);
        PNVGR_GL->addWidget(PNVGR_Course_CBox,      0, 3, 1, 1);
        PNVGR_GL->addWidget(PNVGR_TimeSoul_Label,   1, 2, 1, 1);
        PNVGR_GL->addWidget(PNVGR_TimeSoul_CBox,    1, 2, 1, 1);
        PNVGR_GL->addWidget(PNVGR_Regimen_Label,    1, 3, 1, 1);
        PNVGR_GL->addWidget(PNVGR_Regimen_CBox,     1, 3, 1, 1);

    QGroupBox *PNVGR_Box = new QGroupBox();
        PNVGR_Box->setLayout(PNVGR_GL);

    connect(PNVGR_Button,  SIGNAL(clicked()), this, SLOT(Send_PNVGR_Slot()));

    connect(PNVGR_CB, SIGNAL(currentIndexChanged(int)), this, SLOT(PNVGR_CBox_Slot(int)));

    return PNVGR_Box;
}

void NMEA_Formular::PODST_CBox_Slot(int CB)
{
    if(CB == 0)
    {
        PODST_Label_0->show();
        PODST_Distance_Label_0->show();
        PODST_Label_1->hide();
        PODST_Spin_1->hide();
        PODST_Label_2->hide();
        PODST_Spin_2->hide();
        PODST_Label_3->hide();
        PODST_Spin_3->hide();
    }
    else
    {
        PODST_Label_0->hide();
        PODST_Distance_Label_0->hide();
        PODST_Label_1->show();
        PODST_Spin_1->show();
        PODST_Label_2->show();
        PODST_Spin_2->show();
        PODST_Label_3->show();
        PODST_Spin_3->show();
    }
}

void NMEA_Formular::Send_PONGL_Slot()
{
    QString R = "PONGL," + QString::number(PONGL_Course_SBox->value()) + "," +
                           QString::number(PONGL_Roll_SBox->value())  + "," +
                           QString::number(PONGL_Pitch_SBox->value());
    emit Send_NMEA_Signal(R);
}

void NMEA_Formular::PORZA_CBox_Slot(int CB)
{
    if(CB == 0)
    {
        PORZA_PortSpeed_CBox->hide();
        PORZA_Port_Label->show();
    }
    else
    {
        PORZA_PortSpeed_CBox->show();
        PORZA_Port_Label->hide();
    }
}

void NMEA_Formular::PNVGO_CBox_Slot(int CB)
{
    if(CB == 0)
    {
        PNVGO_Pitch_Spin->hide();
        PNVGO_PitchI_Spin->hide();
        PNVGO_Pitch_Label->show();
        PNVGO_PitchI_Label->show();
    }
    else
    {
        PNVGO_Pitch_Spin->show();
        PNVGO_PitchI_Spin->show();
        PNVGO_Pitch_Label->hide();
        PNVGO_PitchI_Label->hide();
    }
}

void NMEA_Formular::PNVGS_CBox_Slot(int CB)
{
    if(CB == 0)
    {
        PNVGS_Loss_Label->show();
        PNVGS_Loss->hide();
        PNVGS_Seach_Label->show();
        PNVGS_Seach->hide();
    }
    else
    {
        PNVGS_Loss_Label->hide();
        PNVGS_Loss->show();
        PNVGS_Seach_Label->hide();
        PNVGS_Seach->show();
    }
}

void NMEA_Formular::PNVGR_CBox_Slot(int CB)
{
    if(CB == 0)
    {
        PNVGR_Roll_CBox->hide();
        PNVGR_Roll_Label->show();
        PNVGR_Course_CBox->hide();
        PNVGR_Course_Label->show();
        PNVGR_TimeSoul_CBox->hide();
        PNVGR_TimeSoul_Label->show();
        PNVGR_Regimen_CBox->hide();
        PNVGR_Regimen_Label->show();
    }
    else
    {
        PNVGR_Roll_CBox->show();
        PNVGR_Roll_Label->hide();
        PNVGR_Course_CBox->show();
        PNVGR_Course_Label->hide();
        PNVGR_TimeSoul_CBox->show();
        PNVGR_TimeSoul_Label->hide();
        PNVGR_Regimen_CBox->show();
        PNVGR_Regimen_Label->hide();
    }
}


void NMEA_Formular::Send_PODST_Slot()
{
    if(PODST_Spin_1->isHidden())
         emit Send_NMEA_Signal("PODST");
    else
    {
        QString PODST_1 = QString::number(PODST_Spin_1->value());
        if(PODST_Spin_2->value() == 0 || PODST_Spin_3->value() == 0)
        {

            emit Send_NMEA_Signal("PODST," + PODST_1 + ",,");
        }
        else
        {
        QString PODST_2 = QString::number(PODST_Spin_2->value());
        QString PODST_3 = QString::number(PODST_Spin_3->value());
        emit Send_NMEA_Signal("PODST," + PODST_1 + "," + PODST_2 + "," + PODST_3);
        }
    }
}

void NMEA_Formular::Send_PONDM_Slot()
{
        emit Send_NMEA_Signal("PONDM");
}

void NMEA_Formular::Send_PORZA_Slot()
{
    if(PORZA_PortSpeed_CBox->isHidden())
        emit Send_NMEA_Signal("PORZA");
    else
    {
        QString Boudrate = PORZA_PortSpeed_CBox->currentText();
        emit Send_NMEA_Signal("PORZA,1," + Boudrate + ",1");
    }
}

void NMEA_Formular::Send_PORZB_Slot()
{
    QString R;

    if(PORZB_PORZV_CBox->currentIndex())
        R += ",PORZV," + PORZB_PORZV_CBox->currentText();
    if(PORZB_GGA_CBox->currentIndex() != 3)
        R += ",GGA," + PORZB_GGA_CBox->currentText();
    if(PORZB_POUGC_CBox->currentIndex() != 3)
        R += ",POUGC," + PORZB_POUGC_CBox->currentText();
    if(PORZB_ZDA_CBox->currentIndex())
        R += ",ZDA," + PORZB_ZDA_CBox->currentText();
    if(PORZB_POHPR_CBox->currentIndex() != 3)
        R += ",POHPR," + PORZB_POHPR_CBox->currentText();
    if(PORZB_RMC_CBox->currentIndex() != 3)
        R += ",RMC," + PORZB_RMC_CBox->currentText();
    if(PORZB_HDT_CBox->currentIndex() != 3)
        R += ",HDT," + PORZB_HDT_CBox->currentText();
    if(PORZB_GLL_CBox->currentIndex() != 3)
        R += ",GLL," + PORZB_GLL_CBox->currentText();
    if(PORZB_POUGT_CBox->currentIndex() != 3)
        R += ",POUGT," + PORZB_POUGT_CBox->currentText();

    emit Send_NMEA_Signal("PORZB"+R);
}

void NMEA_Formular::Send_PNVGO_Slot()
{
    if(PNVGO_Pitch_Spin->isHidden())
        emit Send_NMEA_Signal("PNVGO");
    else
    {
        QString Pitch  = QString::number(PNVGO_Pitch_Spin->value());
        QString PitchI = QString::number(PNVGO_PitchI_Spin->value());

        emit Send_NMEA_Signal("PNVGO," + Pitch + "," + PitchI);
    }
}

void NMEA_Formular::Send_PNVGVER_Slot()
{
    emit Send_NMEA_Signal("PNVGVER");
}

void NMEA_Formular::Send_PNVGUSB_Slot()
{
    QString PNVGUSB;
    if(PNVGUSB_CB->currentIndex() == 0)
        PNVGUSB = "S";
    if(PNVGUSB_CB->currentIndex() == 1)
        PNVGUSB = "E";
    if(PNVGUSB_CB->currentIndex() == 2)
        PNVGUSB = "N";

    emit Send_NMEA_Signal("PNVGUSB," + PNVGUSB);
}

void NMEA_Formular::Send_PNVGRST_Slot()
{
    QString PNVGRST;
    if(PNVGRST_CB->currentIndex() == 0)
        PNVGRST = "A";
    if(PNVGRST_CB->currentIndex() == 1)
        PNVGRST = "S";

    emit Send_NMEA_Signal("PNVGRST," + PNVGRST);
}

void NMEA_Formular::Send_PNVGS_Slot()
{
    QString PNVGS;
    if(PNVGS_CB->currentIndex() == 1)
        PNVGS = "," + QString::number(PNVGS_Loss->value()) + ","
                    + QString::number(PNVGS_Seach->value());

    emit Send_NMEA_Signal("PNVGS" + PNVGS);
}

void NMEA_Formular::Send_PNVGR_Slot()
{
    QString PNVGR_String;
    quint8 PNVGR = 0;

    if(PNVGR_CB->currentIndex() == 1)
    {
        if(PNVGR_Roll_CBox->isChecked())
            PNVGR |= 1;
        if(PNVGR_Course_CBox->isChecked())
            PNVGR |= 2;
        if(PNVGR_TimeSoul_CBox->isChecked())
            PNVGR |= 4;
        if(PNVGR_Regimen_CBox->isChecked())
            PNVGR |= 8;

        PNVGR_String = "PNVGR," + QString::number(PNVGR) + ",0.000";

    }
    else
        PNVGR_String = "PNVGR";

    emit Send_NMEA_Signal(PNVGR_String);
}


void NMEA_Formular::Parse_PODST(const struct POHPR &POHPR)
{
    PODST_Distance_Label_0->setText(QString::fromLocal8Bit(&POHPR.status));
}

void NMEA_Formular::Parse_PONDM(const struct PONDM &PONDM)
{
    PONDM_Course_Label      ->setText(QString::number(PONDM.Course));
    PONDM_Pitch_Label       ->setText(QString::number(PONDM.Pitch));
    PONDM_Roll_Label        ->setText(QString::number(PONDM.Roll));
    PONDM_Distance_Label_1  ->setText(QString::number(PONDM.Distance_1));
    PONDM_Distance_Label_2  ->setText(QString::number(PONDM.Distance_2));
    PONDM_Distance_Label_3  ->setText(QString::number(PONDM.Distance_3));
}

void NMEA_Formular::Parse_PORZA(const struct PORZA &PORZA)
{
    PORZA_Port_Label->setText(QString::number(PORZA.Boudrate));
}

void NMEA_Formular::Parse_PNVGO(const struct PNVGO &PNVGO)
{
    PNVGO_Pitch_Label->setText(QString::number(PNVGO.Pitch));
    PNVGO_PitchI_Label->setText(QString::number(PNVGO.PitchI));
}

void NMEA_Formular::Parse_PNVGVER(const struct PNVGVER &PNVGVER)
{
    PNVGVER_Soft   ->setText(QString::fromLocal8Bit(PNVGVER.PNVGVER_Soft));
    PNVGVER_NSoft_1->setText(QString::fromLocal8Bit(PNVGVER.PNVGVER_NSoft_1, 5));
    PNVGVER_NSoft_2->setText(QString::fromLocal8Bit(PNVGVER.PNVGVER_NSoft_2, 5));

    QString NSoft_3(QString::fromLocal8Bit(PNVGVER.PNVGVER_NSoft_3, 5));
    if(NSoft_3[0] != 0)
        PNVGVER_NSoft_3->setText(NSoft_3);
    else
        PNVGVER_NSoft_3->setText("     ");

    PNVGVER_Linux_Kernel->setText(QString::fromLocal8Bit(PNVGVER.PNVGVER_Linux_Kernel));
}

void NMEA_Formular::Parse_PNVGS(const struct PNVGS &PNVGS)
{
    PNVGS_Loss_Label ->setText(QString::number(PNVGS.Loss,  'g', 4));
    PNVGS_Seach_Label->setText(QString::number(PNVGS.Seach, 'g', 4));
}

void NMEA_Formular::Parse_PNVGR(const struct PNVGR &PNVGR)
{
    if(PNVGR.Status & 1)
        PNVGR_Roll_Label->setText(tr("Roll"));
    else
        PNVGR_Roll_Label->setText("");

    if(PNVGR.Status & 2)
        PNVGR_Course_Label->setText(tr("Course"));
    else
        PNVGR_Course_Label->setText("");

    if(PNVGR.Status & 4 )
        PNVGR_TimeSoul_Label->setText(tr("Time Soul"));
    else
        PNVGR_TimeSoul_Label->setText("");

    if(PNVGR.Status & 8)
        PNVGR_Regimen_Label->setText(tr("Test"));
    else
        PNVGR_Regimen_Label->setText("");
}
