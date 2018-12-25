/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionExit;
    QAction *actionPencil;
    QAction *actionShapes;
    QAction *actionEraser;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFIle;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(639, 406);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionPencil = new QAction(MainWindow);
        actionPencil->setObjectName(QStringLiteral("actionPencil"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/images/pencil.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPencil->setIcon(icon);
        actionShapes = new QAction(MainWindow);
        actionShapes->setObjectName(QStringLiteral("actionShapes"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/images/shapes.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShapes->setIcon(icon1);
        actionEraser = new QAction(MainWindow);
        actionEraser->setObjectName(QStringLiteral("actionEraser"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/images/eraser_transparent.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEraser->setIcon(icon2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 639, 25));
        menuFIle = new QMenu(menuBar);
        menuFIle->setObjectName(QStringLiteral("menuFIle"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFIle->menuAction());
        menuFIle->addAction(actionNew);
        menuFIle->addAction(actionOpen);
        menuFIle->addAction(actionSave);
        menuFIle->addAction(actionSave_As);
        menuFIle->addAction(actionExit);
        mainToolBar->addAction(actionPencil);
        mainToolBar->addAction(actionShapes);
        mainToolBar->addAction(actionEraser);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionPencil->setText(QApplication::translate("MainWindow", "Pencil", 0));
        actionShapes->setText(QApplication::translate("MainWindow", "Shapes", 0));
        actionEraser->setText(QApplication::translate("MainWindow", "Eraser", 0));
        menuFIle->setTitle(QApplication::translate("MainWindow", "FIle", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
