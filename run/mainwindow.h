#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "viewer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public :
    MainWindow();
    ~MainWindow();

private :
    //Main Widget (Container  or Viewer)
    Viewer*  viewer;
};
#endif
