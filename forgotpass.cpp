#include "forgotpass.h"
#include "ui_forgotpass.h"

ForgotPass::ForgotPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPass)
{
    ui->setupUi(this);
}
ForgotPass::~ForgotPass()
{
    delete ui;
}
void ForgotPass::on_pushButton_clicked()
{
    close();
    emit firstWindow();
//gtre9ou8pih
}
