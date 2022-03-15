#include "Gyro_Formular.h"

Gyro_Formular::Gyro_Formular()
{
    Graphic::Add_Graphic(-18000, 18000, "X");
    Graphic::Add_Graphic(-18000, 18000, "Y");
    Graphic::Add_Graphic(-18000, 18000, "Z");
    Graphic::Add_Graphic(-50,    50,    "T");
}

Gyro_Formular::~Gyro_Formular()
{

}

void Gyro_Formular::Parse_ACCEL_Slot(const struct ACCEL &ACCEL)
{
    Graphic::Build_Graphic(ACCEL.X_G,     ACCEL.Status, 0);
    Graphic::Build_Graphic(ACCEL.Y_G,     ACCEL.Status, 1);
    Graphic::Build_Graphic(ACCEL.Z_G,     ACCEL.Status, 2);

    Graphic::Build_Graphic(ACCEL.T,       ACCEL.Status, 3);
}
