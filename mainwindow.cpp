#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QMenuBar>
#include <QKeySequence>
#include <QFileDialog>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QToolBar* toolBar = new QToolBar();
    QAction* line = new QAction(*new QIcon(":/line.svg") ,"Draw straight line" ,toolBar);
    toolBar->addAction(line);
    addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);
    QMenuBar* menuBar = new QMenuBar();
    QMenu* fileMenu = new QMenu("file" ,menuBar);
    QAction* open = new QAction("open...", fileMenu);
    connect(open, &QAction::triggered, this, &MainWindow::openAction);
    open->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    fileMenu->addAction(open);
    menuBar->addMenu(fileMenu);
    setMenuBar(menuBar);
    label->setAutoFillBackground(true);
    label->setStyleSheet("background-color:white;");
    setCentralWidget(label);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openAction()
{
    currentFile = QFileDialog::getOpenFileName(this);
    QPixmap image(currentFile);
    label->setPixmap(image);
}

