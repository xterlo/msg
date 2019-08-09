#ifndef GLAVNAYA_H
#define GLAVNAYA_H

#include "ui_glavnaya.h"
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <string>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QAction>
#include <QMenu>
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
    void on_exitbutton_clicked();
    void on_fullscreen_clicked();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_Mini_clicked();
    void on_dialogs_itemClicked(QListWidgetItem *item);
    void asd();
    void on_pushButton_2_clicked();

private:

    Ui::Glavnaya *ui;
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    bool checkmouse;
    bool checkfull = false;
    int MySelectedItem;
    int sizew=Glavnaya::size().width();
    int sizey=Glavnaya::size().height();
    int posx=Glavnaya::pos().x();
    int posy=Glavnaya::pos().y();
    QSystemTrayIcon *trayIconG;
public slots:
    void recieveData(QString Qnick);

};

#endif // GLAVNAYA_H

