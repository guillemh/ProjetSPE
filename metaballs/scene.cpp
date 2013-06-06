#include <iostream>
#include <GL/glut.h>
#include <cstdlib>

#include "scene.h"
#include "metaballs.hpp"
#include "../core/vecteur.hpp"
#include "../core/particule.hpp"
#include <vector>

using std::vector;

Scene::Scene() :
    m (Metaballs(Vecteur<3>(), 0.05, 0.1, 1, 1, 1))
{
    
    Vecteur<3> v = Vecteur<3>(0.2);
    Vecteur<3> v2 = Vecteur<3>(0.3);
    Particule<3> * p = new Particule<3>(1, v, Vecteur<3>());
    Particule<3> * p2 = new Particule<3>(2, v2, Vecteur<3>());
    list<Particule<3> *> l;
    l.push_back(p);
    l.push_back(p2);
    
    m.coloration(l);
    
    delete p;
    delete p2;
}

Scene::~Scene() {
}

void Scene::draw() {
    glPushMatrix();
	m.draw();
    glPopMatrix();
}
