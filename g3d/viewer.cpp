#include <QKeyEvent>
#include <QColor>
#include <list>

#include "viewer.h"

using std::list ;

Viewer::Viewer () {
}


Viewer::~Viewer()
{
    delete s ;
}


void Viewer::init()
{

    //=== VIEWING PARAMETERS
    restoreStateFromFile();
    toogleWireframe = true;  // filled faces
    toogleLight = false;     // light off

    if (toogleLight == true) glEnable(GL_LIGHTING);
    else glDisable(GL_LIGHTING);
	
    if (toogleWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR);
    glEnable(GL_COLOR_MATERIAL);
	
    setSceneRadius(8.0f);
	
    //=== INIT SCENE
    s = new Scene () ;

}


void Viewer::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix() ;
    s->draw();
    glPopMatrix();
    if (toogleRecord) {
	saveSnapshot();
    }
}


void Viewer::animate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix () ;
    s->animate();
    glPopMatrix () ;
}


void Viewer::keyPressEvent(QKeyEvent *e)
{
    // Get event modifiers key
    const Qt::KeyboardModifiers modifiers = e->modifiers();

    if ((e->key()==Qt::Key_W) && (modifiers==Qt::NoButton)) {
	toogleWireframe = !toogleWireframe;
	if (toogleWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	updateGL();
    } else if ((e->key()==Qt::Key_L) && (modifiers==Qt::NoButton)) {
	toogleLight = !toogleLight;
	if (toogleLight == true) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);
	updateGL();
    } else if (e->key()==Qt::Key_R) {
	toogleRecord = !toogleRecord;
	updateGL();
    } else {
	QGLViewer::keyPressEvent(e);
    }
}

