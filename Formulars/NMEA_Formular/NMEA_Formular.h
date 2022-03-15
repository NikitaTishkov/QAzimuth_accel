#ifndef NMEA_FORMULAR_H
#define NMEA_FORMULAR_H

#include <QWidget>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QStringList>
#include <QGroupBox>
#include <QGridLayout>
#include <QFont>
#include <QCheckBox>

#include "lib/NMEA_Struct.h"

class NMEA_Formular : public QWidget
{
    Q_OBJECT
public:
    explicit NMEA_Formular();
signals:
    void Send_NMEA_Signal(const QString &);
public slots:
    void Parse_PODST(const struct POHPR &);
    void Parse_PONDM(const struct PONDM &);
    void Parse_PORZA(const struct PORZA &);
    void Parse_PNVGO(const struct PNVGO &);
    void Parse_PNVGVER(const struct PNVGVER &);
    void Parse_PNVGS(const struct PNVGS &);
    void Parse_PNVGR(const struct PNVGR &);
private slots:
    void PODST_CBox_Slot(int);
    void PORZA_CBox_Slot(int);
    void PNVGO_CBox_Slot(int);
    void PNVGS_CBox_Slot(int);
    void PNVGR_CBox_Slot(int);

    void Send_PODST_Slot();
    void Send_PONDM_Slot();
    void Send_PORZA_Slot();
    void Send_PORZB_Slot();
    void Send_PONGL_Slot();
    void Send_PNVGO_Slot();
    void Send_PNVGVER_Slot();
    void Send_PNVGUSB_Slot();
    void Send_PNVGRST_Slot();
    void Send_PNVGS_Slot();
    void Send_PNVGR_Slot();

private:
    QFont       Label_Font;
    QStringList ReqInst_List;

    QGridLayout     *PODST_GridLayout(void);
    QLabel          *PODST_Label_0;
    QLabel          *PODST_Label_1;
    QLabel          *PODST_Label_2;
    QLabel          *PODST_Label_3;
    QLabel          *PODST_Distance_Label_0;
    QDoubleSpinBox  *PODST_Spin_1;
    QDoubleSpinBox  *PODST_Spin_2;
    QDoubleSpinBox  *PODST_Spin_3;

    QGroupBox       *PONGL_GroupBox(void);
    QDoubleSpinBox  *PONGL_Course_SBox;
    QDoubleSpinBox  *PONGL_Pitch_SBox;
    QDoubleSpinBox  *PONGL_Roll_SBox;

    QGridLayout     *PONDM_GridLayout(void);
    QLabel          *PONDM_Course_Label;
    QLabel          *PONDM_Pitch_Label;
    QLabel          *PONDM_Roll_Label;
    QLabel          *PONDM_Distance_Label_1;
    QLabel          *PONDM_Distance_Label_2;
    QLabel          *PONDM_Distance_Label_3;

    QComboBox       *PORZA_PortSpeed_CBox;
    QLabel          *PORZA_Port_Label;

    QGroupBox       *PORZB_GroupBox(void);
    QComboBox       *PORZB_PORZV_CBox;
    QComboBox       *PORZB_GGA_CBox;
    QComboBox       *PORZB_ZDA_CBox;
    QComboBox       *PORZB_POHPR_CBox;
    QComboBox       *PORZB_RMC_CBox;
    QComboBox       *PORZB_HDT_CBox;
    QComboBox       *PORZB_GLL_CBox;
    QComboBox       *PORZB_POUGT_CBox;
    QComboBox       *PORZB_POUGC_CBox;

    QGridLayout     *PNVGO_GridLayout(void);
    QDoubleSpinBox  *PNVGO_Pitch_Spin;
    QLabel          *PNVGO_Pitch_Label;
    QDoubleSpinBox  *PNVGO_PitchI_Spin;
    QLabel          *PNVGO_PitchI_Label;

    QGroupBox       *PNVGVER_GroupBox(void);
    QLabel          *PNVGVER_Soft;
    QLabel          *PNVGVER_NSoft_1;
    QLabel          *PNVGVER_NSoft_2;
    QLabel          *PNVGVER_NSoft_3;
    QLabel          *PNVGVER_Linux_Kernel;

    QComboBox       *PNVGUSB_CB;

    QComboBox       *PNVGRST_CB;

    QGridLayout     *PNVGS_GridLayout(void);
    QComboBox       *PNVGS_CB;
    QDoubleSpinBox  *PNVGS_Loss;
    QDoubleSpinBox  *PNVGS_Seach;
    QLabel          *PNVGS_Loss_Label;
    QLabel          *PNVGS_Seach_Label;

    QGroupBox       *PNVGR_GridLayout(void);
    QComboBox       *PNVGR_CB;
    QCheckBox       *PNVGR_Roll_CBox;
    QCheckBox       *PNVGR_Course_CBox;
    QCheckBox       *PNVGR_TimeSoul_CBox;
    QCheckBox       *PNVGR_Regimen_CBox;
    QLabel          *PNVGR_Roll_Label;
    QLabel          *PNVGR_Course_Label;
    QLabel          *PNVGR_TimeSoul_Label;
    QLabel          *PNVGR_Regimen_Label;
};

#endif // NMEA_FORMULAR_H
