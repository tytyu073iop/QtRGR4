#include "layerbutton.h"

layerButton::layerButton(size_t num) : num(num) {
    connect(this, &layerButton::clicked, this, &layerButton::handle);
}

void layerButton::handle()
{
    emit SPClicked(num);
}


