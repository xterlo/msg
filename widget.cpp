#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    downloader = new Downloader(); // Инициализируем Downloader

    // по нажатию кнопки запускаем получение данных по http
    connect(ui->pushButton, &QPushButton::clicked, downloader, &Downloader::getData);

}

Widget::~Widget()
{
    delete ui;
}
