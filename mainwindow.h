#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString currentFile;
    QLabel* label = new QLabel();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openAction();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
