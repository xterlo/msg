
#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>
#include <QWidget>
#include "smtp.h"


namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

signals:
    void firstWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::Registration *ui;


};

#endif // REGISTRATION_H
