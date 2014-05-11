#include "qhidmanager.h"

QHIDManager& QHIDManager::get() {
    static QHIDManager instance;
    return instance;
}

QHIDManager::QHIDManager()
{
    hid_init();
}

QHIDManager::~QHIDManager() {
    hid_exit(); //TODO: What if this fails?
}

QVector<QHIDInfo> QHIDManager::enumerate(quint16 vendor_id, quint16 product_id) {
    QVector<QHIDInfo> result;
    hid_device_info *info = hid_enumerate(vendor_id, product_id);
    while (info != nullptr) {
        result.append(
        {info->path,
         QString::fromWCharArray(info->serial_number),
         QString::fromWCharArray(info->manufacturer_string),
         QString::fromWCharArray(info->product_string),
         info->vendor_id, info->product_id, info->release_number,
         info->usage_page, info->usage, info->interface_number
        });
        info = info->next;
    }
    hid_free_enumeration(info);
    return result;
}
