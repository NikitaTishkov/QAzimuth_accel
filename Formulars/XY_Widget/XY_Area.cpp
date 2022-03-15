#include "XY_Area.h"
#include "ui_XY_Area.h"

XY_Area::XY_Area(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XY_Area)
{
    ui->setupUi(this);
    setWindowTitle("XY_Area");

    XV_Wid = new XY_Widget(QString("X_V"));
    XG_Wid = new XY_Widget(QString("X_G"));
    YV_Wid = new XY_Widget(QString("Y_V"));
    YG_Wid = new XY_Widget(QString("Y_G"));
    ZV_Wid = new XY_Widget(QString("Z_V"));
    ZG_Wid = new XY_Widget(QString("Z_G"));

    ui->mdiArea->addSubWindow(XV_Wid);
    ui->mdiArea->addSubWindow(XG_Wid);
    ui->mdiArea->addSubWindow(YV_Wid);
    ui->mdiArea->addSubWindow(YG_Wid);
    ui->mdiArea->addSubWindow(ZV_Wid);
    ui->mdiArea->addSubWindow(ZG_Wid);
}

XY_Area::~XY_Area()
{
    delete ui;
}

void XY_Area::Parse_ACCEL_Slot(const struct ACCEL &A)
{
    XV_Wid->Get_Data(A.X_V, A.T);
    XG_Wid->Get_Data(A.X_G, A.T);
    YV_Wid->Get_Data(A.Y_V, A.T);
    YG_Wid->Get_Data(A.Y_G, A.T);
    ZV_Wid->Get_Data(A.Z_V, A.T);
    ZG_Wid->Get_Data(A.Z_G, A.T);
}

void XY_Area::Clear()
{
    XV_Wid->Clear();
    XG_Wid->Clear();
    YV_Wid->Clear();
    YG_Wid->Clear();
    ZV_Wid->Clear();
    ZG_Wid->Clear();
}

void XY_Area::resizeEvent(QResizeEvent *)
{
    ui->mdiArea->resize(this->width()-5, this->height()-5);
}
