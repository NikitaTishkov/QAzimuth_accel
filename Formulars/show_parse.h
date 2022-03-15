#ifndef SHOW_PARSE_H
#define SHOW_PARSE_H

#include <QWidget>
#include <QLineEdit>
#include "lib/NMEA_Struct.h"

class Show_parse : public QWidget
{
    Q_OBJECT
private:
    QLineEdit *qle_1;
    QLineEdit *qle_2;
    QLineEdit *qle_3;
    QLineEdit *qle_4;
public:
    explicit Show_parse(QWidget *parent = 0);
    
signals:
    
public slots:
    void Parse_POHPR_Slot(const struct POHPR &);
};

#endif // SHOW_PARSE_H
