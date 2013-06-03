#include <qapplication.h>
#include "viewer.h"
#include <GL/glut.h>

int main(int argc, char** argv)
{
	// Read command lines arguments.
	QApplication application(argc,argv);
    glutInit (&argc, argv) ;
	// Instantiate the viewer.
	Viewer viewer;

	viewer.setWindowTitle("Fenetre de test");
	// Make the viewer window visible on screen.
	viewer.show();

	// Run main loop.
	return application.exec();
}
