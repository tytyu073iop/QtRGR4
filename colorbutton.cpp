#include "colorbutton.h"
#include <QColorDialog>

ColorButton::ColorButton(const QColor& color, size_t i) : layerButton(i), color(color) {
    QPixmap pm(20,20);
    pm.fill(color);
    this->setIcon(QIcon(pm));
    connect(this, SIGNAL(SPClicked(size_t)), SLOT(CallDialog(size_t)));
}

void ColorButton::CallDialog(size_t s)
{
    auto newColor = QColorDialog::getColor(color);
    QPixmap pm(20,20);
    pm.fill(newColor);
    this->setIcon(QIcon(pm));
    emit GotColor(newColor, s);
}
