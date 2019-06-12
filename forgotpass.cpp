#include "forgotpass.h"
#include "ui_forgotpass.h"

ForgotPass::ForgotPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPass)
{
    ui->setupUi(this);
}
//asdasd
ForgotPass::~ForgotPass()
{
    delete ui;
}

void ForgotPass::on_pushButton_clicked()
{
    close();
    emit firstWindow();
}
//pervaya(new)
//dasdsa
