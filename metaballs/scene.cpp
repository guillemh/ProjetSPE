#include <iostream>
#include <GL/glut.h>
#include <cstdlib>

#include "scene.h"
#include "metaballs.hpp"
#include "../core/vecteur.hpp"
#include "../core/particule.hpp"
#include <vector>

using std::vector;

// Scene::Scene() :
//     m (Metaballs(Vecteur<3>(), 0.1, 2, 5, 5, 5))
// {
    
//     Vecteur<3> v = Vecteur<3>(2);
//     Vecteur<3> v2 = Vecteur<3>(2);
//     Vecteur<3> v3 = Vecteur<3>(3.7);
//     Vecteur<3> v4 = Vecteur<3>(2, 3, 2);
//     Vecteur<3> v5 = Vecteur<3>(0.1, 2, 2);
//     Particule<3> * p = new Particule<3>(1, v, Vecteur<3>());
//     Particule<3> * p2 = new Particule<3>(2, v2, Vecteur<3>());
//     // Particule<3> * p3 = new Particule<3>(3, v3, Vecteur<3>());
//     // Particule<3> * p4 = new Particule<3>(4, v4, Vecteur<3>());
//     // Particule<3> * p5 = new Particule<3>(5, v5, Vecteur<3>());
//     list<Particule<3> *> l;
//     l.push_back(p);
//     l.push_back(p2);
//     // l.push_back(p3);
//     // l.push_back(p4);
//     // l.push_back(p5);
    
//     m.coloration(l);
    
//     delete p;
//     delete p2;
//     // delete p3;
//     // delete p4;
//     // delete p5;
// }

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

// ATTENTION : Décommenter la coloration des sommets dans metaballs.cpp
// Scene::Scene() {
//     Vecteur<3> v1 = Vecteur<3>(2);
//     Vecteur<3> v2 = Vecteur<3>(3.5);
//     // Vecteur<3> v3 = Vecteur<3>(3.7);
//     // Vecteur<3> v4 = Vecteur<3>(2, 3, 2);
//     // Vecteur<3> v5 = Vecteur<3>(0.1, 2, 2);
//     Particule<3> * p = new Particule<3>(1, v1, Vecteur<3>());
//     Particule<3> * p2 = new Particule<3>(2, v2, Vecteur<3>());
//     // Particule<3> * p3 = new Particule<3>(3, v3, Vecteur<3>());
//     // Particule<3> * p4 = new Particule<3>(4, v4, Vecteur<3>());
//     // Particule<3> * p5 = new Particule<3>(5, v5, Vecteur<3>());
//     list<Particule<3> *> l;
//     l.push_back(p);
//     l.push_back(p2);
//     // l.push_back(p3);
//     // l.push_back(p4);
//     // l.push_back(p5);
//     Metaballs *m = new Metaballs (Vecteur<3>(), 0.1, 1, 5, 5, 5);
//     m->coloration(l);
//     v.push_back (m);
//     delete p;
//     delete p2;
//     // delete p3;
//     // delete p4;
//     // delete p5;
// }

Scene::~Scene() {
    v.clear();
}

void Scene::draw() {
    glPushMatrix();
    GLfloat y_min = -16;
    GLfloat z_min = 0;
    for (unsigned int i = 0 ; i < v.size() ; i++) {
	glPushMatrix();
	// glTranslatef (-0.5, y_min + float((i % 16) * 2), z_min + float((i / 16) * 2));
	v[i]->draw();
	glPopMatrix();
    }
    glPopMatrix();
}
