#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <QWidget>
#include <QKeyEvent>
#include "forgotpassrepeat.h"
namespace Ui {
class Activation;
}

class Activation : public QWidget
{
    Q_OBJECT
signals:
    void firstWindow();
public:
    explicit Activation(QWidget *parent = nullptr);
    ~Activation();
private:
    Ui::Activation *ui;
    forgotpassrepeat *fpr;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
protected:
    void keyPressEvent(QKeyEvent *event);
public slots:
    void emailData(QString Qmail);

private slots:
    void on_exitbutton_clicked();
};

#endif // ACTIVATION_H
