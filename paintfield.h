#ifndef PAINTFIELD_H
#define PAINTFIELD_H

#include <QLabel>
#include <QObject>
#include <QPointF>
#include <QPainter>
#include <QVector>
#include <QPair>
#include <QGridLayout>
#include "MyLayer.h"

class MainWindow;

class PaintField : public QLabel
{
    Q_OBJECT
    MainWindow* parent;
    QPainter* painter;
    QPointF bPoint;
    QPixmap* activeLayer;
protected:
    QVector<MyLayer> layers;
    void rerender();
    void add(QPointF, QPixmap*, const QColor&);
    void remove(QPointF, QPixmap*);
public:
    PaintField(MainWindow* parent = nullptr);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    friend MainWindow;

public slots:
    void del(size_t);
    void resize(size_t);
    void changeColor(const QColor&, size_t);

signals:
    void newLayer(const QPixmap&);
};

#endif // PAINTFIELD_H
