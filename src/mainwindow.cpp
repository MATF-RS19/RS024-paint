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
#include <QInputDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    inputWidthHeight();
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    draw = new Draw(height, width);
    zValue = 0;
    zMaxPosition = 0;
    currentDraw = draw;
    layers[zValue] = draw;
    scene->addItem(draw);
    ui->listWidget->addItem(new QListWidgetItem(QString("Layer %1").arg(zValue), nullptr, zValue));
    setWindowTitle(tr("Paint"));
    resize(height >= 600 ? 600 : height,
           width  >= 700 ? 700 : width);

    createActions();
    createMenus();
    createToolButtons();
    createToolBars();
}

MainWindow::~MainWindow()
{
    delete ui;

    for(auto key: layers.keys()) {
        delete layers.value(key);
    }

}

void MainWindow::createActions(){
    lineAction = new QAction("Line", this);
    rectangleAction = new QAction("Rectangle", this);
    triangleAction = new QAction("Triangle", this);
    circleAction = new QAction("Circle", this);
    ellipseAction = new QAction("Ellipse", this);

    QString imagesDirectory = QDir::currentPath() + "/../src/images";

    lineAction->setIcon(QIcon(imagesDirectory + "/line.png"));
    rectangleAction->setIcon(QIcon(imagesDirectory + "/rectangle.png"));
    triangleAction->setIcon(QIcon(imagesDirectory + "/triangle.png"));
    circleAction->setIcon(QIcon(imagesDirectory + "/circle.png"));
    ellipseAction->setIcon(QIcon(imagesDirectory + "/ellipse.png"));

    QObject::connect(rectangleAction, SIGNAL(triggered()), this, SLOT(rectangle()));
    QObject::connect(triangleAction, SIGNAL(triggered()), this, SLOT(triangle()));
    QObject::connect(circleAction, SIGNAL(triggered()), this, SLOT(circle()));
    QObject::connect(ellipseAction, SIGNAL(triggered()), this, SLOT(ellipse()));
    QObject::connect(lineAction, SIGNAL(triggered()), this, SLOT(line()));
}

void MainWindow::createMenus(){
    shapeMenu = new QMenu;

    shapeMenu->addAction(lineAction);
    shapeMenu->addAction(rectangleAction);
    shapeMenu->addAction(triangleAction);
    shapeMenu->addAction(circleAction);
    shapeMenu->addAction(ellipseAction);
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
    scene->setSceneRect(0, 0, event->size().width(), event->size().height());
}

void MainWindow::on_actionPencil_triggered()
{
    if(currentDraw != nullptr)
        currentDraw->setOption(Draw::Pen);
}

void MainWindow::on_actionEraser_triggered()
{
    if(currentDraw != nullptr)
        currentDraw->setOption(Draw::Erase);
}

void MainWindow::on_actionFarba_triggered()
{
    if(currentDraw != nullptr)
        currentDraw->setOption(Draw::Fill);
}

void MainWindow::rectangle()
{
    if(currentDraw != nullptr)
        currentDraw->setOption(Draw::Rectangle);
}


void MainWindow::triangle()
{
    if(currentDraw != nullptr)
        currentDraw->setOption(Draw::Triangle);
}


void MainWindow::circle()
{
    if(currentDraw != nullptr)
        currentDraw->setOption(Draw::Circle);
}

void MainWindow::ellipse()
{
    if(currentDraw != nullptr)
        currentDraw->setOption(Draw::Ellipse);
}

void MainWindow::line()
{
    if(currentDraw != nullptr)
        currentDraw->setOption(Draw::Line);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if(currentDraw != nullptr)
        currentDraw->setPenWidth(value);
}

void MainWindow::on_pushButton_clicked()
{
    if(currentDraw != nullptr){
        QColor newColor = QColorDialog::getColor(currentDraw->penColor());

        if (newColor.isValid()) {
            currentDraw->setPenColor(newColor);
        }
    }
}


void MainWindow::on_actionUndo_triggered()
{
    if(currentDraw != nullptr)
        currentDraw->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    if(currentDraw != nullptr)
        currentDraw->redo();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isSaved()) {
        event->accept();
    } else {
        event->ignore();
    }

}

