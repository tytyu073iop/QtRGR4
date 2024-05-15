#ifndef MYLAYER_H
#define MYLAYER_H
#include <QPixmap>
#include <QPoint>

struct MyLayer {
    QPixmap* layer;
    QPoint point;
    bool operator==(const MyLayer& other) const {
        return layer == other.layer;
    }
};

#endif // MYLAYER_H
