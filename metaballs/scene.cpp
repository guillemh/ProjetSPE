#include <iostream>
#include <GL/glut.h>
#include <cstdlib>

#include "scene.h"
#include "metaballs.hpp"
#include "../core/vecteur.hpp"
#include "../core/particule.hpp"
#include <vector>

using std::vector;

Scene::Scene() {
    v = vector<Metaballs *> ();
    double x_min = -5;
    double y_min = -5;
    double z_min = -5;
    Vecteur<3> origine = Vecteur<3> (x_min, y_min, z_min);
    Metaballs *m = new Metaballs (origine, 0.5, 4, 10, 10, 10);
    m->coloration();
    v.push_back (m);
}

Scene::~Scene() {
	v.clear();
}

void Scene::draw() {
    glPushMatrix();
    v[0]->draw();
    glPopMatrix();
}
