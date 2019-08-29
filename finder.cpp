#include "finder.h"
#include "ui_finder.h"
#include <QDebug>
static QString adduser;
finder::finder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::finder)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint );
}

finder::~finder()
{
    delete ui;
}

void finder::on_lineEdit_textChanged(const QString &arg1)
{
    adduser = ui->lineEdit->text();
    emit newdialog(adduser);
}
void finder::mousePressEvent(QMouseEvent *event) {
    QDesktopWidget * screen = QApplication::desktop();
    screen->availableGeometry();
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();

    if(event->button() == Qt::LeftButton && m_nMouseClick_Y_Coordinate<20)
        {
           {

                 checkmouse = true;
           }

        }
    else checkmouse = false;

}
void finder::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        checkmouse = false;
    }
    return QWidget::mouseReleaseEvent(event);
}
void finder::mouseMoveEvent(QMouseEvent *event)
{
    if (checkmouse == true){
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);}

}

void finder::on_exitbutton_clicked()
{

    close();
}
