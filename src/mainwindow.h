#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDialog>
#include <QtGui>
#include <QtCore>
#include "line.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    QPointF pointB,pointE;
protected:

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Line *line;
};

#endif // MAINWINDOW_H
