#include "Accel_Formular.h"
#include <math.h>

#define PI 3.1415926535897932384
#define G 16384.0

Accel_Formular::Accel_Formular() : N(0)
{
    setWindowTitle("Accel");

    Graphic::Add_Graphic(-18000, 18000, "X");
    Graphic::Add_Graphic(-18000, 18000, "Y");
    Graphic::Add_Graphic(-18000, 18000, "Z");
    Graphic::Add_Graphic(-3000,  3000,  "H");
    Graphic::Add_Graphic(-50,    50,    "T");

}

Accel_Formular::~Accel_Formular()
{

}

void Accel_Formular::Parse_ACCEL_Slot(const struct ACCEL &ACCEL)
{

    float X = ACCEL.X_V;// * 1.008215 -1377.7;
    float Y = ACCEL.Y_V;// * 1.009177 -600.5;
    float Z = ACCEL.Z_V;// * 1.006635 -255.7;

    double H, Move;
    H = hypot(X, Y);

    Move = 16384.0 - (double)hypot(H, Z);

    Graphic::Build_Graphic(X,             ACCEL.Status, 0);
    Graphic::Build_Graphic(Y,             ACCEL.Status, 1);
    Graphic::Build_Graphic(Z,             ACCEL.Status, 2);
    Graphic::Build_Graphic(Move,          ACCEL.Status, 3);
    Graphic::Build_Graphic(ACCEL.T,       ACCEL.Status, 4);

}

inline void Accel_Formular::Filter(float &F0, const float &F1)
{
    F0 = (F0*N + F1)/(N+1);
}

void Accel_Formular::Filter_Accel(const struct ACCEL &A)
{
    Filter(AAccel.T, A.T);
    Filter(AAccel.X_V, (const float)A.X_V);
    Filter(AAccel.Y_V, (const float)A.Y_V);
    Filter(AAccel.Z_V, (const float)A.Z_V);
    Filter(AAccel.X_G, (const float)A.X_G);
    Filter(AAccel.Y_G, (const float)A.Y_G);
    Filter(AAccel.Z_G, (const float)A.Z_G);

    N++;

    if(N == 100000)
        N = 0;
}

struct ACCEL Accel_Formular::Make_NMEA()
{
    struct ACCEL Accel;
    if(N == 0)
    {
        Accel.Status = 'B';
        Accel.T   = 0;
        Accel.X_V = 0;
        Accel.Y_V = 0;
        Accel.Z_V = 0;
        Accel.X_G = 0;
        Accel.Y_G = 0;
        Accel.Z_G = 0;
    }
    else
    {
        Accel.Status = 'A';
        Accel.T   = AAccel.T;
        Accel.X_V = (quint32)AAccel.X_V;
        Accel.Y_V = (quint32)AAccel.Y_V;
        Accel.Z_V = (quint32)AAccel.Z_V;
        Accel.X_G = (quint32)AAccel.X_G;
        Accel.Y_G = (quint32)AAccel.Y_G;
        Accel.Z_G = (quint32)AAccel.Z_G;

        N = 0;
    }

    return Accel;
}
