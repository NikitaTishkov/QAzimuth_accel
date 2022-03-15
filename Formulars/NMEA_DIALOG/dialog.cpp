#include "dialog.h"
#include <QKeyEvent>
#include <QtCore/QDebug>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QSpinBox>
#include <QDateTime>
#include <QLineEdit>
#include <QPalette>

#define HEIGHT 30

Dialog::Dialog(QSettings &Settings, QWidget *parent)
    : QWidget(parent)
    , localEchoEnabled(true)
{
    QA_Settings = &Settings;
    ComboBox = new QComboBox;
    ComboBox->setEditable(true);
    ComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::red);
    ComboBox->setPalette(p);
    ComboBox->setMaximumHeight(HEIGHT);
    ComboBox->setMaxVisibleItems(5);

    Read_Dialog_ComboBox();

    Protocol_Choice = new QComboBox();
    QStringList Protocol_List;
    Protocol_List << "$" << "0x10";
    Protocol_Choice->addItems(Protocol_List);

    Protocol_Znak = new QLabel("*");
    Control_Sum_Label = new QLabel("00");
    Control_Sum_Label->setFrameStyle(QFrame::Sunken | QFrame::Panel);

    Sent_NMEA = new QPushButton(tr("Send"));
    Sent_NMEA->setMinimumHeight(HEIGHT);
    Sent_NMEA->setDisabled(true);

    File_Label = new QLabel("_________________");

    Show_Text = new Show_Text_QW;
    Show_Text->hide();

    Show_Text_1 = new Show_Text_QW;
    Show_Text_1->hide();
    QPalette Show_Text_Palette = Show_Text_1->palette();
    Show_Text_Palette.setColor(QPalette::Base, QColor(100, 255, 50, 255));
    Show_Text_1->setPalette(Show_Text_Palette);

    Show_Hex = new Show_Text_QW;
    Show_Hex->hide();
    QPalette Show_Hex_Palette = Show_Hex->palette();
    Show_Hex_Palette.setColor(QPalette::Base, QColor(100, 200, 255, 255));
    Show_Hex->setPalette(Show_Hex_Palette);

    Text_Button                     = new QPushButton(tr("&Text"));
    Text_Button->setCheckable(true);

    Text_Button_1                     = new QPushButton(tr("&Text_1"));
    Text_Button_1->setCheckable(true);

    Hex_Button                      = new QPushButton(tr("&Hex"));
    Hex_Button->setCheckable(true);

    Save_File_Button = new QPushButton(tr("&Save"));
    QPalette pal_blau = Save_File_Button->palette();
    pal_blau.setColor(QPalette::Button, QColor(0,154,255));
    Save_File_Button->setPalette(pal_blau);

    Open_File_Button  = new QPushButton(tr("&Open_File"));
    QSpinBox    *Read_Spinbox     = new QSpinBox();
    Read_File_Button              = new QPushButton(tr("&Read_File"));
    Read_File_Button->setDisabled(true);
    Read_File_Button->setCheckable(true);
    Read_All_Button              = new QPushButton(tr("Read_&All"));
    Read_All_Button->setDisabled(true);
    Read_All_Button->setCheckable(true);

    Clear_Button = new QPushButton(tr("&Clear"));

    Read_Spinbox->setMaximum(10000);
    Read_Spinbox->setMinimum(1);
    Read_Spinbox->setValue(10);
    Read_Spinbox->setSuffix(" ms");

    QHBoxLayout *QHB = new QHBoxLayout;
    QHB->addWidget(Protocol_Choice);
    QHB->addWidget(ComboBox);
    QHB->addWidget(Protocol_Znak);
    QHB->addWidget(Control_Sum_Label);
    QHB->addWidget(Sent_NMEA);

    QHBoxLayout *QHB_1 = new QHBoxLayout;
    QHB_1->addWidget(Text_Button);
    QHB_1->addWidget(Text_Button_1);
    QHB_1->addWidget(Hex_Button);
    QHB_1->addWidget(Save_File_Button);
    QHB_1->addWidget(Open_File_Button);
    QHB_1->addWidget(Read_Spinbox);
    QHB_1->addWidget(Read_File_Button);
    QHB_1->addWidget(Read_All_Button);
    QHB_1->addWidget(Clear_Button);

    slider = new QSlider(Qt::Horizontal);
        slider->setDisabled(true);
    spin   = new QSpinBox();
        spin->setDisabled(true);
        spin->setMinimum(0);
        spin->setMaximum(100);
        spin->setSuffix(" %");

    QHBoxLayout *QhB = new QHBoxLayout;
    QhB->addWidget(slider);
    QhB->addWidget(spin);

    QVBoxLayout *QVB = new QVBoxLayout;
        QVB->addLayout(QHB);
        QVB->addWidget(File_Label);
        QVB->addWidget(Show_Text);
        QVB->addWidget(Show_Text_1);
        QVB->addWidget(Show_Hex);
        QVB->addLayout(QHB_1);
        QVB->addLayout(QhB);
    setLayout(QVB);

    NMEA_F = new NMEA_Formular();

    read_thread = new Read_File_Thread();

    connect(ComboBox,  SIGNAL(editTextChanged(const QString &)),
            this,      SLOT(Control_Sum(const QString &)));

    connect(Text_Button,   SIGNAL(clicked(bool)), Show_Text,   SLOT(Show_Hide(bool)));
    connect(Text_Button_1, SIGNAL(clicked(bool)), Show_Text_1, SLOT(Show_Hide(bool)));

    connect(Hex_Button,  SIGNAL(clicked(bool)), Show_Hex, SLOT(Show_Hide(bool)));

    connect(Open_File_Button, SIGNAL(pressed()), this, SLOT(Open_File_Slot()));

    connect(Save_File_Button, SIGNAL(pressed()), this, SLOT(Save_File_Slot()));

    connect(Read_File_Button, SIGNAL(clicked(bool)),  this, SLOT(Read_Stop_Slot(bool)));

    connect(Read_All_Button,SIGNAL(clicked()),  this, SLOT(Read_All()));

    connect(Clear_Button, SIGNAL(clicked()), this, SLOT(Clear_Slot()));

    connect(Read_Spinbox, SIGNAL(valueChanged(int)), read_thread, SLOT(Set_Period(int)));

    connect(read_thread, SIGNAL(Read_Line()), this, SLOT(Read_File_Slot()));

    connect(Sent_NMEA, SIGNAL(clicked()), this, SLOT(putData()));

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(Peremotka_Slot(int)));

    connect(spin, SIGNAL(valueChanged(int)),   this, SLOT(Change_Slider(int)));

    connect(Protocol_Choice, SIGNAL(currentIndexChanged(int)), this, SLOT(NMEA_BINR_SLOT(int)));

    connect(NMEA_F, SIGNAL(Send_NMEA_Signal(const QString&)), this, SLOT(Get_NMEA_SLOT(const QString)));
}

