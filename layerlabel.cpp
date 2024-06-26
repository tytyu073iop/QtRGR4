#include "layerlabel.h"
#include "layerbutton.h"
#include "MyLayer.h"
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include "colorbutton.h"

LayerLabel::~LayerLabel()
{
    delete preview;
    delete text;
    delete trash;
    delete resize;
    delete cb;
}

LayerLabel::LayerLabel(const MyLayer* i, size_t counter)
{
    QPixmap pm(50,30);
    pm.fill(Qt::white);
    auto buff = i->layer->scaled(50, 30);
    QPainter painter(&pm);
    painter.drawPixmap(0,0, buff);
    preview = new QLabel();
    preview->setPixmap(pm);
    //preview->setFixedSize(50, 30);
    this->addWidget(preview, 0, 0);
    text = new QLabel(QString::number(counter));
    //text->setFixedSize(50, 30);
    this->addWidget(text, 0, 1);
    //currentLayer->addWidget(text, 0, 2);
    trash = new layerButton(counter);
    trash->setText("delete");
    //trash->setFixedSize(10, 30);
    //connect(trash, &layerButton::SPClicked, label, &PaintField::del);
    this->addWidget(trash, 0, 2);
    resize = new layerButton(counter);
    resize->setText("edit");
    this->addWidget(resize, 0, 3);
    cb = new ColorButton(i->color, counter);
    this->addWidget(cb, 0, 4);
    //layersLayout->addLayout(currentLayer, counter, 0);
}
