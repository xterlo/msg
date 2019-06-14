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
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
private:
    Ui::MainWindow *ui;
    Registration *reg;
    Glavnaya *glava;
    ForgotPass *forgot;
    Activation *activation;



};

#endif // MAINWINDOW_H
