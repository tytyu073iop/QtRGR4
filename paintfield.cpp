#include "paintfield.h"
#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QRectF>
#include <algorithm>
#include <QFileDialog>

void PaintField::rerender()
{
    QPainter paint(parent->image);
    paint.eraseRect(0,0,500,500);
    for (auto i : layers) {
        paint.drawPixmap(i.first, *i.second);
    }
    this->setPixmap(*(parent->image));
}

void PaintField::add(QPointF point, QPixmap* pm)
{
    QPainter paint(parent->image);
    paint.drawPixmap(point, *pm);
    layers.push_back({point, pm});
    this->setPixmap(*(parent->image));
}

void PaintField::remove(QPointF point, QPixmap* pm)
{
    //delete pm;
    layers.removeAll({point, pm});
    rerender();
    //del on us
}

PaintField::PaintField(MainWindow* parent) : parent(parent) {

}

void PaintField::mousePressEvent(QMouseEvent *event) {
    activeLayer = new QPixmap(500, 500);
    activeLayer->fill(Qt::transparent);
    painter = new QPainter(activeLayer);
    QPen pen(parent->color);
    pen.setWidth(parent->size);
    painter->setPen(pen);
    bPoint = event->localPos();
    layers.push_back({QPointF(0, 0), activeLayer});
}

void PaintField::mouseMoveEvent(QMouseEvent* event) {
    //if (painter == nullptr) { return; }

    auto text = parent->actionGroup->checkedAction()->iconText();

    if (text == "Draw curved line") {

        return;
    }
    activeLayer->fill(Qt::transparent);
    remove(QPointF(0, 0), activeLayer);
    //painter->eraseRect(0,0,500,500);
    //activeLayer->clear();
    if (text == "Draw straight line") {
        painter->drawLine(bPoint, event->localPos());
        add(QPointF(0, 0), activeLayer);
    }
}

void PaintField::mouseReleaseEvent(QMouseEvent *event) {
    //painter->drawLine(bPoint, event->localPos());
    painter->end();
    delete painter;
    rerender();
}
