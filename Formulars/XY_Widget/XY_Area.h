#ifndef XY_AREA_H
#define XY_AREA_H

#include <QWidget>
#include "XY_Widget.h"

namespace Ui {
class XY_Area;
}

class XY_Area : public QWidget
{
    Q_OBJECT

public:
    explicit XY_Area(QWidget *parent = 0);
    ~XY_Area();

private:
    Ui::XY_Area *ui;
    XY_Widget *XV_Wid, *XG_Wid, *YV_Wid, *YG_Wid, *ZV_Wid, *ZG_Wid;
public slots:
    void Parse_ACCEL_Slot(const struct ACCEL &);
    void Clear();
protected:
    void resizeEvent(QResizeEvent *);
};

#endif // XY_AREA_H
