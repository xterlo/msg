#ifndef FORGOTPASS_H
#define FORGOTPASS_H
#include <QWidget>
#include <QMouseEvent>
#include "smtp.h"
#include "activation.h"
#include "forgotpassrepeat.h"



namespace Ui {
class ForgotPass;
}

class ForgotPass : public QWidget
{
    Q_OBJECT


public:
    explicit ForgotPass(QWidget *parent = nullptr);
    ~ForgotPass();

private slots:
    void on_pushButton_clicked();


    void on_exitbutton_clicked();

    void on_backbutton_clicked();

    void on_Mini_clicked();

signals:
    void sendData(QString Qmail);
    void firstWindow();


private:
    Ui::ForgotPass *ui;
    forgotpassrepeat *fpr;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    Activation *activation;
    bool checkmouse;

protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // FORGOTPASS_H


