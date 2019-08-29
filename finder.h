#ifndef FINDER_H
#define FINDER_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDesktopWidget>
namespace Ui {
class finder;
}

class finder : public QWidget
{
    Q_OBJECT

public:
    explicit finder(QWidget *parent = nullptr);
    ~finder();
signals:
    void newdialog(QString user);
private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_exitbutton_clicked();
private:
    Ui::finder *ui;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    bool checkmouse;

};

#endif // FINDER_H
