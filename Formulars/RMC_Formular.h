#ifndef RMC_FORMULAR_H
#define RMC_FORMULAR_H

#include <Graphic/graphic.h>

class RMC_Formular : public Graphic
{
    Q_OBJECT
public:
    RMC_Formular();
    ~RMC_Formular();
public slots:
    void Parse_GPRMC_Signal(const struct GPRMC &);
};

#endif // RMC_FORMULAR_H
