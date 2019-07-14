#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>

#include <downloader.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    void end();
    ~Widget();
private slots:
    void on_pushButton_2_clicked();
    void pr_bar();

private:
    Downloader *downloader;
    Ui::Widget *ui;
};

#endif // WIDGET_H
