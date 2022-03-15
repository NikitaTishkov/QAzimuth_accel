#include "parse_nmea.h"
#include <QStringList>
#include <stdio.h>


Parse_NMEA::Parse_NMEA(QMenu *menu, QObject *parent) :
    QObject(parent)
{
    menuNMEA = menu;
    NMEA_Select();

    memset(&ctx, 0, sizeof(BmUartProtoNmea));
    memset(&NMEA_Data_Settings, 0, sizeof(struct NMEA_Data));

    Read_Settings();
}

void Parse_NMEA::Parse(const QString &Text_NMEA)
{
    NMEA_D = NMEA_Data_Settings;

    char data[4096];
    memset(data, 0, 4096);

    strcpy(data, Text_NMEA.toLocal8Bit().data());

    nmea_recv(&ctx, data, strlen(data), &NMEA_D);

    if(NMEA_D.ACCEL.Status == 'A')
        emit Parse_ACCEL_Signal(NMEA_D.ACCEL);
}

void Parse_NMEA::Parse_Accel_Slot(const QString &Text_NMEA, struct ACCEL &ACCEL)
{
    char data[4096];
    memset(data, 0, 4096);

    strcpy(data, Text_NMEA.toLocal8Bit().data());

    struct NMEA_Data N;
    N.ACCEL.X_V = 1;
    nmea_recv(&ctx, data, strlen(data), &N);

    ACCEL = N.ACCEL;
}

Parse_NMEA::~Parse_NMEA()
{
    Settings.beginGroup("/NMEA_sentence");
        Settings.setValue("/ACCEL",   NMEA_Data_Settings.ACCEL.X_V);
    Settings.endGroup();
}

void Parse_NMEA::Read_Settings()
{
    Settings.beginGroup("/NMEA_sentence");
        NMEA_Data_Settings.ACCEL.X_V        = Settings.value("/ACCEL").toBool();
    Settings.endGroup();

    Settings.beginGroup("/NMEA_sentence");
        NMEA_Actions[0]->setChecked(Settings.value("/ACCEL").toBool());
    Settings.endGroup();
}

void Parse_NMEA::NMEA_Select()
{
    menuNMEA->addAction("ACCEL");

    NMEA_Actions = menuNMEA->actions();

    for(int i=0; i<NMEA_Actions.size(); i++)
        NMEA_Actions[i]->setCheckable(true);

    connect(menuNMEA, SIGNAL(triggered(QAction*)), this, SLOT(OnOFF_NMEA()));
}

void Parse_NMEA::OnOFF_NMEA()
{
        if(NMEA_Actions[10]->isChecked())
            NMEA_Data_Settings.ACCEL.X_V = 1;
        else
            NMEA_Data_Settings.ACCEL.X_V = 0;
}

QByteArray Parse_NMEA::Make_NMEA(struct ACCEL &Accel)
{
    char nmea[100];
    NmeaFormat(nmea, sizeof nmea, "ACCEL,%0.3f,%02d,%02d,%02d,%02d,%02d,%02d",
                  Accel.T,
                  (int) Accel.X_V,
                  (int) Accel.Y_V,
                  (int) Accel.Z_V,
                  (int) Accel.X_G,
                  (int) Accel.Y_G,
                  (int) Accel.Z_G
                  );
    QByteArray Data;
    Data.push_back(nmea);

    return Data;
}
