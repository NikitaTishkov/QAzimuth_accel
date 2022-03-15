#include "XY_Widget.h"
#include "ui_XY_Widget.h"

XY_Widget::XY_Widget(QString Title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XY_Widget)
{
    ui->setupUi(this);
    setWindowTitle(Title);

    Graphic = new XY_Graphic;

    ui->verticalLayout->addWidget(Graphic);

    connect(ui->Y_UP,    SIGNAL(valueChanged(int)), Graphic, SLOT(Y_UP_Slot(int)));
    connect(ui->Y_Down,  SIGNAL(valueChanged(int)), Graphic, SLOT(Y_Down_Slot(int)));
    connect(ui->X_Left,  SIGNAL(valueChanged(int)), Graphic, SLOT(X_Left_Slot(int)));
    connect(ui->X_Right, SIGNAL(valueChanged(int)), Graphic, SLOT(X_Right_Slot(int)));
}

XY_Widget::~XY_Widget()
{
    delete ui;
}

void XY_Widget::Get_Data(float AC_X, float AC_Y)
{
    Data.X.push_back(AC_X);
    Data.Y.push_back(AC_Y);

    if(Data.X.size() == ui->Average_spinBox->value())
    {
        float X = 0, Y = 0;

        for(int i = 0; i < Data.X.size(); i++)
        {
            X = (X*i + Data.X[i])/(i+1);
            Y = (Y*i + Data.Y[i])/(i+1);
        }

        Graphic->Get_Data(X, Y);
        Data.X.clear();
        Data.Y.clear();
    }
}

void XY_Widget::Clear()
{
    Graphic->Clear();
}
