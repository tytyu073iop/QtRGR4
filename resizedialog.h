#ifndef RESIZEDIALOG_H
#define RESIZEDIALOG_H

#include <QDialog>
#include <QObject>
#include <QLineEdit>

class ResizeDialog : public QDialog
{
    Q_OBJECT
    int height, width;
    float scale;
    int rotate;
    QLineEdit* x;
    QLineEdit* y;
    QLineEdit* s;
    QLineEdit* r;
public:
    ResizeDialog(QWidget *parent);
    ~ResizeDialog();
    int GetHeight();
    int GetWidth();
    int GetRotate();
    float GetScale();
    int exec(int height, int width, float scale, int rotate);
};

#endif // RESIZEDIALOG_H
