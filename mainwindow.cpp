#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QMenuBar>
#include <QKeySequence>
#include <QFileDialog>
#include <QLabel>
#include <QPainter>
#include <QActionGroup>
#include <QColorDialog>
#include <QMouseEvent>
#include <QInputDialog>
#include <QStatusBar>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include "layerlabel.h"
  #include <QSizePolicy>
#include "layerbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageSize.setHeight(label->height());
    imageSize.setWidth(label->width());
    image = new QPixmap(imageSize);
    image->fill(Qt::white);
    label->setPixmap(*image);
    QPixmap colorPM(20, 20);
    colorPM.fill(Qt::black);
    colorAction = new QAction(QIcon(colorPM), "set color");

    QWidget* widget = new QWidget;
    QGridLayout* grid = new QGridLayout(widget);
    grid->setColumnMinimumWidth(1, 200);
    grid->addWidget(label, 0, 0);
    grid->addWidget(new QPushButton("test"), 0, 1);
    grid->addLayout(layersLayout, 0, 2);

    QToolBar* toolBar = new QToolBar();
    actionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::ExclusiveOptional);
    QAction* line = new QAction(*new QIcon(":/line.svg") ,"straight line" ,actionGroup);
    QAction* curvedLine = new QAction(*new QIcon(":/curveLine.svg"), "curved line", actionGroup);
    QAction* circle = new QAction(*new QIcon(":/circle.svg"), "circle", actionGroup);
    QAction* square = new QAction(*new QIcon(":/square.svg"), "square", actionGroup);
    for (auto i : actionGroup->actions()) {
        i->setCheckable(true);
        toolBar->addAction(i);
    }
    addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);
    QToolBar* optionsBar = new QToolBar();
    connect(colorAction, &QAction::triggered, this, &MainWindow::ChangeColour);
    optionsBar->addAction(colorAction);
    QAction* sizeAction = new QAction("size", optionsBar);
    optionsBar->addAction(sizeAction);
    connect(sizeAction, &QAction::triggered, this, &MainWindow::changeSize);
    addToolBar(Qt::ToolBarArea::RightToolBarArea, optionsBar);
    QMenuBar* menuBar = new QMenuBar();
    QMenu* fileMenu = new QMenu("file" ,menuBar);
    QAction* open = new QAction("open...", fileMenu);
    open->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    // open->setShortcut(QKeySequence(Qt::Key_Open));
    connect(open, &QAction::triggered, this, &MainWindow::openAction);
    fileMenu->addAction(open);
    QAction* save = new QAction("save", fileMenu);
    save->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    connect(save, &QAction::triggered, this, &MainWindow::saveAction);
    fileMenu->addAction(save);
    QAction* saveAs = new QAction("save as...", fileMenu);
    saveAs->setShortcut(QKeySequence(Qt::ALT + Qt::Key_S));
    connect(saveAs, &QAction::triggered, this, &MainWindow::saveAsAction);
    fileMenu->addAction(saveAs);
    menuBar->addMenu(fileMenu);
    QMenu* debugMenu = new QMenu("debug" ,menuBar);
    QAction* draw = new QAction("draw", debugMenu);
    connect(draw, &QAction::triggered, this, &MainWindow::debugDraw);
    debugMenu->addAction(draw);
    menuBar->addMenu(debugMenu);
    setMenuBar(menuBar);
    label->setAutoFillBackground(true);
    // label->setStyleSheet("background-color:white;");
    setCentralWidget(widget);
    connect(label, &PaintField::newLayer, this, &MainWindow::updateLayers);

    QStatusBar* statusBar = new QStatusBar(this);
    MessageLabel* messageLabel = new MessageLabel(this);
    for (auto i : actionGroup->actions()) {
        connect(i, &QAction::triggered, messageLabel, &MessageLabel::changed);
    }
    statusBar->insertPermanentWidget(0, messageLabel);
    setStatusBar(statusBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // qDebug() << "main resize";
}

void MainWindow::openAction()
{
    currentFile = QFileDialog::getOpenFileName(this);
    image->load(currentFile);
    label->setPixmap(*image);
}

void MainWindow::saveAction()
{
    if (currentFile.isEmpty()) {
        currentFile = QFileDialog::getSaveFileName(this);
    }
    image->save(currentFile);
}

void MainWindow::debugDraw()
{
    QPainter painter;
    painter.begin(image);
    painter.drawEllipse(100, 100, 100, 100);
    painter.end();
    label->setPixmap(*image);
}

void MainWindow::saveAsAction()
{
    currentFile = QString();
    saveAction();
}

void MainWindow::ChangeColour()
{
    QColor newColor = QColorDialog::getColor(Qt::black, this);
    QPixmap newPM(20, 20);
    newPM.fill(newColor);
    colorAction->setIcon(QIcon(newPM));
    color = newColor;
}

void MainWindow::changeSize()
{
    size = QInputDialog::getInt(this, "size", "size", size, 0);
}

void MainWindow::updateLayers()
{
    //deleting
    for (size_t i = 0; i < layersLayout->rowCount(); i++) {
        auto item = static_cast<LayerLabel*>(layersLayout->itemAtPosition(i,0));
        qDebug() << layersLayout->rowCount() << item;
        if (item == nullptr) { continue; }
        layersLayout->removeItem(item);
        item->setParent(nullptr);
        delete item;
        layersLayout->update();
    }
    //if (layersLayout->rowCount() == 2) { return; }
    size_t counter = 0;
    for (auto i : label->layers) {
        LayerLabel* currentLayer = new LayerLabel(i, counter);
        connect(currentLayer->trash, &layerButton::SPClicked, label, &PaintField::del);
        connect(currentLayer->resize, &layerButton::SPClicked, label, &PaintField::resize);
        layersLayout->addLayout(currentLayer, counter, 0);
        counter++;
    }
}



