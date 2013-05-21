#include <qapplication.h>
#include "mainwindow.h"

using namespace std;

int main(int argc, char** argv)
{
    QApplication application(argc, argv);
    MainWindow window;
    window.setMinimumSize(800,400);
    window.show();
    return application.exec();
}
