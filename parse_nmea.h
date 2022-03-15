#ifndef PARSE_NMEA_H
#define PARSE_NMEA_H

#include <QObject>
#include <QString>
#include <QMenu>
#include <QSettings>

#include "lib/NMEA_Struct.h"

class Parse_NMEA : public QObject
{
    Q_OBJECT
public:
    explicit Parse_NMEA(QMenu *, QObject *parent = 0);
    ~Parse_NMEA();
signals:
    void Parse_ACCEL_Signal(const struct ACCEL &);
public slots:
    void Parse(const QString &);
    void Parse_Accel_Slot(const QString &, struct ACCEL&);
    QByteArray Make_NMEA(struct ACCEL &);
    void OnOFF_NMEA();
private:
    struct NMEA_Data NMEA_D, NMEA_Data_Settings;
    BmUartProtoNmea ctx;
    QSettings Settings;
    void Read_Settings();
    QMenu *menuNMEA;
    QList<QAction*> NMEA_Actions;
    void NMEA_Select();
};

#endif // PARSE_NMEA_H
