#include <QKeyEvent>
#include <QColor>
#include <list>

#include "viewer.h"

#include "scene.h"
using std::list ;

#define NBSHOTMAX 3000


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
    nbShot = 0;

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
    s = new Scene();
}


void Viewer::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix() ;
    s->draw();
    glPopMatrix();
    if (toogleRecord) {
        saveSnapshot();
        nbShot++;
    }
    if (nbShot > NBSHOTMAX) {
        exit(1);
    }
}


void Viewer::animate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    s->animate();
    glPopMatrix();
}

void Viewer::interact() {
    cout << endl << "** Modification des paramètres de la simulation **" << endl;
    s->interact();
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
    } else if (e->key()==Qt::Key_Z) {
        s->animer();
        updateGL();
    } else if ((e->key()==Qt::Key_Home) && (modifiers==Qt::NoButton)) {
        // stop the animation, and reinit the scene
        stopAnimation();
        s->init();
        toogleWireframe = true;
        toogleLight = false;
        updateGL();
    } else if (e->key()==Qt::Key_I) {
        stopAnimation();
        interact();
        updateGL();
    } else if (e->key()==Qt::Key_V) {
        s->changerAffichage();
        updateGL();
    } else if (e->key()==Qt::Key_R) {
        toogleRecord = !toogleRecord;
        nbShot = 0;
        updateGL();
    } else {
        QGLViewer::keyPressEvent(e);
    }
}

QString Viewer::helpString() const
{
        // Some usefull hints...
        QString text("<h2>V i e w e r</h2>");
        text += "Use the mouse to move the camera around the object. ";
        text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
        text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
        text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
        text += "Simply press the function key again to restore it. Several keyFrames define a ";
        text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
        text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
        text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
        text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
        text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
        text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
        text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
        text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
        text += "Press <b>Escape</b> to exit the viewer.";
        return text;
}

