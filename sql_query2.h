#ifndef SQL_QUERY2_H
#define SQL_QUERY2_H

#include <QObject>

class sql_query2 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(QString id_dia READ id_dia WRITE set_id_dia)
    Q_PROPERTY(QString id_msg READ id_msg WRITE set_id_msg)

    bool m_running;
    QString m_id_dia;
    QString m_id_msg;
public:
    explicit sql_query2(QObject *parent = nullptr);
    bool running() const;
    QString id_dia() const;
    QString id_msg() const;
signals:
    void runningChanged(bool running);
    void update();
public slots:
    void checker();
    void setRunning(bool running);
    void reload();
    void set_id_dia(QString id_dia);
    void set_id_msg(QString id_msg);
};

#endif // SQL_QUERY2_H
