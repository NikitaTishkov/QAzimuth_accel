#ifndef POHPR_W_H
#define POHPR_W_H

#include <QWidget>
#include <QPaintEvent>
#include <QVector>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QMenu>
#include <QAction>
#include <QSettings>

#include <lib/NMEA_Struct.h>
#include <Graphic/graphic.h>

#include <Formulars/Accel_Formular.h>

class POHPR_W : public Graphic
{
    Q_OBJECT
public:
    explicit POHPR_W();
    ~POHPR_W();
signals:

public slots:

private slots:
    void Parse_POHPR_Slot(const struct POHPR &);
private:
    QString Find_Text;


};

#endif // POHPR_W_H
