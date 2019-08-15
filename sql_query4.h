#ifndef SQL_QUERY4_H
#define SQL_QUERY4_H

#include <QObject>

class sql_query4 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    bool m_running;
    QString id;
    QString nickname;

public:
    explicit sql_query4(QObject *parent = nullptr);
    bool running() const;
signals:
    void runningChanged(bool running);
    void update();
public slots:
    void checker();
    void setRunning(bool running);
    void reload();
    void recieveid(QString idd);
    void recievenick(QString nick);
};

#endif // SQL_QUERY4_H
