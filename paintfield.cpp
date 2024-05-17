#include "paintfield.h"
#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QRectF>
#include <algorithm>
#include <QFileDialog>
#include <QDebug>
#include "resizedialog.h"
#include <QGraphicsColorizeEffect>

void PaintField::rerender()
{
    qDebug() << "rerendering";
    *parent->image = QPixmap(parent->imageSize);
    QPainter paint(parent->image);
    paint.eraseRect(0,0, parent->imageSize.width(), parent->imageSize.height());
    paint.drawPixmap(0,0,*parent->raw);
    for (const auto& i : layers) {
        auto rot = i->angle;
        paint.rotate(rot);
        paint.drawPixmap(i->point.x(), i->point.y(), *i->layer, 0, 0, parent->imageSize.width(), parent->imageSize.height());
        paint.rotate(-rot);
    }
    this->setPixmap(*(parent->image));
}

void PaintField::add(QPointF point, QPixmap* pm, const QColor& color, const Figure& figa)
{
    QPainter paint(parent->image);
    paint.drawPixmap(point, *pm);
    MyLayer* layer = new MyLayer();
    layer->layer = pm;
    layer->point = point.toPoint();
    layer->color = color;
    layer->figa = figa;
    connect(layer, SIGNAL(rerender()), this, SLOT(rerender()));
    layers.push_back(layer);
    this->setPixmap(*(parent->image));
}

void PaintField::removelast()
{
    //delete pm;
    layers.pop_back();
    rerender();
    //del on us
}

PaintField::PaintField(MainWindow* parent) : parent(parent) {
    //layers.push_back({QPointF(0,0), parent->image});

}

void PaintField::resizeEvent(QResizeEvent *event)
{
    // qDebug() << "label resize" << event->size();
    // auto xnum = event->oldSize().width() / event->size().width();
    // auto ynum = event->oldSize().height() / event->size().height();
    // QTransform transform(xnum, 0, 0, ynum, 0, 0);
    // for (auto i : layers) {
    //     auto backup = *i.second;
    //     i.second->fill(Qt::transparent);
    //     QPainter painter(i.second);
    //     painter.setTransform(transform);

    // }
    // if (event->oldSize().height() <= 0 || event->oldSize().width() <= 0) { return; }
    // QSize scale(event->size() - event->oldSize());
    // parent->imageSize += scale;
    // *parent->image = parent->image->scaled(parent->imageSize);
    // for (const auto& i : layers) {
    //     *i->layer = i->layer->scaled(parent->imageSize);
    // }
    // rerender();
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
    if (dialog->exec(layers[i]->point.x(), layers[i]->point.y(),1,0) == QDialog::Accepted) {
        QTransform transform;
        transform.scale(dialog->GetScale(), dialog->GetScale());
        qDebug() << dialog->GetWidth();
        //transform.translate(dialog->GetWidth(), dialog->GetHeight());
        layers[i]->point = QPoint(dialog->GetHeight(), dialog->GetWidth());
        transform.rotate(dialog->GetRotate());
        auto backup = layers[i]->layer->transformed(transform);
        layers[i]->layer->fill(Qt::transparent);
        QPainter painter(layers[i]->layer);
        painter.drawPixmap(0,0,backup);
        qDebug() << layers[i]->layer->height();
        //QPainter painter(layers[i].layer);
        //painter.drawLine(0,0,50,50);
        rerender();
    }
    delete dialog;
}

void PaintField::changeColor(const QColor & color, size_t i)
{
    auto image = layers[i]->layer->toImage();
    qDebug() << layers[i]->color << color << image.pixelColor(0,0);
    for (int var = 0; var < image.height(); ++var) {
        for (int j = 0; j < image.width(); ++j) {
            if (image.pixelColor(j, var) != QColor(0,0,0,0)) {
                image.setPixelColor(j, var, color);
            }
        }
    }
    image.save(QFileDialog::getSaveFileName(parent));
    layers[i]->color = color;
    *layers[i]->layer = QPixmap::fromImage(image);
    rerender();
}

void PaintField::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MouseButton::RightButton) {
        for (const auto& i : layers) {
            i->startAnimation();
        }
        return;
    }
    activeLayer = new QPixmap(parent->imageSize);
    activeLayer->fill(Qt::transparent);
    painter = new QPainter(activeLayer);
    QPen pen(parent->color);
    pen.setWidth(parent->size);
    painter->setPen(pen);
    bPoint = event->localPos();
    MyLayer* layer = new MyLayer;
    layer->layer = activeLayer;
    auto text = parent->actionGroup->checkedAction()->iconText();
    if (text == "curved line") {
        layer->figa = Figure::line;
    }
    layers.push_back(layer);
}

void PaintField::mouseMoveEvent(QMouseEvent* event) {
    if (painter == nullptr) { return; }
    auto text = parent->actionGroup->checkedAction()->iconText();
    if (text == "curved line") {
        painter->drawPoint(event->localPos());
        rerender();
        return;
    }
    activeLayer->fill(Qt::transparent);
    removelast();
    //activeLayer->clear();
    if (text == "straight line") {
        painter->drawLine(bPoint, event->localPos());
        add(QPointF(0, 0), activeLayer, parent->color, Figure::straight);
    } else if (text == "circle") {
        painter->drawEllipse(QRect(bPoint.toPoint(), event->localPos().toPoint()));
        add(QPointF(0, 0), activeLayer, parent->color, Figure::circle);
    } else if (text == "square") {
        painter->drawRect(QRect(bPoint.toPoint(), event->localPos().toPoint()));
        add(QPointF(0, 0), activeLayer, parent->color, Figure::square);
    }
}

void PaintField::mouseReleaseEvent(QMouseEvent *event) {
    //painter->drawLine(bPoint, event->localPos());
    if (painter == nullptr) { return; }
    painter->end();
    delete painter;
    painter = nullptr;
    emit newLayer(*layers.last()->layer);
    rerender();
}
