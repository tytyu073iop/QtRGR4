#ifndef LAYERLABEL_H
#define LAYERLABEL_H

#include <QGridLayout>
#include <QObject>
#include "MyLayer.h"
#include <QLabel>
#include "layerbutton.h"
#include "colorbutton.h"

class LayerLabel : public QGridLayout
{
    Q_OBJECT
    QLabel* preview;
    QLabel* text;
public:
    layerButton* trash;
    layerButton* resize;
    ColorButton* cb;
    ~LayerLabel();
    LayerLabel(const MyLayer &i, size_t counter);
};

#endif // LAYERLABEL_H
