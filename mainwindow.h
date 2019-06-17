#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "glavnaya.h"
#include "registration.h"
#include "forgotpass.h"
#include <QMouseEvent>
#include "regactivation.h"
#include <qdesktopwidget.h>

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

signals:
    void sendData(QString Qnick);
private slots:
    void on_authorization_clicked();
    void on_reg_clicked();
    void on_forgot_clicked();
    void on_exitbutton_clicked();   
private:
    Ui::MainWindow *ui;
    Registration *reg;
    Glavnaya *glava;
    ForgotPass *forgot;
    Regactivation *regactivation;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