Dialog::~Dialog()
{
    int S =     ComboBox->currentIndex();
    if(S < 4)
        S = 4;

    QA_Settings->beginGroup("/Dialog_ComboBox");
    QA_Settings->setValue("/Send_NMEA_0", ComboBox->itemText(S));
    QA_Settings->setValue("/Send_NMEA_1", ComboBox->itemText(S-1));
    QA_Settings->setValue("/Send_NMEA_2", ComboBox->itemText(S-2));
    QA_Settings->setValue("/Send_NMEA_3", ComboBox->itemText(S-3));
    QA_Settings->setValue("/Send_NMEA_4", ComboBox->itemText(S-4));
    QA_Settings->endGroup();

    delete(NMEA_F);
}

void Dialog::Read_Dialog_ComboBox()
{
    QA_Settings->beginGroup("/Dialog_ComboBox");
        QString S0 = QA_Settings->value("/Send_NMEA_0", "").toString();
        QString S1 = QA_Settings->value("/Send_NMEA_1", "").toString();
        QString S2 = QA_Settings->value("/Send_NMEA_2", "").toString();
        QString S3 = QA_Settings->value("/Send_NMEA_3", "").toString();
        QString S4 = QA_Settings->value("/Send_NMEA_4", "").toString();
    QA_Settings->endGroup();

    if(S0.size() > 0)
        ComboBox->addItem(S0);
    if(S1.size() > 0)
        ComboBox->addItem(S1);
    if(S2.size() > 0)
        ComboBox->addItem(S2);
    if(S3.size() > 0)
        ComboBox->addItem(S3);
    if(S4.size() > 0)
        ComboBox->addItem(S4);

    ComboBox->setCurrentIndex(4);

}

