#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <QWidget>

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
};

#endif // ACTIVATION_H
