#ifndef GYRO_H
#define GYRO_H

#include <Graphic/graphic.h>

class Gyro_Formular : public Graphic
{
    Q_OBJECT
public:
    Gyro_Formular();
    ~Gyro_Formular();

public slots:
    void Parse_ACCEL_Slot(const struct ACCEL &);
};

#endif // GYRO_H
