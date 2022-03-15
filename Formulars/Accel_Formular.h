#ifndef ACCEL_FORMULAR_H
#define ACCEL_FORMULAR_H

#include <Graphic/graphic.h>

class Accel_Formular : public Graphic
{
    Q_OBJECT
public:
    Accel_Formular();
    void Filter_Accel(const struct ACCEL &);
    ~Accel_Formular();
    struct ACCEL Make_NMEA();

public slots:
    void Parse_ACCEL_Slot(const struct ACCEL &);
signals:
    void Accel_Deg_SIGNAL(float, char );
private:
    struct Average_ACCEL{
        char    Status;
        float   T;
        float X_V;
        float Y_V;
        float Z_V;
        float X_G;
        float Y_G;
        float Z_G;
    };

    struct Average_ACCEL AAccel;
    quint32 N;
    inline void Filter(float &,  const float  &);
};

#endif // ACCEL_FORMULAR_H
