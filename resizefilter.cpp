#include "resizefilter.h"
#include <QResizeEvent>

ResizeFilter::ResizeFilter(QObject *parent, QObject *watched)
    : QObject{parent}, watched(watched)
{

}

bool ResizeFilter::eventFilter(QObject *watched, QEvent *event)
{
    qDebug() << "block!" << event->type();
    if (this->watched == watched && event->type() == QEvent::Resize) {
        return true;
    }
    return false;
}
