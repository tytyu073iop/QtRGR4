#ifndef PAINTFIELD_H
#define PAINTFIELD_H

#include <QLabel>
#include <QObject>
#include <QPointF>
#include <QPainter>
#include <QVector>
#include <QPair>

class MainWindow;

class PaintField : public QLabel
{
    Q_OBJECT
    MainWindow* parent;
    QPainter* painter;
    QPointF bPoint;
    QPixmap* activeLayer;
protected:
    QVector<QPair<QPointF, QPixmap*>> layers;
    void rerender();
    void add(QPointF, QPixmap*);
    void remove(QPointF, QPixmap*);
public:
    PaintField(MainWindow* parent = nullptr);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // PAINTFIELD_H
