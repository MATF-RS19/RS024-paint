#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#include <QMessageBox>
#include <QGraphicsView>
#include <QColorDialog>
#include <QDir>
#include <string>

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
}

void MainWindow::createActions(){
    rectangleAction = new QAction("Rectangle", this);
    triangleAction = new QAction("Triangle", this);
    circleAction = new QAction("Circle", this);
    QString imagesDirectory = QDir::currentPath() + "/../src/images";
    rectangleAction->setIcon(QIcon(imagesDirectory + "/rectangle.png"));
    triangleAction->setIcon(QIcon(imagesDirectory + "/triangle.png"));
    circleAction->setIcon(QIcon(imagesDirectory + "/circle.png"));

    QObject::connect(rectangleAction, SIGNAL(triggered()), this, SLOT(rectangle()));
    QObject::connect(triangleAction, SIGNAL(triggered()), this, SLOT(triangle()));
    QObject::connect(circleAction, SIGNAL(triggered()), this, SLOT(circle()));
}

void MainWindow::createMenus(){
    shapeMenu = new QMenu;
    shapeMenu->addAction(rectangleAction);
    shapeMenu->addAction(triangleAction);
    shapeMenu->addAction(circleAction);
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
{
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
    int index = item->type();
    double tmpZvalue = layers[index]->zValue();
    layers[index]->setZValue(zValue);
    layers[zMaxPosition]->setZValue(tmpZvalue);
    zMaxPosition = index;
    currentDraw = layers[index];
}
