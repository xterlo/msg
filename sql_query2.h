#ifndef SQL_QUERY2_H
#define SQL_QUERY2_H

#include <QObject>

class sql_query2 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    bool m_running;
    QString id;
    QString id_msg;
public:
    explicit sql_query2(QObject *parent = nullptr);
    bool running() const;
signals:
    void runningChanged(bool running);
    void update();
public slots:
    void checker();
    void setRunning(bool running);
    void receiveid(QString idd);
    void receiveidd(QString idd);
    void reload();
};

#endif // SQL_QUERY2_H
