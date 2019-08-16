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
    sizew=finder::size().width();
    sizey=finder::size().height();
    posx=finder::pos().x();
    posy=finder::pos().y();
}

finder::~finder()
{
    delete ui;
}

void finder::mousePressEvent(QMouseEvent *event) {
    QDesktopWidget * screen = QApplication::desktop();
    screen->availableGeometry();
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
    if(event->button() == Qt::LeftButton && m_nMouseClick_Y_Coordinate<20)
        {
           {
           if(checkfull == false)
               {
                 checkmouse = true;
               }

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
void finder::on_fullscreen_clicked()
{
    QDesktopWidget * screen = QApplication::desktop();
    checkmouse = false;
    screen->availableGeometry();
    if(m_nMouseClick_Y_Coordinate<20)
        {
        if (finder::size().width()==screen->availableGeometry().width() && finder::size().height()==screen->availableGeometry().height() )
        {
            finder::setGeometry(posx,posy,sizew,sizey);
            checkfull=false;
        }
        else
        {
            sizew=finder::size().width();
            sizey=finder::size().height();
            posx=finder::pos().x();
            posy=finder::pos().y();
            finder::setGeometry(0,0,screen->availableGeometry().width(),screen->availableGeometry().height());
            checkfull=true;
        }
        }
}
void finder::on_exitbutton_clicked()
{
    this->close();
}
void finder::on_Mini_clicked()
{
    finder::showMinimized();
}
void finder::mouseDoubleClickEvent(QMouseEvent *event)
{
    finder::on_fullscreen_clicked();
}

void finder::on_pushButton_clicked()
{
    adduser = ui->lineEdit->text();
    emit newdialog(adduser);
    this->close();
}
