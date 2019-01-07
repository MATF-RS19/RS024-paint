#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "draw.h"
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QDebug>
#include <QListWidgetItem>
#include "shapebutton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void resizeEvent(QResizeEvent *event) override;
    int height;
    int width;

private slots:
    void on_actionPencil_triggered();

    void on_actionEraser_triggered();

    void on_horizontalSlider_valueChanged(int value);

    void on_Color_clicked();

    void on_actionBackgroundFill_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionNew_triggered();

    void on_AddLayer_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_ShowSelected_clicked();

    void on_actionSave_As_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionRotate_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_actionReset_Zoom_triggered();

    void on_DeleteLayer_clicked();

    void sortItems();

public slots:
    void rectangle();
    void triangle();
    void circle();
    void ellipse();
    void line();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Draw *draw;
    Draw *currentDraw;
    int zValue;
    int zMaxPosition;
    bool isSaved();

    void createActions();
    void createMenus();
    void createToolBars();
    void createToolButtons();
    void inputWidthHeight();
    void mergePixmaps(QImage &img, QList<QImage> &layersImages,
                      const int thread_number, const int xMax, const int yMax, const int numThreads, int layersImagesSize);
    void deleteItems(QList<QListWidgetItem*> &items);
    QAction* rectangleAction;
    QAction* triangleAction;
    QAction* circleAction;
    QAction* ellipseAction;
    QAction* lineAction;

    QMenu* shapeMenu;
    QToolBar* editToolBar;
    ShapeButton* shapeToolButton;
    QMap<int, Draw*> layers;
};

#endif // MAINWINDOW_H
