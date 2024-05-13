#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPainter>
//#include <Qt>
#include <QPointF>
#include <QActionGroup>
#include <QPen>
#include "paintfield.h"
#include "messagelabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString currentFile;
    PaintField* label = new PaintField(this);
    QPixmap* image = new QPixmap(500, 500);
    QColor color;
    QAction* colorAction;
    QActionGroup* actionGroup = new QActionGroup(nullptr);
    int size = QPen().width();



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    friend PaintField;
    friend MessageLabel;

public slots:
    void openAction();
    void saveAction();
    void debugDraw();
    void saveAsAction();
    void ChangeColour();
    void changeSize();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
