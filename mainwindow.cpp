#include "mainwindow.h"
#include <QStatusBar>
#include <QtWidgets>
#include "Tabs/LoginTab.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setFixedSize(800, 480);
    statusBar()->hide();
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    tabWidget = new CustomTabWidget();
    tabWidget->addTab(new LoginTab(), QIcon(":/img/resources/megaphone.png"), "Test 1");
    QIcon icon(":/img/resources/cctv.png");
    tabWidget->addTab(new QWidget(), icon, "Test 2");
    tabWidget->setIconSize(QSize(40,40));
    tabWidget->addTab(new QWidget(), QIcon(":/img/resources/building.png"), "Test 3");
    setCentralWidget(tabWidget);

    QFile styleFile("E:\\workspace\\MainManipulator\\resources\\dark.qss");
    //QFile styleFile( ":/img/resources/dark.qss" );
    styleFile.open( QFile::ReadOnly );

    QString style( styleFile.readAll() );
    setStyleSheet( style );
}

MainWindow::~MainWindow()
{
}


