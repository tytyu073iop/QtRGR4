#ifndef MYLAYER_H
#define MYLAYER_H
#include <QPixmap>

struct MyLayer {
    QPixmap* layer;
    bool operator==(const MyLayer& other) const {
        return layer == other.layer;
    }
};

#endif // MYLAYER_H
