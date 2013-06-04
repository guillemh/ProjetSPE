#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "skybox.h"
#include <QGLViewer/qglviewer.h>

using namespace std;

Skybox::Skybox(const Cascade<3> *c)
{
    box_x = c->getBassinY() * 20;
    box_y = c->getBassinX() * 20;
    box_z = c->getBassinZ();

}

Skybox::~Skybox() {}

void Skybox::init()
{
    glEnable(GL_TEXTURE_2D);
    //filteringMode = 0;	
    loadTexture(TEX_CRATE, "images/crate.tiff");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glDisable(GL_TEXTURE_2D);
}

void Skybox::loadTexture(TextureId texId, const char *filename)
{
    // generates an OpenGL texture id, and store it in the map
    GLuint id;
    glGenTextures(1, &id);
    textures[texId] = id;

    // load a texture file as a QImage
    QImage img = QGLWidget::convertToGLFormat(QImage(filename));

    // specify the texture (2D texture, rgba, single file)
    glBindTexture(GL_TEXTURE_2D, textures[texId]);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0,
		  GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
}

void Skybox::draw()
{ 
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textures[TEX_CRATE]);
    //setFiltering();

    glBegin(GL_QUADS);
    // face droite
    glNormal3d(0, 0, 1);
    glTexCoord2f(0, 0);
    glVertex3f(-0.5*box_x, 0.5*box_x, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0.5*box_x, 0.5*box_x, 0);
    glTexCoord2f(1, 1);
    glVertex3f(0.5*box_x, 0.5*box_x, 1*box_x);
    glTexCoord2f(0, 1);
    glVertex3f(-0.5*box_x, 0.5*box_x, 1*box_x);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face avant
    glNormal3d(1, 0, 0);
    glTexCoord2f(0, 0);
    glVertex3d(0.5*box_x, 0.5*box_x, 0);
    glTexCoord2f(1, 0);
    glVertex3d(0.5*box_x, 0.5*box_x, box_x);
    glTexCoord2f(1, 1);
    glVertex3d(0.5*box_x, -0.5*box_x, box_x);
    glTexCoord2f(0, 1);
    glVertex3d(0.5*box_x, -0.5*box_x, 0);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face arriere
    glNormal3d(-1, 0, 0);
    glTexCoord2f(0, 0);
    glVertex3d(-0.5*box_x, -0.5*box_x, box_x);
    glTexCoord2f(1, 0);
    glVertex3d(-0.5*box_x, 0.5*box_x, box_x);
    glTexCoord2f(1, 1);
    glVertex3d(-0.5*box_x, 0.5*box_x, 0);
    glTexCoord2f(0, 1);
    glVertex3d(-0.5*box_x, -0.5*box_x, 0);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face gauche
    glNormal3d(0, -1, 0);
    glTexCoord2f(0, 0);
    glVertex3d(0.5*box_x, -0.5*box_x, box_x);
    glTexCoord2f(1, 0);
    glVertex3d(-0.5*box_x, -0.5*box_x, box_x);
    glTexCoord2f(1, 1);
    glVertex3d(-0.5*box_x, -0.5*box_x, 0);
    glTexCoord2f(0, 1);
    glVertex3d(0.5*box_x, -0.5*box_x, 0);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face dessous
    glNormal3d(0, 0, -1);
    glTexCoord2f(0, 0);
    glVertex3d(0.5*box_x, 0.5*box_x, 0);
    glTexCoord2f(1, 0);
    glVertex3d(0.5*box_x, -0.5*box_x, 0);
    glTexCoord2f(1, 1);
    glVertex3d(-0.5*box_x, -0.5*box_x, 0);
    glTexCoord2f(0, 1);
    glVertex3d(-0.5*box_x, 0.5*box_x, 0);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
}

void Skybox::animate() {}


