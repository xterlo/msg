#ifndef CRYPTER_H
#define CRYPTER_H

#include <QObject>
#include <QDebug>

static QString kEncryptorString;
class Crypter : public QObject
{
    Q_OBJECT
public:
    static void setSecretkey(QString secKey) {
       kEncryptorString = secKey;
    }
    static QString cryptString(QString toCrypt)
    {
        QString resultString = "";
        for ( int i = 0; i < toCrypt.length(); i++)
        {
            resultString.append(QString(QChar(toCrypt[i]).unicode()^QChar(kEncryptorString[keyIndex(i)]).unicode()));
        }
        QByteArray b;
        b = resultString.toUtf8();
        QByteArray b64 = b.toBase64();
        resultString = b64;
        return resultString;
    }
    static QString decryptString(QString toDecrypt)
    {
        QString resultString;
        QByteArray b;
        b = toDecrypt.toUtf8();
        toDecrypt = QByteArray::fromBase64(b);
        for ( int i = 0; i < toDecrypt.length(); i++)
        {
            resultString.append(QString(QChar(toDecrypt[i]).unicode()^QChar(kEncryptorString[keyIndex(i)]).unicode()));
        }
        return resultString;
    }
private:
    Crypter(QObject *parent = 0);
    static int keyIndex(int index)
    { 
        int len = kEncryptorString.length();
        int multiple = index / len;
        if ( index >=  len ) {
            return index - (len * multiple);
        }
        return index;
    }
};

#endif // CRYPTER_H
