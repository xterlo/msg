#ifndef REGRegactivation_H
#define REGACTIVATION_H

#include <QWidget>
#include <QKeyEvent>
#include "glavnaya.h"
namespace Ui {
class Regactivation;
}

class Regactivation : public QWidget
{
    Q_OBJECT
signals:
    void firstWindow();
public:
    explicit Regactivation(QWidget *parent = nullptr);
    ~Regactivation();
private:
    Ui::Regactivation *ui;
    Glavnaya *glavnaya;

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
public slots:
    void recieveData(QString Qnick);

private slots:
    void on_exitbutton_clicked();
};

#endif // REGACTIVATION_H
