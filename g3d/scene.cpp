#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

#include "scene.h"
#include "../core/fluide.hpp"
#include "../core/materiau.hpp"

using namespace std;


Scene::Scene()
    : f(),
      m()
{
    
    srand (time (NULL));
    init();
    
}

Scene::~Scene() {
    clear();
}

void Scene::init() {

    /* On supprime l'éventuelle scène précédente */
    clear();

    /* On créé la scène, avec les paramètres initiaux */
    anim = false;
    
    //    m = new Materiau<3>(EAU);
    //    int d [3] = {10, 10, 20};
    //    f = new Fluide<3>(m, d, 0.05, m->getDensiteRepos(), m->getPression(), Vecteur<3>(), -0.25, 0.25, -0.25, 1.0, 0.0); 
    
    
    m = new Materiau<3>(EAU);
    Vecteur<3> d = Vecteur<3>(2, 2, 50);
    f = new Fluide<3>(m, d, 0.05, m->getDensiteRepos(), m->getPression(), Vecteur<3>());
    
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


    f->colorationMetaball();
}

void Scene::clear() {
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
    // f->schemaIntegration();
    // f->affiche();
    //     anim = false;
    // }    
}

void Scene::interact() {
    cout << endl << "Quels paramètres voulez-vous modifier?" << endl;
    cout << " 1. Le matériau" << endl;
    cout << " 2. Les paramètres du matériau" << endl;
    cout << " 3. Les paramètres de l'agencement du fluide" << endl;
    cout << " autre. Annuler et revenir à la simulation" << endl;
    int numero;
    cin >> numero;
    switch (numero) {
    case 1:
        changerMateriau();
        break;
    case 2:
        m->changerParam();
        break;
    case 3:
        f->changerParam();
        break;
    others:
        break;
    }

    cout << endl << "Où voulez-vous reprendre la simulation?" << endl;
    cout << " 1. Reprendre là où elle en est" << endl;
    cout << " 2. Recommencer avec les nouveaux paramètres" << endl;
    cin >> numero;
    if (numero == 2) {
        f->init();
    }
}

void Scene::changerMateriau() {
    cout << "Quel matériau voulez-vous?" << endl;
    cout << " 1. Eau" << endl;
    cout << " 2. Mucus" << endl;
    cout << " 3. Vapeur" << endl;
    int numero;
    cin >> numero;
    TypeFluide type;
    switch(numero) {
    case 1:
        type = EAU;
        break;
    case 2:
        type = MUCUS;
        break;
    case 3:
        type = VAPEUR;
        break;
    others:
        return;
    }
    m->changerNature(type);
}
