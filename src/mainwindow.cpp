#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#include <QMessageBox>
#include <QGraphicsView>
#include <QColorDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    draw = new Draw;
    widg =  scene->addWidget(draw);
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
    delete draw;
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

void MainWindow::rectangle(){
    //TODO:
}


void MainWindow::triangle(){
    //TODO:
}


void MainWindow::circle(){
    //TODO:
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    scene->setSceneRect(0,0,event->size().width(),event->size().height());
    widg->resize(event->size());
    draw->resize(event->size());
    draw->setWidth(event->size().width());
    draw->setHeight(event->size().height());
}

void MainWindow::on_actionPencil_triggered()
{
    draw->setOption(Draw::Pen);
}

void MainWindow::on_actionEraser_triggered()
{
    draw->setOption(Draw::Erase);
}

void MainWindow::on_actionFarba_triggered()
{
    draw->setOption(Draw::Fill);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    draw->setPenWidth(value);
}

void MainWindow::on_pushButton_clicked()
{
    QColor newColor = QColorDialog::getColor(draw->penColor());

    if (newColor.isValid())
        draw->setPenColor(newColor);
}



void MainWindow::on_actionUndo_triggered()
{
    draw->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    draw->redo();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isSaved()) event->accept();
     else event->ignore();

}

bool MainWindow::isSaved()
{
    if (draw->isModified()) {
       QMessageBox::StandardButton ret;

       ret = QMessageBox::warning(this, tr("Paint"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            return draw->saveFile();

        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void MainWindow::on_actionNew_triggered()
{
    draw->newSheet();
}
