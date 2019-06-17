#ifndef FORGOTPASSREPEAT_H
#define FORGOTPASSREPEAT_H

#include <QWidget>

namespace Ui {
class forgotpassrepeat;
}

class forgotpassrepeat : public QWidget
{
    Q_OBJECT

public:
    explicit forgotpassrepeat(QWidget *parent = nullptr);
    ~forgotpassrepeat();

private slots:
    void on_pushButton_clicked();

private:
    Ui::forgotpassrepeat *ui;
public slots:
    void emailData(QString Qmail);
};

#endif // FORGOTPASSREPEAT_H
