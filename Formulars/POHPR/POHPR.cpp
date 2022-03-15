#include "POHPR.h"

#define Min_H 220
#define HEIGHT 100

POHPR_W::POHPR_W()
{
    Graphic::Add_Graphic(0, 360, "Course");
    Graphic::Add_Graphic(-90, 90, "Roll");
    Graphic::Add_Graphic(-90, 90, "Pitch");

    Graphic::Add_Time_Label();
}


POHPR_W::~POHPR_W()
{

}


void POHPR_W::Parse_POHPR_Slot(const struct POHPR &POHPR)
{
        Graphic::Build_Graphic(POHPR.course,   POHPR.status, 0);
        Graphic::Build_Graphic(POHPR.roll,     POHPR.status, 1);
        Graphic::Build_Graphic(POHPR.pitch,    POHPR.status, 2);

        Graphic::Write_Time(POHPR.time);
}


