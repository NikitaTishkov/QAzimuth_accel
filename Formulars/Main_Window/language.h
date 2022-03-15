#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QWidget>
#include <QActionGroup>
#include <QAction>

class Language : public QActionGroup
{
    Q_OBJECT
public:
    explicit Language(QWidget *parent = 0);

signals:
    void Set_Language(QString);
public slots:

private:
    QAction *English;
    QAction *Ukrainian;
private slots:
    void Action(QAction*);
};

#endif // LANGUAGE_H
