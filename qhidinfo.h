#ifndef QHIDINFO_H
#define QHIDINFO_H

#include <QtGlobal>
#include <QString>

struct QHIDInfo {
    QString path;
    QString serial_number;
    QString manufacturer_string;
    QString product_string;
    quint16 vendor_id;
    quint16 product_id;
    quint16 release_number;
    quint16 usage_page;
    quint16 usage;
    qint32  interface_number;
};

#endif // QHIDINFO_H
