#ifndef FORGOTPASS_H
#define FORGOTPASS_H
//sdsadsadsadsadsa
#include <QWidget>
//dsadsadsadada
//asdsadsadadsad
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
//dsadasd
signals:
    void firstWindow();

private:
    Ui::ForgotPass *ui;
};
//sdfksdfdsfdsf
#endif // FORGOTPASS_H
//dsfdsfdsfsdf

