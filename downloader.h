#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);

signals:
    void onReady();

public slots:
    void getData();
    void onResult(QNetworkReply *reply);
    void HideConsole();

private:
    QNetworkAccessManager *manager;
};

#endif // DOWNLOADER_H
