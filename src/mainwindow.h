#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "draw.h"

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

protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::MainWindow *ui;
    bool isSaved();

    QGraphicsScene *scene;
    Draw *draw;
    QGraphicsProxyWidget *widg;
};

#endif // MAINWINDOW_H
