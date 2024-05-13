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
    paint.eraseRect(0,0, parent->imageSize.width(), parent->imageSize.height());
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
    //layers.push_back({QPointF(0,0), parent->image});

}

void PaintField::mousePressEvent(QMouseEvent *event) {
    activeLayer = new QPixmap(parent->imageSize);
    activeLayer->fill(Qt::transparent);
    painter = new QPainter(activeLayer);
    QPen pen(parent->color);
    pen.setWidth(parent->size);
    painter->setPen(pen);
    bPoint = event->localPos();
    layers.push_back({QPointF(0, 0), activeLayer});
}

void PaintField::resizeEvent(QResizeEvent *event)
{
    qDebug() << "label resize";
    // auto xnum = event->oldSize().width() / event->size().width();
    // auto ynum = event->oldSize().height() / event->size().height();
    // QTransform transform(xnum, 0, 0, ynum, 0, 0);
    // for (auto i : layers) {
    //     auto backup = *i.second;
    //     i.second->fill(Qt::transparent);
    //     QPainter painter(i.second);
    //     painter.setTransform(transform);

    // }
    if (event->oldSize() == QSize(-1, -1)) { return; }
    QSize scale(event->size() - event->oldSize());
    parent->imageSize += scale;
    *parent->image = parent->image->scaled(parent->imageSize);
    for (auto i : layers) {
        *i.second = i.second->scaled(parent->imageSize);
    }
    rerender();
}

void PaintField::mouseMoveEvent(QMouseEvent* event) {
    //if (painter == nullptr) { return; }

    auto text = parent->actionGroup->checkedAction()->iconText();

    if (text == "curved line") {

        return;
    }
    activeLayer->fill(Qt::transparent);
    remove(QPointF(0, 0), activeLayer);
    //activeLayer->clear();
    if (text == "straight line") {
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
