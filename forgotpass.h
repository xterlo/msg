#ifndef FORGOTPASS_H
#define FORGOTPASS_H
#include <QWidget>
#include <QMouseEvent>
#include "smtp.h"



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

signals:
    void firstWindow();


private:
    Ui::ForgotPass *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;


};

#endif // FORGOTPASS_H


