
#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>



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
    void on_backbutton_clicked();
    void on_exitbutton_clicked();

private:
    Ui::Registration *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

};

#endif // REGISTRATION_H
