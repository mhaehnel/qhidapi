#ifndef QHIDEVICE_H
#define QHIDEVICE_H

#include <QObject>
#include <QTimer>
#include <hidapi/hidapi.h>
#include <qhidapi_global.h>

class QHIDAPISHARED_EXPORT QHIDevice : public QObject
{
    Q_OBJECT
    hid_device* _device;
    QByteArray recvBuf;
    QByteArray reportBuf;
    size_t expectData, expectReport;
    QTimer tmr;
public:
    explicit QHIDevice(QString path, QObject *parent = 0);
    QHIDevice(quint16 vendor_id, quint16 product_id);
    QHIDevice(quint16 vendor_id, quint16 product_id, const QString& serial_number);
    bool good();
    QString manufacturer();
    QString product();
    QString serial();
    QString indexedString(int index);

signals:
    void receivedData(QByteArray data);
    void receivedReport(QByteArray data);
    void timeout();
    void error(QString error);

public slots:
    void read(size_t length, int timeout_ms = 0); //Send signal once length bytes received
    void getReport(size_t length, int timeout_ms = 0); //Send signal once length bytes received
    int write(const QByteArray& data);
    int sendReport(const QByteArray& data);
};

#endif // QHIDEVICE_H
