
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QFile>
#include <QDockWidget>
#include <QSettings>

#include "parse_nmea.h"

#include <Formulars/Koord/Coord_QW.h>
//#include <Formulars/Course_Roll_Pitch/Course_Roll_Pitch.h>
#include <Formulars/POHPR/POHPR.h>
#include <Formulars/POUGT/POUGT_Formular.h>
#include <Formulars/Accel_Formular.h>
#include <Formulars/Gyro_Formular.h>
#include <Formulars/RMC_Formular.h>
#include <Formulars/Com_Accel/Com_Accel.h>
#include <Formulars/XY_Widget/XY_Area.h>
#include "language.h"

namespace Ui {
class MainWindow;
}


class Console;
class SettingsDialog;
class Panel_Buttons;
class Parse_NMEA;

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void Show_NMEA_Text(const QByteArray&);
    void Show_BINR_Text(const QByteArray&);
    void Sent_NMEA(QString&);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void Show_Hide_Slot(bool);
private slots:
    void openSerialPort_1();
    void closeSerialPort_1();
    void openSerialPort_2();
    void closeSerialPort_2();
    void about();
    void write_NMEA_Data_SLOT(const QString &);
    void write_BINR_Data_SLOT(const QString &);
    void write_BINR_Data_SLOT(const QByteArray &);
    void readDatafromPort_1();
    void readDatafromPort_2();
    void ACCEL_TO_Dialog(const struct POHPR &);
    void handleError(QSerialPort::SerialPortError error);
    void Enable_Connect(bool);
    void Resize_Slot(const QSize &);
    void Language_Change(QAction*);
    void ZDA_Slot(const struct POHPR &);
private:
    void init_Formular();
    void initActionsConnections();
    void NMEA_Select();

    QSettings Settings;
    void ReadSettings();
    void WriteSettings();

    QStringList Languiges();
    QStringList Language_File;

    Parse_NMEA *parse_nmea;

    bool BINR_NMEA;
    bool read_Accel;
    Ui::MainWindow *ui;
    Dialog              *dialog;
    SettingsDialog      *settings_1, *settings_2;
    QSerialPort         *serial_1, *serial_2;
    Parse_NMEA          *parse_NMEA;
    //QWidget             *pohpr;

    QScrollArea         *NMEA_Form;

    Accel_Formular      *Accel_F;
    Gyro_Formular       *Gyro_F;
    struct ACCEL         Accel;

    QByteArray          Accel_Byte;

    QWidget      *XY_Wid;
    QWidget      *Com_Accel_F;
protected:
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