void Dialog::NMEA_BINR_SLOT(int click)
{
    ComboBox->clearEditText();
    if(click == 0)
    {
        Protocol_Znak->setText("*");
        Control_Sum_Label->show();
    }
    else
    {
        Protocol_Znak->setText("[10][03]");
        Control_Sum_Label->hide();
    }
}

void Dialog::Control_Sum(const QString &str)
{
  if(Protocol_Choice->currentIndex() == 0)
    {
        qint8 nmeaCRC = 0;

        for (int i = 0; i < str.length(); i++)
        {
            nmeaCRC ^= str.toLocal8Bit()[i];
        }

        QString B = QString::number(nmeaCRC, 16).toUpper();

        if(B.length()<2)
            B = "0"+B;

        B.resize(2);

        Control_Sum_Label->setText(B);

        NMEA_Text ="$"+str+"*"+B+"\r\n";
    }
    else
    {
        NMEA_Text ="10"+str+"1003";
    }
}

void Dialog::putData(void)
{
    if(Protocol_Choice->currentIndex() == 0)
    {
        emit Write_NMEA_Data_SIGNAL(NMEA_Text);
    }
    else
    {
        emit Write_BINR_Data_SIGNAL(NMEA_Text);
    }
}

void Dialog::Show_NMEA_Text(const QByteArray &Byte)
{
    QString Text  = QString::fromLocal8Bit(Byte);

    Show_Text->insertPlainText(Text);
    Show_Text->moveCursor(QTextCursor::End);

    if(Save_File.exists())
       Save_File.write(Text.toLocal8Bit());

    emit Parse_NMEA_Signal(Text);
}

void Dialog::Show_NMEA_Text_1(const QByteArray &Byte)
{
    QString Text  = QString::fromLocal8Bit(Byte);

    Show_Text_1->insertPlainText(Text);
    Show_Text_1->moveCursor(QTextCursor::End);
}


void Dialog::Show_BINR_Text(const QByteArray &Byte)
{
        QString Hex_String;
        for(int i = 0; i < Byte.size(); i++)
        {
            quint8 Z = Byte[i];
            QString H = QString::number(Z, 16);
            if(H.size() < 2)
                H = "0"+ H;
            Hex_String += H + " ";
        }
        Hex_String +="\r\n";
        Hex_String = Hex_String.toUpper();
        Show_Hex->moveCursor(QTextCursor::End);
        Show_Hex->insertPlainText(Hex_String);
}


void Dialog::setLocalEchoEnabled(bool set)
{
    localEchoEnabled = set;
}

void Dialog::Disable_Enable_Send(bool S)
{
    Sent_NMEA->setEnabled(S);

    if(S)
    {
        QPalette p = palette();
        p.setColor(QPalette::Base, Qt::black);
        p.setColor(QPalette::Text, Qt::green);
        ComboBox->setPalette(p);
    }
    else
    {
        QPalette p = palette();
        p.setColor(QPalette::Base, Qt::black);
        p.setColor(QPalette::Text, Qt::red);
        ComboBox->setPalette(p);
    }
}

void Dialog::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}

void Dialog::keyPressEvent(QKeyEvent *key)
{
    switch(key->key())
    {
        case Qt::Key_Return:
            Sent_NMEA->animateClick();
            break;
        case Qt::Key_T:
            Text_Button->animateClick();
            break;
        case Qt::Key_H:
            Hex_Button->animateClick();
            break;
        case Qt::Key_R:
            Read_File_Button->animateClick();
            break;
        case Qt::Key_A:
            Read_All_Button->animateClick();
            break;
        case Qt::Key_S:
            Save_File_Button->animateClick();
            break;
        case Qt::Key_O:
            Open_File_Button->animateClick();
            break;
        case Qt::Key_C:
            Clear_Button->animateClick();
            break;
    }
}

void Dialog::Read_Stop_Slot(bool checked)
{
    if(checked)
    {
        read_thread->start();
        emit Enable_Connect(false);

        Read_All_Button ->setEnabled(false);
        Open_File_Button->setEnabled(false);
        Clear_Button    ->setEnabled(false);
    }
    else
    {
        read_thread->quit();
        emit Enable_Connect(true);

        Read_All_Button ->setEnabled(true);
        Open_File_Button->setEnabled(true);
        Clear_Button    ->setEnabled(true);
    }

    emit Push_Read_Buton_Signal(checked);
}

