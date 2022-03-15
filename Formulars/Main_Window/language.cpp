#include "language.h"
#include <QVBoxLayout>

Language::Language(QWidget *parent) :  QActionGroup(parent)
{
    English   = new QAction("English", this);
        English->setCheckable(true);
        English->setChecked(true);
    Ukrainian = new QAction("Ukrainian", this);
        Ukrainian->setCheckable(true);

    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(Action(QAction*)));
}

void Language::Action(QAction* a)
{
    if(a == English)
    {
        emit Set_Language("English");
    }
    else if(a == Ukrainian)
    {
        emit Set_Language("Ukrainian");
    }
}
