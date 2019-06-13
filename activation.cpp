#include "activation.h"
#include "ui_activation.h"

Activation::Activation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Activation)
{
    ui->setupUi(this);
}

Activation::~Activation()
{
    delete ui;
}
