#ifndef GLAVNAYA_H
#define GLAVNAYA_H

#include "ui_glavnaya.h"
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <string>

namespace Ui {
class Glavnaya;
}

class Glavnaya : public QWidget
{
    Q_OBJECT


public:
    explicit Glavnaya(QWidget *parent = nullptr);
    ~Glavnaya();


signals:
    void firstWindow();


private slots:
    void on_pushButton_clicked();
    void on_exitbutton_clicked();
    void on_fullscreen_clicked();

private:

    Ui::Glavnaya *ui;
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    bool checkmouse;
    bool checkfull;

    int sizew=Glavnaya::size().width();
    int sizey=Glavnaya::size().height();
    int posx=Glavnaya::pos().x();
    int posy=Glavnaya::pos().y();


};

#endif // GLAVNAYA_H

