#include "movew.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(50, 50);
    setStyleSheet("QWidget { background: red; }");
}

void CustomWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void CustomWidget::mousePressEvent(QMouseEvent *event)
{
    startPos = event->pos();
    QWidget::mousePressEvent(event);
}

void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint delta = event->pos() - startPos;
    QWidget * w = window();
    if(w)
        w->move(w->pos() + delta);
    QWidget::mouseMoveEvent(event);
}
