#include <QCoreApplication>
#include "downloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Downloader *downloader;
    downloader = new Downloader;
    downloader->getData();

    return a.exec();
}