bool MainWindow::isSaved()
{
    if (currentDraw !=nullptr && currentDraw->isModified()) {
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
    if(currentDraw != nullptr)
        currentDraw->newSheet();
    else
       on_AddLayer_clicked();

}

void MainWindow::on_AddLayer_clicked()
{
    Draw* newDraw = new Draw(height,width);
    zMaxPosition = ++zValue;
    newDraw->setZValue(zMaxPosition);
    layers[zValue] = newDraw;
    scene->addItem(newDraw);
    ui->listWidget->addItem(new QListWidgetItem(QString("Layer %1").arg(zValue), nullptr, zValue));
    currentDraw = newDraw;

    sortItems();
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

void MainWindow::mergePixmaps(QImage &img, QList<QImage> &layersImages,
                              const int thrNum, const int xMax, const int yMax,
                              const int numThreads, int layersImagesSize)
{
    int numRows = xMax / numThreads;
    int rest = xMax % numThreads;
    int start, end;
    if (thrNum == 0) {
        start = numRows * thrNum;
        end = (numRows * (thrNum + 1)) + rest;
     } else {
        start = numRows * thrNum + rest;
        end = (numRows * (thrNum + 1)) + rest;
     }
    for (int i = start; i < end; ++i) {
        for(int j = 0; j < yMax; ++j) {
            if(img.pixelColor(i, j) == Qt::white) {
                for(int k = 0; k<layersImagesSize; k++) {
                    if(layersImages[k].pixelColor(i, j) != Qt::white) {
                        img.setPixelColor(i, j, layersImages[k].pixelColor(i, j));
                        break;
                    }
                }
            }
        }
    }
}



void MainWindow::inputWidthHeight()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    QLabel label("Insert width and height:");
    form.addRow(&label);
    QLineEdit w(&dialog);
    QLineEdit h(&dialog);
    QIntValidator validator(500,1500,this);
    w.setValidator(&validator);
    h.setValidator(&validator);
    form.addRow(QString("Width:"),&w);
    form.addRow(QString("Height:"),&h);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    if(dialog.exec() == QDialog::Accepted && !w.text().isEmpty() && !h.text().isEmpty()) {
        width  = w.text().toInt() < 500? 500: w.text().toInt() > 1500? 1500:w.text().toInt();;
        height = h.text().toInt() < 500? 500: h.text().toInt() > 1500? 1500:h.text().toInt();
    } else {
        width = 1350;
        height = 700;
    }
}
bool compare(const QListWidgetItem *v1, const QListWidgetItem *v2)
{
    return v1->type() < v2->type();
}

void MainWindow::on_pushButton_2_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.isEmpty() || items.size() == 1) {
        return;
    }
    Draw *allTogether = new Draw(height, width);
    unsigned long numThreads = 10;
    QList<QImage> layersImages;
    std::sort(items.begin(), items.end(), compare);
    QImage img = layers[items.last()->type()]->getLastPixmap().toImage();
    int layersImagesSize = items.size() - 1;
    for(int i = 0;i<layersImagesSize;i++) {
        layersImages.push_front(layers[items[i]->type()]->getLastPixmap().toImage());
    }
    std::vector<std::thread> threads(numThreads);
    for (unsigned long i = 0; i < numThreads; ++i) {
      threads[i] = std::thread(&MainWindow::mergePixmaps, this, std::ref(img), std::ref(layersImages),
                               i, allTogether->getWidth(), allTogether->getHeight(),
                               numThreads, layersImagesSize);
    }
    for (unsigned long i = 0; i < numThreads; ++i) {
       threads[i].join();
    }

    allTogether->appendPixmapList(QPixmap::fromImage(img));
    allTogether->setPixmap(QPixmap::fromImage(img));

    zMaxPosition = ++zValue;
    allTogether->setZValue(zMaxPosition);

    layers[zValue] = allTogether;
    scene->addItem(allTogether);

    ui->listWidget->addItem(new QListWidgetItem(QString("Layer %1").arg(zValue), nullptr, zValue));
    deleteItems(items);
    currentDraw = allTogether;

    sortItems();

}


void MainWindow::on_actionSave_As_triggered()
{
    if (currentDraw != nullptr && currentDraw->isModified()) {
       currentDraw->saveFile();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if(currentDraw != nullptr)
        currentDraw->openFile();
}

void MainWindow::on_actionSave_triggered()
{
    if (currentDraw != nullptr && currentDraw->isModified()) {
        currentDraw->setModified(false);
        currentDraw->saveSameFile();
    }
}

void MainWindow::on_actionRotate_triggered()
{
    ui->graphicsView->rotate(-90);
}

void MainWindow::on_actionZoom_in_triggered()
{
    ui->graphicsView->scale(1.2, 1.2);

//    if(currentDraw != nullptr)
//        currentDraw->zoomIn(); zoom in each layer separately
}

void MainWindow::on_actionZoom_out_triggered()
{
    ui->graphicsView->scale(0.8, 0.8);

//    if(currentDraw != nullptr)
//        currentDraw->zoomOut(); zoom out each layer separately
}

void MainWindow::on_actionReset_Zoom_triggered()
{
    ui->graphicsView->resetMatrix();

//    if(currentDraw != nullptr)
//        currentDraw->resetZoom(); reset zoom on each layer separately
}

void MainWindow::deleteItems(QList<QListWidgetItem *> &items)
{
    foreach(QListWidgetItem* item, items) {
        ui->listWidget->removeItemWidget(item);
        delete layers[item->type()];
        layers.remove(item->type());
        delete item;
    }
    if(!layers.isEmpty()) {
        zMaxPosition = layers.lastKey();
    }
    else {
        zValue = -1;
        zMaxPosition = -1;
        currentDraw = nullptr;
    }

}

void MainWindow::on_DeleteLayer_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    deleteItems(items);
    sortItems();
}

void MainWindow::sortItems()
{
    QString itemText;

    for(int i = 0; i<ui->listWidget->count(); i++) {
        itemText = QString("Layer %1").arg(i);
        ui->listWidget->item(i)->setText(itemText);
    }
}
