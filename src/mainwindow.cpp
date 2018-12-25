#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QFileDialog>
#include <QDir>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath(), "Png file(*.png);;Jpeg file(*.jpeg);;Jpg file(*.jpg)");

    QPixmap pix(filename);
    scene->addPixmap(pix);

    ui->graphicsView->setScene(scene);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionPencil_triggered()
{

    ui->graphicsView->setScene(scene);
    line = new Line();
    scene->addItem(line);

}

void MainWindow::on_actionShapes_triggered()
{
    //TODO:
}
