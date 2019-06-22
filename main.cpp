#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
static float version = 1.0;


int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("bin/plugins");
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("95.143.216.174");
    db.setPort(3306);
    db.setDatabaseName("server");
    db.setUserName("server");
    db.setPassword("server");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    if(!db.open()) {
        QMessageBox::warning(0,"Ошибка!","Не удалось подключиться к серверу.\nКод ошибки: 0001");
    }
    else {
        QSqlQuery query;
        query.exec("SELECT * FROM version WHERE active='1' ORDER BY id DESC ");
        QSqlRecord rec = query.record();
        query.next();
        float version_  = query.value(rec.indexOf("version")).toFloat();
        if (version != version_) {
            QMessageBox msgBox;
             msgBox.setText("Вышла новая версия программы.\nЖелаете обновиться?");
             msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
             msgBox.setDefaultButton(QMessageBox::Yes);
             int ret = msgBox.exec();
             switch (ret) {
                case QMessageBox::Yes:
                    //скачиваем
                    QMessageBox::information(0,"OK","OK");
                    break;
                case QMessageBox::No:
                    break;
             }
        }
    }

    return a.exec();
}
