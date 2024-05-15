#include "paintfield.h"
#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QRectF>
#include <algorithm>
#include <QFileDialog>
#include <QDebug>
#include "resizedialog.h"

void PaintField::rerender()
{
    qDebug() << "rerendering";
    QPainter paint(parent->image);
    paint.eraseRect(0,0, parent->imageSize.width(), parent->imageSize.height());
    for (auto i : layers) {
        paint.drawPixmap(i.point.x(), i.point.y(), *i.layer, 0, 0, parent->imageSize.width(), parent->imageSize.height());
    }
    this->setPixmap(*(parent->image));
}

void PaintField::add(QPointF point, QPixmap* pm)
{
    QPainter paint(parent->image);
    paint.drawPixmap(point, *pm);
    layers.push_back({pm});
    this->setPixmap(*(parent->image));
}

void PaintField::remove(QPointF point, QPixmap* pm)
{
    //delete pm;
    layers.removeAll({pm});
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
    layers.push_back({activeLayer});
}

void PaintField::resizeEvent(QResizeEvent *event)
{
    qDebug() << "label resize" << event->size();
    // auto xnum = event->oldSize().width() / event->size().width();
    // auto ynum = event->oldSize().height() / event->size().height();
    // QTransform transform(xnum, 0, 0, ynum, 0, 0);
    // for (auto i : layers) {
    //     auto backup = *i.second;
    //     i.second->fill(Qt::transparent);
    //     QPainter painter(i.second);
    //     painter.setTransform(transform);

    // }
    if (event->oldSize().height() <= 0 || event->oldSize().width() <= 0) { return; }
    QSize scale(event->size() - event->oldSize());
    parent->imageSize += scale;
    *parent->image = parent->image->scaled(parent->imageSize);
    for (auto i : layers) {
        *i.layer = i.layer->scaled(parent->imageSize);
    }
    rerender();
}

void PaintField::del(size_t i)
{
    layers.removeAt(i);
    rerender();
    parent->updateLayers();
}

void PaintField::resize(size_t i)
{
    ResizeDialog* dialog = new ResizeDialog(parent);
    if (dialog->exec(layers[i].point.x(), layers[i].point.y(),1,0) == QDialog::Accepted) {
        QTransform transform;
        transform.scale(dialog->GetScale(), dialog->GetScale());
        qDebug() << dialog->GetWidth();
        //transform.translate(dialog->GetWidth(), dialog->GetHeight());
        layers[i].point = QPoint(dialog->GetHeight(), dialog->GetWidth());
        transform.rotate(dialog->GetRotate());
        auto backup = layers[i].layer->transformed(transform);
        layers[i].layer->fill(Qt::transparent);
        QPainter painter(layers[i].layer);
        painter.drawPixmap(0,0,backup);
        qDebug() << layers[i].layer->height();
        //QPainter painter(layers[i].layer);
        //painter.drawLine(0,0,50,50);
        rerender();
    }
    delete dialog;
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
    emit newLayer(*layers.last().layer);
    rerender();
}
