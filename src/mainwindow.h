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

private slots:
    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionPencil_triggered();

    void on_actionShapes_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem* item;
    Line *line;
};

#endif // MAINWINDOW_H
