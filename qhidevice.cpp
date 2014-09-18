#include "qhidevice.h"
#include <cassert>
#include <QDebug>

QHIDevice::QHIDevice(hid_device *dev, QObject *parent) : QObject(parent), _device(dev) {
	if (_device == nullptr) return;
    hid_set_nonblocking(_device,true);
    poll.setInterval(100);
    _timeout.setSingleShot(true);
    connect(&_timeout,&QTimer::timeout,[this] () { poll.stop(); emit timeout(); });
    connect(&poll,&QTimer::timeout, [this] () {
        unsigned char* buf = new unsigned char[expectData];
        int res = hid_read(_device,buf,expectData);
        if (res == -1) {
			qDebug() << "ERR!";
            //TODO What to do on error?
        }
        recvBuf.append(reinterpret_cast<char*>(buf),res);
        expectData -= res;
        if (expectData == 0) {
			poll.stop();
			_timeout.stop();
			emit receivedData(recvBuf);
        }
        delete[] buf;
    });
}

QHIDevice::QHIDevice(QString path, QObject *parent) :
    QHIDevice::QHIDevice(hid_open_path(path.toStdString().c_str()),parent)
{}

QHIDevice::QHIDevice(quint16 vendor_id, quint16 product_id, QObject *parent) :
    QHIDevice(hid_open(vendor_id,product_id,nullptr),parent)
{}

QHIDevice::QHIDevice(quint16 vendor_id, quint16 product_id, const QString &serial_number, QObject *parent) :
    QHIDevice(hid_open(vendor_id,product_id, serial_number.toStdWString().c_str()),parent)
{}

bool QHIDevice::good() {
    return _device != nullptr;
}


int QHIDevice::write(const QByteArray &data) {
	if (_device == nullptr) return -1;
    return hid_write(_device,reinterpret_cast<const unsigned char*>(data.constData()),data.size());
}

int QHIDevice::sendReport(const QByteArray &data) {
    if (_device != nullptr) return -1;
    return hid_send_feature_report(_device,reinterpret_cast<const unsigned char*>(data.constData()),data.size());
}

void QHIDevice::getReport(size_t length, int timeout_ms) {
	if (_device == nullptr) return;
	_timeout.start(timeout_ms);
    expectData = length;
    recvBuf.clear();
    poll.start();
}

void QHIDevice::read(size_t length, int timeout_ms) {
	if (_device == nullptr) return;
	_timeout.start(timeout_ms);
    expectData = length;
    recvBuf.clear();
    poll.start();
}
