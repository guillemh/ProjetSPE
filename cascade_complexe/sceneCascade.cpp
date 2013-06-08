#include <iostream>
#include <GL/glut.h>

#include "sceneCascade.h"
#include "../core/fluide.hpp"
#include "../core/materiau.hpp"

using namespace std;


SceneCascade::SceneCascade()
{
    Materiau<3> *m = new Materiau<3>(EAU);
    int d [3] = {5, 5, 5};
    Fluide<3> *f = new Fluide<3>(m, d, 0.1, m->getDensiteRepos(), m->getPression());
    c = new Cascade<3> (f);
    s = new Skybox(c);   
    init();
}


SceneCascade::~SceneCascade() {}

void SceneCascade::init() {
    s->init();
}

void SceneCascade::draw()
{
    glPushMatrix();
    c->draw();
   
    glPushMatrix();
    glTranslatef(-5,0,5);
    c->draw();
    glPopMatrix(); 

    //glPushMatrix();
    //glTranslatef(-10,0,0);

    //glScaled(1.5,1.5,1.4);
    //glRotated(90,1,0,0);
    
    //drawSphere(70,30,5);
    //glPopMatrix(); 

    s->draw();    
    glPopMatrix();
}


void SceneCascade::drawSphere(int scaley, int scalex, GLfloat r) {
    int i, j;
    GLfloat v[scalex*scaley][3];
 
    for (i=0; i<scalex; ++i) {
      for (j=0; j<scaley; ++j) {
	v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
	v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
	v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
      }
    }

 
    glBegin(GL_QUADS);
    for (i=0; i<scalex-1; ++i) {
      for (j=0; j<scaley; ++j) {
	glVertex3fv(v[i*scaley+j]);
	glVertex3fv(v[i*scaley+(j+1)%scaley]);
	glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
	glVertex3fv(v[(i+1)*scaley+j]);
      }
    }
    glEnd();
}

void SceneCascade::animate()
{
    c->animate();
}
