#include "show_parse.h"
#include <QGridLayout>

Show_parse::Show_parse(QWidget *parent) :
    QWidget(parent)
{
    qle_1 = new QLineEdit("0");
    qle_1->setReadOnly(true);
    qle_2 = new QLineEdit("0");
    qle_2->setReadOnly(true);
    qle_3 = new QLineEdit("0");
    qle_3->setReadOnly(true);
    qle_4 = new QLineEdit("0");
    qle_4->setReadOnly(true);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(qle_1, 0, 0, 1, 1);
    mainLayout->addWidget(qle_2, 1, 0, 1, 1);
    mainLayout->addWidget(qle_3, 0, 2, 1, 1);
    mainLayout->addWidget(qle_4, 1, 2, 1, 1);

    setLayout(mainLayout);
}

void Show_parse::Parse_POHPR_Slot(const struct POHPR &pohpr)
{
    qle_1->setText(QString::number(pohpr.time));
    qle_2->setText(QString::number(pohpr.course));
    qle_3->setText(QString::number(pohpr.roll));
    qle_4->setText(QString::number(pohpr.pitch));
}
