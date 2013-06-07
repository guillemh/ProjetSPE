#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

#include "scene.h"
#include "../core/fluide.hpp"
#include "../core/materiau.hpp"

using namespace std;


/* Constructeur à modifier, évidemment */
Scene::Scene() {
    
    srand (time (NULL));   
    anim = false;
    m = new Materiau<3>(EAU);
    // int d [3] = {2, 1, 1};
    int d [3] = {3, 3, 50};
    f = new Fluide<3>(m, d, 0.05, m->getDensiteRepos(), m->getPression()); 
    
    //    Vecteur<3> vec0 = Vecteur<3>();
    //    
    //    Vecteur<3> vec1 = Vecteur<3>(0, 0, 0.1);
    //    Vecteur<3> vec2 = Vecteur<3>(0, 0.07, 0.02);
    //    Vecteur<3> vec3 = Vecteur<3>(0.02, 0.05, 0.09);
    //    Vecteur<3> vec4 = Vecteur<3>(0.07, 0.04, 0.05);
    //    Vecteur<3> vec5 = Vecteur<3>(0.03, 0.04, 0.06);
    //    Vecteur<3> vec6 = Vecteur<3>(0.04, 0.07, 0.03);
    //    Vecteur<3> vec7 = Vecteur<3>(0.03, 0.1, 0.04);
    //    Vecteur<3> vec8 = Vecteur<3>(0.07, 0.07, 0.1);
    //    Vecteur<3> vec9 = Vecteur<3>(0.06, 0.04, 0.03);
    //    Vecteur<3> vec10 = Vecteur<3>(0.06, 0.05, 0.08);
    //    
    //    Particule<3> *p1 = new Particule<3>(1, vec1, vec0);
    //    Particule<3> *p2 = new Particule<3>(2, vec2, vec0);
    //    Particule<3> *p3 = new Particule<3>(3, vec3, vec0);
    //    Particule<3> *p4 = new Particule<3>(4, vec4, vec0);
    //    Particule<3> *p5 = new Particule<3>(5, vec5, vec0);
    //    Particule<3> *p6 = new Particule<3>(6, vec6, vec0);
    //    Particule<3> *p7 = new Particule<3>(7, vec7, vec0);
    //    Particule<3> *p8 = new Particule<3>(8, vec8, vec0);
    //    Particule<3> *p9 = new Particule<3>(9, vec9, vec0);
    //    Particule<3> *p10 = new Particule<3>(10, vec10, vec0);
    //    
    //    f = new Fluide<3>(m);
    //    f->ajouteParticule(p1);
    //    f->ajouteParticule(p2);
    //    f->ajouteParticule(p3);
    //    f->ajouteParticule(p4);
    //    f->ajouteParticule(p5);
    //    f->ajouteParticule(p6);
    //    f->ajouteParticule(p7);
    //    f->ajouteParticule(p8);
    //    f->ajouteParticule(p9);
    //    f->ajouteParticule(p10);

//      m = new Materiau<3>(EAU);
//    
//      Vecteur<3> vInit = Vecteur<3> (0, 0.1, 0);
//      Vecteur<3> pos1 = Vecteur<3> (0, -0.02, 0);
//      Vecteur<3> pos2 = Vecteur<3> (0, 0.02, 0);
//      Particule<3> *p1 = new Particule<3> (1, pos1, Vecteur<3>(), m->getDensiteRepos(), m->getPression(), m->getMasseParticules());
//      Particule<3> *p2 = new Particule<3> (2, pos2, Vecteur<3>(), m->getDensiteRepos(), m->getPression(), m->getMasseParticules());
//    
//      f = new Fluide<3> (m);
//      f->ajouteParticule(p1);
//      f->ajouteParticule(p2);
}

Scene::~Scene() {
    delete m;
    delete f;
}

void Scene::draw() {
    glPushMatrix();
    f->draw();
    //f->affiche();
    glPopMatrix();
}

void Scene::animate() {
    // if (anim) {
        f->majDensitePression();
        f->majPositionVitesse();
    //     f->schemaIntegration();
    //     f->affiche();
    //     anim = false;
    // }    
}
