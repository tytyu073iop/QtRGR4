#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPainter>
//#include <Qt>
#include <QPointF>
#include <QActionGroup>
#include <QPen>
#include <QResizeEvent>
#include <QSize>
#include "paintfield.h"
#include "messagelabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString currentFile;
    QSize imageSize;
    PaintField* label = new PaintField(this);
    QPixmap* image;
    QColor color;
    QAction* colorAction;
    QActionGroup* actionGroup = new QActionGroup(nullptr);
    int size = QPen().width();
    QGridLayout* layersLayout = new QGridLayout();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void resizeEvent(QResizeEvent *event);
    friend PaintField;
    friend MessageLabel;


public slots:
    void openAction();
    void saveAction();
    void debugDraw();
    void saveAsAction();
    void ChangeColour();
    void changeSize();
    void updateLayers();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
