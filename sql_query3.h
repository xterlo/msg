#ifndef SQL_QUERY3_H
#define SQL_QUERY3_H

#include <QObject>

class sql_query3 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    bool m_running;
    QString nickname;

public:
    explicit sql_query3(QObject *parent = nullptr);
    bool running() const;
signals:
    void runningChanged(bool running);
public slots:
    void checker();
    void recievenick(QString nick);
    void setRunning(bool running);
};

#endif // SQL_QUERY3_H
