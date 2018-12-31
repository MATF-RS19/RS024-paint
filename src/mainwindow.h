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

private slots:
    void on_actionPencil_triggered();
    void on_actionEraser_triggered();
    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_actionFarba_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();
    void on_actionNew_triggered();

    void on_AddLayer_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();
    void on_actionSave_As_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

public slots:
    void rectangle();
    void triangle();
    void circle();

protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::MainWindow *ui;
    bool isSaved();
    QGraphicsScene *scene;
    Draw *draw;
    Draw *currentDraw;
    Draw *allTogether;
    QGraphicsProxyWidget *widg;
    int zValue;
    int zMaxPosition;

    void createActions();
    void createMenus();
    void createToolBars();
    void createToolButtons();
    void mergePixmaps(QImage &img, QList<QImage> &layersImages,
                      const int thread_number, const int xMax, const int yMax, const int numThreads);

    QAction* rectangleAction;
    QAction* triangleAction;
    QAction* circleAction;

    QMenu* shapeMenu;
    QToolBar* editToolBar;
    ShapeButton* shapeToolButton;
    QList<Draw*> layers;
};

#endif // MAINWINDOW_H
