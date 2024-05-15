#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QColor>
#include "layerbutton.h"

class ColorButton : public layerButton
{
    Q_OBJECT
    QColor color;
public:
    ColorButton(const QColor&, size_t);
public slots:
    void CallDialog(size_t);
signals:
    void GotColor(QColor color, size_t);
};

#endif // COLORBUTTON_H
