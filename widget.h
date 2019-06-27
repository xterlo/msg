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
    ~Widget();
private:
    Ui::Widget *ui;
    Downloader *downloader;
};

#endif // WIDGET_H
