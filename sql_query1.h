#ifndef SQL_QUERY1_H
#define SQL_QUERY1_H

#include <QObject>

class sql_query1 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(QString id_dia READ id_dia WRITE set_id_dia)
    Q_PROPERTY(QString nickname READ nickname WRITE set_nickname)
    Q_PROPERTY(QStringList msg_array READ msg_array WRITE set_msg_array)
    bool m_running;
    QString m_id_dia;
    QString m_nickname;
    QStringList m_msg_array;

public:
    explicit sql_query1(QObject *parent = nullptr);
    bool running() const;
    QString id_dia() const;
    QString nickname() const;
    QStringList msg_array() const;
signals:
    void runningChanged(bool running);
    void update();
public slots:
    void checker();
    void setRunning(bool running);
    void reload();
    void set_id_dia(QString id_dia);
    void set_nickname(QString nickname);
    void set_msg_array(QStringList msg_array);
};

#endif // SQL_QUERY1_H
