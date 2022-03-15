#ifndef POUGT_FORMULAR_H
#define POUGT_FORMULAR_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <Graphic/Graphic_Widget.h>

#include <lib/NMEA_Struct.h>
#include <Graphic/graphic.h>

class POUGT_Formular : public Graphic
{
    Q_OBJECT
public:
    explicit POUGT_Formular();
    ~POUGT_Formular();

signals:

public slots:

private slots:
    void Parse_POUGT_Slot(const struct POUGT &);
    virtual void Find_Slot();
private:
    QString Find_Text;
protected:

};

#endif // POUGT_FORMULAR_H
