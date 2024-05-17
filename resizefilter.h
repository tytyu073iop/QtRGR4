#ifndef RESIZEFILTER_H
#define RESIZEFILTER_H

#include <QObject>

class ResizeFilter : public QObject
{
    Q_OBJECT
    QObject* watched;

public:
    explicit ResizeFilter(QObject *watched, QObject *parent = nullptr);
    virtual bool eventFilter(QObject *watched, QEvent *event);

signals:
};

#endif // RESIZEFILTER_H
