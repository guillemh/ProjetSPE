#include <iostream>

#include "skybox.h"

using namespace std;

Skybox::Skybox(const Cascade<3> *c)
{
    box_x = c->getBassinY() * 20;
    box_y = c->getBassinX() * 20;
    box_z = c->getBassinZ();
}

Skybox::~Skybox() {}

void Skybox::draw()
{

    
 
    glBegin(GL_QUADS);
    // face droite
    glNormal3d(0, 0, 1);
    glVertex3f(-0.5*box_x, 0.5*box_x, 1*box_x);
    glVertex3f(0.5*box_x, 0.5*box_x, 1*box_x);
    glVertex3f(0.5*box_x, 0.5*box_x, 0);
    glVertex3f(-0.5*box_x, 0.5*box_x, 0);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face avant
    glNormal3d(1, 0, 0);
    glVertex3d(0.5*box_x, 0.5*box_x, 0);
    glVertex3d(0.5*box_x, 0.5*box_x, box_x);
    glVertex3d(0.5*box_x, -0.5*box_x, box_x);
    glVertex3d(0.5*box_x, -0.5*box_x, 0);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face arriere
    glNormal3d(-1, 0, 0);
    glVertex3d(-0.5*box_x, -0.5*box_x, box_x);
    glVertex3d(-0.5*box_x, 0.5*box_x, box_x);
    glVertex3d(-0.5*box_x, 0.5*box_x, 0);
    glVertex3d(-0.5*box_x, -0.5*box_x, 0);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face gauche
    glNormal3d(0, -1, 0);
    glVertex3d(0.5*box_x, -0.5*box_x, box_x);
    glVertex3d(-0.5*box_x, -0.5*box_x, box_x);
    glVertex3d(-0.5*box_x, -0.5*box_x, 0);
    glVertex3d(0.5*box_x, -0.5*box_x, 0);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face dessous
    glNormal3d(0, 0, -1);
    glVertex3d(0.5*box_x, 0.5*box_x, 0);
    glVertex3d(0.5*box_x, -0.5*box_x, 0);
    glVertex3d(-0.5*box_x, -0.5*box_x, 0);
    glVertex3d(-0.5*box_x, 0.5*box_x, 0);
    
    glEnd();
    
}

void Skybox::animate() {}


