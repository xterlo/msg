#ifndef SQL_QUERY3_H
#define SQL_QUERY3_H

#include <QObject>

class sql_query3 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(QString nickname READ nickname WRITE set_nickname)
    bool m_running;  
    QString m_nickname;

public:
    explicit sql_query3(QObject *parent = nullptr);
    bool running() const;
    QString nickname() const;
signals:
    void runningChanged(bool running);
public slots:
    void checker();
    void setRunning(bool running);
    void set_nickname(QString nickname);
};

#endif // SQL_QUERY3_H
