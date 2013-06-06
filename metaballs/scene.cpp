#include <iostream>
#include <GL/glut.h>
#include <cstdlib>

#include "scene.h"
#include "metaballs.hpp"
#include "../core/vecteur.hpp"
#include <vector>

using std::vector;

Scene::Scene() {
    v = vector<Metaballs *> ();
	double y_min = -16;
	double z_min = 0;
	for (int i = 0 ; i < 128 ; i++) {
		Vecteur<3> origine = Vecteur<3> (-0.5, y_min + (double((i % 16) << 1)), z_min + (double ((i / 16) << 1)));
		Metaballs *m = new Metaballs (origine, 1, 0.05, 1, 1, 1);
		m->coloration (i);
		v.push_back (m);
	}
}

Scene::~Scene() {
	v.clear();
}

void Scene::draw() {
    glPushMatrix();
	GLfloat y_min = -16;
	GLfloat z_min = 0;
	for (int i = 0 ; i < 128 ; i++) {
		glPushMatrix();
		glTranslatef (-0.5, y_min + float((i % 16) * 2), z_min + float((i / 16) * 2));
		v[i]->draw();
		glPopMatrix();
	}	
    glPopMatrix();
}
