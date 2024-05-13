#ifndef LAYERBUTTON_H
#define LAYERBUTTON_H

#include <QObject>
#include <QPushButton>

class layerButton : public QPushButton
{
    Q_OBJECT
    size_t num;
public:
    layerButton(size_t);

public slots:
    void handle();

signals:
    void SPClicked(size_t);
};

#endif // LAYERBUTTON_H
