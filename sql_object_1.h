#ifndef SQL_OBJECT_1_H
#define SQL_OBJECT_1_H

#include <QObject>

class sql_object_1 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    bool m_running;
    int count;
public:
    explicit sql_object_1(QObject *parent = nullptr);
    bool running() const;
signals:
    void runningChanged(bool running);

public slots:
   void update();
   void restart();
   void setRunning(bool running);
   void recieveData(QString Qid_dia);
   void recievenick(QString Qnick);
};

#endif // SQL_OBJECT_1_H
