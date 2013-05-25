#include <iostream>
#include <GL/glut.h>

#include "scene.h"
#include "../core/fluide.hpp"
#include "../core/materiau.hpp"

using namespace std;


/* Constructeur à modifier, évidemment */
Scene::Scene () {
	m = new Materiau<3> (EAU) ;
	int d [3] = {10, 10, 10} ;
    f = new Fluide<3> (m, d, 1.0) ;
}

Scene::~Scene () {
}

void Scene::draw () {
	glPushMatrix () ;
	f->draw () ;	
	glPopMatrix () ;
}

void Scene::animate () {
	f->majDensitePression();
	f->majPositionVitesse();
}
