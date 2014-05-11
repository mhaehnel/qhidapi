#ifndef QHIDMANAGER_H
#define QHIDMANAGER_H

#include <QVector>
#include <qhidinfo.h>
#include "qhidapi_global.h"
#include <hidapi/hidapi.h>

class QHIDAPISHARED_EXPORT QHIDManager
{
public:
    static QHIDManager& get();
    QVector<QHIDInfo> enumerate(quint16 vendor_id = 0, quint16 product_id = 0);
private:
    QHIDManager();
    virtual ~QHIDManager();
};

#endif // QHIDMANAGER_H
