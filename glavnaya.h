#ifndef GLAVNAYA_H
#define GLAVNAYA_H

#include <QWidget>

namespace Ui {
class Glavnaya;
}

class Glavnaya : public QWidget
{
    Q_OBJECT

public:
    explicit Glavnaya(QWidget *parent = nullptr);
    ~Glavnaya();
signals:
    void firstWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Glavnaya *ui;
};

#endif // GLAVNAYA_H
//asdasdadadasd
