#ifndef MYLAYER_H
#define MYLAYER_H
#include <QPixmap>
#include <QPoint>
#include <QObject>
#include <QPropertyAnimation>

enum class Figure {
    straight, line, square, circle
};

struct MyLayer : QObject {
private:
    Q_OBJECT
public:
    Q_PROPERTY(int angle MEMBER angle)
    Q_PROPERTY(QPoint point MEMBER point)
    Figure figa;
    QPixmap* layer;
    QPoint point;
    int angle = 0;
    QColor color;
    bool operator==(const MyLayer& other) const {
        return layer == other.layer;
    }
    ~MyLayer();
public slots:
    void startAnimation();
    void valuChanged();
signals:
    void rerender();
};

inline MyLayer::~MyLayer()
{
    //delete layer;
}

inline void MyLayer::startAnimation()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this, figa == Figure::circle ? "angle" : "point");
    qDebug() << "animation!" << animation->propertyName();
    animation->setDuration(500);
    QPoint mov;
    if (figa == Figure::straight) {
        mov = QPoint(20,20);
    } else if(figa == Figure::line) {
        mov = QPoint(100, 0);
    } else if(figa == Figure::square) {
        mov = QPoint(0, 100);
    }
    if (figa == Figure::circle) {
        int newAngle = 90;
        animation->setKeyValueAt(0.5f, newAngle);
        animation->setEndValue(angle);
    } else {
        animation->setKeyValueAt(0.5f, point + mov);
        animation->setEndValue(point);
    }
    connect(animation, SIGNAL(valueChanged(QVariant)), this, SLOT(valuChanged()));
    animation->start();
}

inline void MyLayer::valuChanged()
{
    emit rerender();
}

#endif // MYLAYER_H
