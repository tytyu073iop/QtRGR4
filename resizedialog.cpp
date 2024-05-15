#include "resizedialog.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QPushButton>

ResizeDialog::ResizeDialog(QWidget* parent) : QDialog(parent)
{
    setModal(true);
    QGridLayout* grid = new QGridLayout();
    x = new QLineEdit();
    y = new QLineEdit();
    x->setValidator(new QIntValidator());
    y->setValidator(new QIntValidator());
    grid->addWidget(x, 0, 0);
    grid->addWidget(y, 0, 1);
    s = new QLineEdit();
    s->setValidator(new QDoubleValidator());
    grid->addWidget(s, 1, 0, 1, 2);
    r = new QLineEdit();
    r->setValidator(new QIntValidator());
    grid->addWidget(r, 2, 0, 1, 2);
    QPushButton* pcmdOk = new QPushButton("&Ok");
    QPushButton* pcmdCancel = new QPushButton("&Cancel");
    grid->addWidget(pcmdOk, 3, 0);
    grid->addWidget(pcmdCancel, 3, 1);
    connect(pcmdOk, SIGNAL(clicked()), SLOT(accept()));
    connect(pcmdCancel,SIGNAL(clicked()), SLOT(reject()));
    setLayout(grid);
}

ResizeDialog::~ResizeDialog()
{
    delete x;
    delete y;
    delete s;
    delete r;
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

int ResizeDialog::exec(int h, int w, float sc, int rot)
{
    height = h;
    width = w;
    scale = sc;
    rotate = rot;
    x->setText(QString::number(width));
    y->setText(QString::number(height));
    s->setText(QString::number(scale));
    r->setText(QString::number(rotate));
    return QDialog::exec();
}
