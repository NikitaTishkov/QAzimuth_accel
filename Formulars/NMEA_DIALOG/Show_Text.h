#ifndef SHOW_TEXT_H
#define SHOW_TEXT_H

#include <QPlainTextEdit>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QString>

#include "higlighter.h"

class LineNumberArea;

class Show_Text_QW : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit Show_Text_QW(QPlainTextEdit *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
signals:

public slots:
    void Find_Slot(double);
    void Show_Hide(bool click);
protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void highlightCurrentLine();
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);
private:
    QWidget *lineNumberArea;

    Higlighter *higlighter;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(Show_Text_QW *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    Show_Text_QW *codeEditor;
};

#endif // SHOW_TEXT_H
