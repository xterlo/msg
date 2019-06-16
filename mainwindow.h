#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "glavnaya.h"
#include "registration.h"
#include "forgotpass.h"
#include <QMouseEvent>
#include "activation.h"
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
    Activation *activation;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;


};

#endif // MAINWINDOW_H
