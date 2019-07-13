#ifndef FORGOTPASSREPEAT_H
#define FORGOTPASSREPEAT_H

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
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
    void on_exitbutton_clicked();


private:
    Ui::forgotpassrepeat *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    bool checkmouse;
protected:

    void keyPressEvent(QKeyEvent *event);

public slots:
    void emailData(QString Qmail);
};

#endif // FORGOTPASSREPEAT_H
