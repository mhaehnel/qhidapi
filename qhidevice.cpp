#include "qhidevice.h"
#include <cassert>

QHIDevice::QHIDevice(QString path, QObject *parent) :
    QObject(parent)
{
    _device = hid_open_path(path.toStdString().c_str());
    hid_set_nonblocking(_device,true);
}

QHIDevice::QHIDevice(quint16 vendor_id, quint16 product_id) {
    _device = hid_open(vendor_id,product_id,nullptr);
    hid_set_nonblocking(_device,true);
}

QHIDevice::QHIDevice(quint16 vendor_id, quint16 product_id, const QString &serial_number) {
    _device = hid_open(vendor_id,product_id, serial_number.toStdWString().c_str());
    hid_set_nonblocking(_device,true);
}

bool QHIDevice::good() {
    return _device != nullptr;
}


int QHIDevice::write(const QByteArray &data) {
    if (_device != nullptr) return -1;
    return hid_write(_device,reinterpret_cast<const unsigned char*>(data.constData()),data.size());
}

int QHIDevice::sendReport(const QByteArray &data) {
    if (_device != nullptr) return -1;
    return hid_send_feature_report(_device,reinterpret_cast<const unsigned char*>(data.constData()),data.size());
}

void QHIDevice::getReport(size_t length, int timeout_ms) {

}

void QHIDevice::read(size_t length, int timeout_ms) {

}
