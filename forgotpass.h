#ifndef FORGOTPASS_H
#define FORGOTPASS_H
#include <QWidget>


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

signals:
    void firstWindow();

private:
    Ui::ForgotPass *ui;
};

#endif // FORGOTPASS_H


