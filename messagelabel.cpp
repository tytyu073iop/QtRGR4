#include "messagelabel.h"
#include "mainwindow.h"

MessageLabel::MessageLabel(MainWindow* parent) : parent(parent) {
    setText("No instrument selected");
}

void MessageLabel::changed()
{
    setText(parent->actionGroup->checkedAction() == nullptr ? "no instrument selected" : parent->actionGroup->checkedAction()->text());
}
