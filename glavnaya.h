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
#include <QThread>
#include "sql_query1.h"
#include "sql_query2.h"
#include "finder.h"

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
    void sendnick(QString nick);
    void sendid(QString id);
    void sendmsg(QString msg);
    void sendid_1(QString idd);
    void sendid_2(QString idd);


private slots:
    void on_exitbutton_clicked();
    void on_fullscreen_clicked();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_Mini_clicked();

    void on_dialogs_itemClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_openfinder_clicked();

private:

    Ui::Glavnaya *ui;
    finder *find;
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    bool checkmouse;
    bool checkfull = false;

    int sizew=Glavnaya::size().width();
    int sizey=Glavnaya::size().height();
    int posx=Glavnaya::pos().x();
    int posy=Glavnaya::pos().y();
    QSystemTrayIcon *trayIconG;
    QThread thread_1;
    QThread thread_2;
    sql_query1 sql_1;
    sql_query2 sql_2;
public slots:
    void recieveData(QString Qnick);
    void updater();
    void add();
    void adddialog(QString user);

};

#endif // GLAVNAYA_H

