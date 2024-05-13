#ifndef MESSAGELABEL_H
#define MESSAGELABEL_H

#include <QLabel>
#include <QObject>

class MainWindow;

class MessageLabel : public QLabel
{
    Q_OBJECT
    MainWindow* parent;
public:
    MessageLabel(MainWindow* parent = nullptr);
public slots:
    void changed();
};

#endif // MESSAGELABEL_H
