#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#include <QMessageBox>
#include <QGraphicsView>
#include <QColorDialog>
#include <QDir>
#include <string>
#include <QColor>
#include <QPainter>
#include <iostream>
#include <thread>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    draw = new Draw;
    zValue = 0;
    zMaxPosition = 0;
    currentDraw = draw;
    layers.append(draw);
    scene->addItem(draw);
    ui->listWidget->addItem(new QListWidgetItem(QString("Layer %1").arg(zValue), nullptr, zValue));
    setWindowTitle(tr("Paint"));
    resize(700,600);
    allTogether = nullptr;

    createActions();
    createMenus();
    createToolButtons();
    createToolBars();
}

MainWindow::~MainWindow()
{
    delete ui;

    for(int i=0; i<layers.size(); i++){
        delete layers[i];
    }
    delete allTogether;
}

void MainWindow::createActions(){
    rectangleAction = new QAction("Rectangle", this);
    triangleAction = new QAction("Triangle", this);
    circleAction = new QAction("Circle", this);
    elipseAction = new QAction("Elipse", this);
    QString imagesDirectory = QDir::currentPath() + "/../src/images";
    rectangleAction->setIcon(QIcon(imagesDirectory + "/rectangle.png"));
    triangleAction->setIcon(QIcon(imagesDirectory + "/triangle.png"));
    circleAction->setIcon(QIcon(imagesDirectory + "/circle.png"));
    elipseAction->setIcon(QIcon(imagesDirectory + "/elipse.png"));

    QObject::connect(rectangleAction, SIGNAL(triggered()), this, SLOT(rectangle()));
    QObject::connect(triangleAction, SIGNAL(triggered()), this, SLOT(triangle()));
    QObject::connect(circleAction, SIGNAL(triggered()), this, SLOT(circle()));
    QObject::connect(elipseAction, SIGNAL(triggered()), this, SLOT(elipse()));
}

void MainWindow::createMenus(){
    shapeMenu = new QMenu;
    shapeMenu->addAction(rectangleAction);
    shapeMenu->addAction(triangleAction);
    shapeMenu->addAction(circleAction);
    shapeMenu->addAction(elipseAction);
}

void MainWindow::createToolButtons(){
    shapeToolButton = new ShapeButton;
    shapeToolButton->setMenu(shapeMenu);
    shapeToolButton->setDefaultAction(rectangleAction);
    QString filepath = QDir::currentPath() + "/../src/images/insert-shapes-512.png";
    shapeToolButton->setIcon(QIcon(filepath));
}

void MainWindow::createToolBars(){
    ui->toolBar_2->addWidget(shapeToolButton);

}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    scene->setSceneRect(0,0,event->size().width(),event->size().height());
}

void MainWindow::on_actionPencil_triggered()
{
    currentDraw->setOption(Draw::Pen);
}

void MainWindow::on_actionEraser_triggered()
{
    currentDraw->setOption(Draw::Erase);
}

void MainWindow::on_actionFarba_triggered()
{
    currentDraw->setOption(Draw::Fill);
}

void MainWindow::rectangle(){
    currentDraw->setOption(Draw::Rectangle);
}


void MainWindow::triangle(){
    currentDraw->setOption(Draw::Triangle);
}


void MainWindow::circle(){
    currentDraw->setOption(Draw::Circle);
}

void MainWindow::elipse(){
    currentDraw->setOption(Draw::Elipse);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    currentDraw->setPenWidth(value);
}

void MainWindow::on_pushButton_clicked()
{
    QColor newColor = QColorDialog::getColor(currentDraw->penColor());

    if (newColor.isValid())
        currentDraw->setPenColor(newColor);
}



void MainWindow::on_actionUndo_triggered()
{
    currentDraw->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    currentDraw->redo();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isSaved()) event->accept();
     else event->ignore();

}

bool MainWindow::isSaved()
{
    if (currentDraw->isModified()) {
       QMessageBox::StandardButton ret;

       ret = QMessageBox::warning(this, tr("Paint"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            return currentDraw->saveFile();

        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void MainWindow::on_actionNew_triggered()
{
    currentDraw->newSheet();
}

void MainWindow::on_AddLayer_clicked()
{   if(allTogether != nullptr){
        zValue--;
        scene->removeItem(allTogether);
        delete allTogether;
        allTogether = nullptr;
    }
    Draw* newDraw = new Draw;
    zValue++;
    zMaxPosition = zValue;
    newDraw->setZValue(zMaxPosition);
    layers.append(newDraw);
    scene->addItem(newDraw);
    ui->listWidget->addItem(new QListWidgetItem(QString("Layer %1").arg(zValue), nullptr, zValue));
    currentDraw = newDraw;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if(allTogether != nullptr){
        zValue--;
        scene->removeItem(allTogether);
        delete allTogether;
        allTogether = nullptr;
    }
    int index = item->type();
    double tmpZvalue = layers[index]->zValue();
    layers[index]->setZValue(zValue);
    layers[zMaxPosition]->setZValue(tmpZvalue);
    zMaxPosition = index;
    currentDraw = layers[index];
}

void MainWindow::mergePixmaps(QImage &img,QList<QImage> &layersImages,const int thrNum,const int xMax,const int yMax,const int numThreads){
    int layersImagesSize = layers.size()-1;
    int numRows = xMax / numThreads;
    int rest = xMax % numThreads;
    int start, end;
    if (thrNum == 0) {
        start = numRows * thrNum;
        end = (numRows * (thrNum + 1)) + rest;
     }else {
        start = numRows * thrNum + rest;
        end = (numRows * (thrNum + 1)) + rest;
     }
    for (int i = start; i < end; ++i)
        for(int j = 0; j < yMax; ++j)
            if(img.pixelColor(i,j) == Qt::white)
                for(int k = 0;k<layersImagesSize;k++)
                    if(layersImages[k].pixelColor(i,j) != Qt::white){
                        img.setPixelColor(i,j,layersImages[k].pixelColor(i,j));
                        break;
                    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(allTogether != nullptr)
        delete allTogether;
    allTogether = new Draw;
    int numThreads = 10;
    QImage img = layers.last()->getLastPixmap().toImage();
    QList<QImage> layersImages;
    QList<QPixmap> layersPixmap;
    for(int i = 0;i<layers.size()-1;i++)
        layersImages.append(layers[i]->getLastPixmap().toImage());
    std::thread threads[numThreads];
    for (int i = 0; i < numThreads; ++i) {
      threads[i] = std::thread(&MainWindow::mergePixmaps,this, std::ref(img), std::ref(layersImages),
                               i,allTogether->getWidth(),allTogether->getHeight(),numThreads);
    }
    for (int i = 0; i < numThreads; ++i) {
       threads[i].join();
     }
    allTogether->setPixmap(QPixmap::fromImage(img));
    scene->addItem(allTogether);
    allTogether->setZValue(++zValue);
}


void MainWindow::on_actionSave_As_triggered()
{
    if (currentDraw->isModified()) {
       currentDraw->saveFile();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    currentDraw->openFile();
}

void MainWindow::on_actionSave_triggered()
{
    if (currentDraw->isModified()) {
        currentDraw->setModified(false);
        currentDraw->saveSameFile();
    }
}

void MainWindow::on_actionRotate_triggered()
{
    ui->graphicsView->rotate(-90);
}
