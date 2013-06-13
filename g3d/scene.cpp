#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

#include "scene.h"
#include "../core/fluide.hpp"
#include "../core/materiau.hpp"

using namespace std;

#define TRACES 1  // 0 si on ne veut aucune trace à l'exécution

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
    arps = true;
    
    
    m = new Materiau<3>(EAU);
    Vecteur<3> d = Vecteur<3>(1, 1, 2);
    double bord = 0.01;
    double ecart = 0.5;
    f = new Fluide<3>(m, d, ecart, m->getDensiteRepos(), m->getPression(), Vecteur<3>(), -bord, bord, -bord, bord, 0.);

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

void Scene::clear() {
    delete m;
    delete f;
}

void Scene::draw() {
    glPushMatrix();
    f->draw();
    // f->affiche();
    glPopMatrix();
}

void Scene::animate() {
    if (anim) {
        if (arps) {
            if (TRACES) {
                f->schemaIntegration_Traces();
            } else {
                f->schemaIntegration();
            }
        } else {
            f->majDensitePression();
            f->majPositionVitesse();
        }
        // f->affiche();
        anim = false;
    }
}

void Scene::interact() {
    cout << endl << "Quels paramètres voulez-vous modifier?" << endl;
    cout << " 1. Les paramètres du système" << endl;
    cout << " 2. Le matériau" << endl;
    cout << " 3. Les paramètres du matériau" << endl;
    cout << " 4. Les paramètres du fluide" << endl;
    cout << " 5. La méthode de simulation" << endl;
    cout << " 6. L'affichage (fonctionne aussi avec la touche v)" << endl;
    cout << " 7. Redémarrer l'animation" << endl;
    cout << " autre. Annuler et revenir à la simulation" << endl;
    int numero;
    cin >> numero;
    bool chgt = false;
    switch (numero) {
    case 1:
        m->changerSysteme();
        break;
    case 2:
        changerMateriau();
        break;
    case 3:
        m->changerParam();
        break;
    case 4:
        chgt = f->changerParam();
        break;
    case 5:
        cout << "Quel algorithme de simulation voulez-vous (actuel = ";
        if (arps) {
            cout << "ARPS)?" << endl;
        } else {
            cout << "SPH traditionnel)?" << endl;
        }
        cout << " 1. SPH traditionnel" << endl;
        cout << " 2. ARPS" << endl;
        int num;
        cin >> num;
        if (num == 1) {
            arps = false;
        } else if (num == 2) {
            arps = true;
        }
        break;
    case 6:
        f->changerAffichage();
        break;
    case 7:
        f->init();
        return;
        break;
    default:
        return;
        break;
    }

    int on;
    if (!chgt) {
        cout << "Voulez-vous effectuer une nouvelle modification?" << endl;
        cout << " 1 => Oui" << endl << " 0 => Non" << endl;
        cin >> on;
        if (on == 1) {
            interact();
            return;
        }
        cout << endl << "Où voulez-vous reprendre la simulation?" << endl;
        cout << " 1. Reprendre là où elle en est" << endl;
        cout << " 2. Recommencer avec les nouveaux paramètres" << endl;
        cin >> numero;
        if (numero == 2) {
            f->init();
        }
    } else {
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
    default:
        return;
    }
    m->changerNature(type);
}

void Scene::changerAffichage() {
    f->changerAffichageAuto();
}
