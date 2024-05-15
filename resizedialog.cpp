#include "resizedialog.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QIntValidator>

ResizeDialog::ResizeDialog(QWidget* parent, int height, int width, float scale, int rotate) :
    QDialog(parent), height(height), width(width), scale(scale), rotate(rotate)
{
    setModal(true);
    QGridLayout grid(this);
    x = new QLineEdit(QString::number(width));
    y = new QLineEdit(QString::number(height));
    x->setValidator(new QIntValidator());
    y->setValidator(new QIntValidator());
    grid.addWidget(x, 0, 0);
    grid.addWidget(y, 0, 1);
    s = new QLineEdit(QString::number(scale));
    s->setValidator(new QDoubleValidator());
    grid.addWidget(s, 1, 0, 1, 2);
    r = new QLineEdit(QString::number(rotate));
    r->setValidator(new QIntValidator());
    grid.addWidget(r, 2, 0, 1, 2);
}

int ResizeDialog::GetHeight()
{
    height = y->text().toInt();
    return height;
}

int ResizeDialog::GetWidth()
{
    width = x->text().toInt();
    return width;
}

int ResizeDialog::GetRotate()
{
    rotate = r->text().toInt();
    return rotate;
}

float ResizeDialog::GetScale()
{
    scale = s->text().toFloat();
    return scale;
}
