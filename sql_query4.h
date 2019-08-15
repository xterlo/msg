#ifndef SQL_QUERY4_H
#define SQL_QUERY4_H

#include <QObject>

class sql_query4 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    bool m_running;
    QString status;
    QString id;
public:
    explicit sql_query4(QObject *parent = nullptr);
    bool running() const;
signals:
    void runningChanged(bool running);
    void update();
public slots:
    void recivestatus(QString stat);
    void checker();
    void setRunning(bool running);
    void receiveid(QString idd);
    void reload();
};

#endif // SQL_QUERY4_H
