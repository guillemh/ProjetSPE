#include <iostream>

#include "skybox.h"

using namespace std;

Skybox::Skybox(const Cascade<3> *c)
{
    box_x = c->getBassinY() * 10;
    box_y = c->getBassinX() * 10;
    box_z = c->getBassinZ();
    int dimension = 2*box_x;
}

Skybox::~Skybox() {}

void Skybox::draw()
{

    
 
    glBegin(GL_QUADS);
    // *box_xace avant
    glNormal3d(0, 0, 1);
    glVertex3d(0.5*box_x, -0.5*box_x, 0.5*box_x);
    glVertex3d(0.5*box_x, 0.5*box_x, 0.5*box_x);
    glVertex3d(-0.5*box_x, 0.5*box_x, 0.5*box_x);
    glVertex3d(-0.5*box_x, -0.5*box_x, 0.5*box_x);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face droite
    glNormal3d(1, 0, 0);
    glVertex3d(0.5*box_x, 0.5*box_x, -0.5*box_x);
    glVertex3d(0.5*box_x, 0.5*box_x, 0.5*box_x);
    glVertex3d(0.5*box_x, -0.5*box_x, 0.5*box_x);
    glVertex3d(0.5*box_x, -0.5*box_x, -0.5*box_x);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face gauche
    glNormal3d(-1, 0, 0);
    glVertex3d(-0.5*box_x, -0.5*box_x, 0.5*box_x);
    glVertex3d(-0.5*box_x, 0.5*box_x, 0.5*box_x);
    glVertex3d(-0.5*box_x, 0.5*box_x, -0.5*box_x);
    glVertex3d(-0.5*box_x, -0.5*box_x, -0.5*box_x);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // dessous
    glNormal3d(0, -1, 0);
    glVertex3d(0.5*box_x, -0.5*box_x, 0.5*box_x);
    glVertex3d(-0.5*box_x, -0.5*box_x, 0.5*box_x);
    glVertex3d(-0.5*box_x, -0.5*box_x, -0.5*box_x);
    glVertex3d(0.5*box_x, -0.5*box_x, -0.5*box_x);
 
    glEnd();
 
    glBegin(GL_QUADS);
    // face arriere
    glNormal3d(0, 0, -1);
    glVertex3d(0.5*box_x, 0.5*box_x, -0.5*box_x);
    glVertex3d(0.5*box_x, -0.5*box_x, -0.5*box_x);
    glVertex3d(-0.5*box_x, -0.5*box_x, -0.5*box_x);
    glVertex3d(-0.5*box_x, 0.5*box_x, -0.5*box_x);
    
    glEnd();
    
}

void Skybox::animate() {}


