#include "mainwindow.h"


MainWindow::MainWindow()
{
    //Central widget
    viewer = new Viewer(this);
    this->setCentralWidget(viewer);
}

MainWindow::~MainWindow()
{
    delete viewer;
}
