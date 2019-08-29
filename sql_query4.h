#ifndef SQL_QUERY4_H
#define SQL_QUERY4_H

#include <QObject>

class sql_query4 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    bool m_running;
    Q_PROPERTY(QString id_dia READ id_dia WRITE set_id_dia)
    Q_PROPERTY(QString status READ status WRITE set_status)
    QString m_status;
    QString m_id_dia;

public:
    explicit sql_query4(QObject *parent = nullptr);
    bool running() const;
    QString status() const;
    QString id_dia() const;
signals:
    void runningChanged(bool running);
    void update();
public slots:
    void checker();
    void setRunning(bool running);
    void reload();
    void set_status(QString status);
    void set_id_dia(QString id_dia);
};

#endif // SQL_QUERY4_H
