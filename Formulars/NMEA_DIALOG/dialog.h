
#ifndef CONSOLE_H
#define CONSOLE_H

#include <QComboBox>
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QFile>
#include <QThread>
#include <QTimer>
#include <QSlider>
#include <QString>
#include <QSpinBox>
#include <QSettings>
#include <QDockWidget>

#include "Show_Text.h"
#include "../NMEA_Formular/NMEA_Formular.h"

class Read_File_Thread : public QThread
{
    Q_OBJECT
private:
    int period;
public:
    Read_File_Thread() : period(10) {};

    void run()
    {
        QTimer timer;
        connect(&timer, SIGNAL(timeout()), this, SLOT(Read()));
        timer.start((period));

        exec();
    }
signals:
    void Read_Line();
public slots:
    void Set_Period(int P)
    {
        period = P;
    }

    void Read()
    {
        emit Read_Line();
    }
};

class Dialog : public QWidget
{
    Q_OBJECT

signals:
    void Write_NMEA_Data_SIGNAL(const QString &);
    void Write_BINR_Data_SIGNAL(const QString &);
    void Parse_NMEA_Signal(const QString &);
    void Clear_Signal();
    void Push_Read_Buton_Signal(bool);
    void Read_All_Button_Signal();
    void Enable_Connect(bool);
    void Show_Hide_Signal(bool);
public:
    explicit Dialog(QSettings &, QWidget *parent = 0);
    ~Dialog();
    void setLocalEchoEnabled(bool);
    void Disable_Enable_Send(bool);

    NMEA_Formular *Get_NMEA_Formular(void);
public slots:
    void Find_Signal_Slot(double);
    void Read_Button_Settings(bool);
    void Get_NMEA_SLOT(const QString &);
    void Show_NMEA_Text(const QByteArray &);
    void Show_NMEA_Text_1(const QByteArray &);

protected:
    virtual void contextMenuEvent(QContextMenuEvent *e);
    void keyPressEvent(QKeyEvent *);

private:
    bool localEchoEnabled;
    QComboBox *Protocol_Choice;
    QLabel *Protocol_Znak;
    QLabel *Control_Sum_Label;
    QString NMEA_Text;
    QLabel  *File_Label;
    Show_Text_QW *Show_Text, *Show_Text_1;
    Show_Text_QW *Show_Hex;

    QFile Open_File;
    QFile Save_File;
    Read_File_Thread *read_thread;
    QSlider *slider;
    QSpinBox *spin;

    QComboBox *ComboBox;

    QPushButton *Save_File_Button;
    QPushButton *Read_File_Button;
    QPushButton *Read_All_Button;
    QPushButton *Text_Button, *Text_Button_1;
    QPushButton *Hex_Button;
    QPushButton *Open_File_Button;
    QPushButton *Clear_Button;

    QPushButton *Sent_NMEA;

    qint64 File_Size;

    QSettings *QA_Settings;

    NMEA_Formular *NMEA_F;

    void Save_File_Funk(QString);
    void Read_Dialog_ComboBox();
private slots:
    void Open_File_Slot();
    void Save_File_Slot();
    void Read_File_Slot();
    void Read_Stop_Slot(bool);
    void Read_All();
    void Peremotka_Slot(int);
    void Change_Slider(int);
    void Clear_Slot();

    void Control_Sum(const QString &);
    void Show_BINR_Text(const QByteArray &);
    void putData(void);
    void NMEA_BINR_SLOT(int);
};

#endif // CONSOLE_H
