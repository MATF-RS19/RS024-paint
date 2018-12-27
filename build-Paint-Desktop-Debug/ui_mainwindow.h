/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionPencil;
    QAction *actionShape;
    QAction *actionSelect;
    QAction *actionEraser;
    QAction *actionLayer_1;
    QAction *actionLayer_2;
    QAction *actionLayer_3;
    QAction *actionLayer_4;
    QAction *actionFarba;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QSlider *horizontalSlider;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(915, 709);
        MainWindow->setFocusPolicy(Qt::NoFocus);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/rec/images/new_file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/rec/images/save_transparent.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/rec/images/save-as.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QStringLiteral("images/save_transparent.png"), QSize(), QIcon::Selected, QIcon::On);
        actionSave_As->setIcon(icon2);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/rec/images/transp_exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/rec/images/undo-6.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon4);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/rec/images/redo-6.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon5);
        actionPencil = new QAction(MainWindow);
        actionPencil->setObjectName(QStringLiteral("actionPencil"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/rec/images/Pencil-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPencil->setIcon(icon6);
        actionShape = new QAction(MainWindow);
        actionShape->setObjectName(QStringLiteral("actionShape"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/rec/images/insert-shapes-512.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShape->setIcon(icon7);
        actionSelect = new QAction(MainWindow);
        actionSelect->setObjectName(QStringLiteral("actionSelect"));
        actionSelect->setEnabled(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/rec/images/Cursor-Select-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect->setIcon(icon8);
        QFont font;
        actionSelect->setFont(font);
        actionEraser = new QAction(MainWindow);
        actionEraser->setObjectName(QStringLiteral("actionEraser"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/rec/images/eraser-icon-14.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEraser->setIcon(icon9);
        actionLayer_1 = new QAction(MainWindow);
        actionLayer_1->setObjectName(QStringLiteral("actionLayer_1"));
        QFont font1;
        font1.setPointSize(12);
        actionLayer_1->setFont(font1);
        actionLayer_2 = new QAction(MainWindow);
        actionLayer_2->setObjectName(QStringLiteral("actionLayer_2"));
        QFont font2;
        font2.setPointSize(13);
        actionLayer_2->setFont(font2);
        actionLayer_3 = new QAction(MainWindow);
        actionLayer_3->setObjectName(QStringLiteral("actionLayer_3"));
        actionLayer_3->setFont(font2);
        actionLayer_4 = new QAction(MainWindow);
        actionLayer_4->setObjectName(QStringLiteral("actionLayer_4"));
        actionLayer_4->setFont(font2);
        actionFarba = new QAction(MainWindow);
        actionFarba->setObjectName(QStringLiteral("actionFarba"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/rec/images/Fill.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFarba->setIcon(icon10);
        actionZoom_in = new QAction(MainWindow);
        actionZoom_in->setObjectName(QStringLiteral("actionZoom_in"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/rec/images/zoom-in.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_in->setIcon(icon11);
        actionZoom_out = new QAction(MainWindow);
        actionZoom_out->setObjectName(QStringLiteral("actionZoom_out"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/rec/images/zoom-out.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_out->setIcon(icon12);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setMinimumSize(QSize(0, 0));
        centralWidget->setMouseTracking(false);
        centralWidget->setFocusPolicy(Qt::NoFocus);
        centralWidget->setAutoFillBackground(false);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 70, 821, 561));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(0, 20, 211, 51));
        horizontalSlider->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"border: 1px solid #999999;\n"
"height: 18px;\n"
"\n"
"border-radius: 9px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"width: 18px;\n"
" background-image: url(:/slider-knob.png)\n"
"}\n"
"\n"
"QSlider::add-page:qlineargradient {\n"
"background: lightgrey;\n"
"border-top-right-radius: 9px;\n"
"border-bottom-right-radius: 9px;\n"
"border-top-left-radius: 0px;\n"
"border-bottom-left-radius: 0px;\n"
"}\n"
"\n"
"QSlider::sub-page:qlineargradient {\n"
"background: blue;\n"
"border-top-right-radius: 0px;\n"
"border-bottom-right-radius: 0px;\n"
"border-top-left-radius: 9px;\n"
"border-bottom-left-radius: 9px;\n"
"}"));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(220, 20, 121, 41));
        pushButton->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));\n"
"font: 13pt \"Ubuntu\";"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 121, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 0, 121, 21));
        MainWindow->setCentralWidget(centralWidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QStringLiteral("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);
        MainWindow->insertToolBarBreak(toolBar_2);

        toolBar->addAction(actionNew);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSave_As);
        toolBar->addAction(actionExit);
        toolBar->addAction(actionZoom_in);
        toolBar->addAction(actionZoom_out);
        toolBar_2->addAction(actionSelect);
        toolBar_2->addAction(actionPencil);
        toolBar_2->addAction(actionFarba);
        toolBar_2->addAction(actionShape);
        toolBar_2->addAction(actionEraser);
        toolBar_2->addAction(actionUndo);
        toolBar_2->addAction(actionRedo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionNew->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", Q_NULLPTR));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", Q_NULLPTR));
        actionPencil->setText(QApplication::translate("MainWindow", "Pencil", Q_NULLPTR));
        actionShape->setText(QApplication::translate("MainWindow", "Shape", Q_NULLPTR));
        actionSelect->setText(QApplication::translate("MainWindow", "Select", Q_NULLPTR));
        actionEraser->setText(QApplication::translate("MainWindow", "Eraser", Q_NULLPTR));
        actionLayer_1->setText(QApplication::translate("MainWindow", "Layer 1", Q_NULLPTR));
        actionLayer_2->setText(QApplication::translate("MainWindow", "Layer  2", Q_NULLPTR));
        actionLayer_3->setText(QApplication::translate("MainWindow", "Layer 3", Q_NULLPTR));
        actionLayer_4->setText(QApplication::translate("MainWindow", "Layer 4", Q_NULLPTR));
        actionFarba->setText(QApplication::translate("MainWindow", "Fill", Q_NULLPTR));
        actionZoom_in->setText(QApplication::translate("MainWindow", "Zoom in", Q_NULLPTR));
        actionZoom_out->setText(QApplication::translate("MainWindow", "Zoom out", Q_NULLPTR));
        pushButton->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Pencil Size", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Pencil Color", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
