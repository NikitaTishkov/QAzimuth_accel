#include "POUGT_Formular.h"
#include <QGridLayout>
#include <QFont>
#include <math.h>

POUGT_Formular::POUGT_Formular()
{
    Graphic::Add_Graphic(-10, 10, "Line");
    Graphic::Add_Graphic(-50, 50, "Diff");

    Graphic::Add_Time_Label();
    Graphic::Add_Label("Satellite");
}

POUGT_Formular::~POUGT_Formular()
{

}

void POUGT_Formular::Parse_POUGT_Slot(const struct POUGT &POUGT)
{
    Graphic::Build_Graphic(POUGT.base_line, POUGT.status, 0);
    Graphic::Build_Graphic(POUGT.diff,      POUGT.status, 1);

    Graphic::Write_Time(POUGT.time);
    Graphic::Write_Data(int(POUGT.satellite),  0);
}


void POUGT_Formular::Find_Slot()
{
    Find_Text = "$POUGT, ";
}