void Dialog::Read_All()
{
    QByteArray data = Open_File.readAll();

    QString Text_NMEA = QString::fromLocal8Bit(data);

   Show_Text->insertPlainText(Text_NMEA);

   QStringList Text_NMEA_List = Text_NMEA.split("\n");

    Show_Text->hide();
    emit Show_Hide_Signal(false);

   for(int i = 0; i < Text_NMEA_List.size(); i++)
   {
       if(Text_NMEA_List[i].size() > 0)
       {
           QString Z = *(Text_NMEA_List[i].end() -1);

           if(Z != "\r")
           {
               Text_NMEA_List[i] += "\r";
           }

           emit Parse_NMEA_Signal(Text_NMEA_List[i] + "\n");
       }
   }

    Read_All_Button->setChecked(false);
    spin->setValue(100);
    slider->setValue(Open_File.pos());

    emit Read_All_Button_Signal();

     Text_Button->click();
    emit Show_Hide_Signal(true);
}

void Dialog::Read_File_Slot()
{
    QByteArray data = Open_File.readLine();

    int R = data.size();

    if(R >2 && data[R-2] != '\r')
        data.insert(R-1, '\r');

    slider->setValue(Open_File.pos());

    if(File_Size > 0)
    {
        int k = (Open_File.pos()*100)/File_Size;

        spin->setValue(k);

        if(k == 100)
            Read_File_Button->click();
    }
    else
        Read_File_Button->click();

        this->Show_NMEA_Text(data);
}

void Dialog::Open_File_Slot()
{
    this->setWindowTitle("");

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
    tr(".nme (*.nme)"));

        if (fileName != "")
        {
            Open_File.setFileName(fileName);
            if (!Open_File.open(QIODevice::ReadOnly))
            {
                QMessageBox::information(0, "Warning", "Error");
            }
            else
            {
                Read_File_Button->setEnabled(true);
                slider->setEnabled(true);
                spin->setEnabled(true);

                if(!Read_File_Button->isChecked())
                    Read_All_Button->setEnabled(true);

                slider->setRange(0, Open_File.size());

                File_Size = Open_File.size();

                File_Label->setText(fileName);
            }
        }
}

void Dialog::Save_File_Funk(QString fileName)
{
    if (fileName != "")
    {
        Save_File.setFileName(fileName);
        if (!Save_File.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(0, "Warning", "Error");
        }
        else
        {
            QTextStream stream(&Save_File);
            stream << Show_Text->toPlainText();
        }
    }
}

void Dialog::Save_File_Slot()
{
    QString date = QDate::currentDate().toString("yyyy.MM.dd");

#ifdef linux
    QString time = QTime::currentTime().toString("hh:mm");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), date + "_" + time + ".nme",
    tr("NMEA File (*.nme)"));
#else
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), date + ".nme",
    tr("NMEA File (*.nme)"));
#endif

    if (QFileInfo(fileName).suffix().isEmpty())
        fileName.append(".nme");

    Save_File_Funk(fileName);

    if(Save_File.isOpen())
    {
        QPalette pal_blau = Read_File_Button->palette();
        Save_File_Button->setPalette(pal_blau);
    }

    File_Label->setText(fileName);
}

void Dialog::Peremotka_Slot(int S)
{
    Open_File.seek(S);
}

void Dialog::Change_Slider(int S)
{
    if(!Read_File_Button->isChecked() && !Read_All_Button->isChecked())
    {
        int k = S*File_Size/100;
        slider->setValue(k);
    }
}

void Dialog::Clear_Slot()
{
    slider->setValue(0);
    spin->setValue(0);
    slider->setEnabled(false);
    spin->setEnabled(false);
    Read_File_Button->setEnabled(false);
    Read_All_Button->setEnabled(false);
    Show_Text->clear();
    Show_Hex->clear();

    File_Label->setText("_________________");

    emit Clear_Signal();
}

void Dialog::Find_Signal_Slot(double Cents)
{
    Show_Text->Find_Slot(Cents);
}

void Dialog::Read_Button_Settings(bool Enable)
{
    if(Open_File.isOpen())
    {
        Read_All_Button->setEnabled(Enable);
        Read_File_Button->setEnabled(Enable);
        slider->setEnabled(Enable);
        spin->setEnabled(Enable);
    }
}

void Dialog::Get_NMEA_SLOT(const QString &NMEA_String)
{
    ComboBox->setCurrentText(NMEA_String);
    Sent_NMEA->animateClick();
}

NMEA_Formular* Dialog::Get_NMEA_Formular(void)
{
    return NMEA_F;
}

