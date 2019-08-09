#ifndef SQL_QUERY1_H
#define SQL_QUERY1_H

#include <QObject>

class sql_query1 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    bool m_running;
    QString nickname;
    QString id;
public:
    explicit sql_query1(QObject *parent = nullptr);
    bool running() const;
signals:
    void runningChanged(bool running);
    void update();
public slots:
    void recievenick(QString nick);
    void recieveid(QString id_d);
    void recievemsg(QString msg);
    void checker();
    void setRunning(bool running);
    void reload();
};

#endif // SQL_QUERY1_H
