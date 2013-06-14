#include <iostream>
#include <GL/glut.h>

#include "sceneCascade.h"
#include "../core/fluide.hpp"
#include "../core/materiau.hpp"

using namespace std;


SceneCascade::SceneCascade()
    : c1(),
      c2(),
      s(),
      f(),
      arps(false)
{
    init();
}


SceneCascade::~SceneCascade() {
    clear();
}

void SceneCascade::clear() {
    delete c1;
    delete c2;
    delete f;
    delete s;
}

void SceneCascade::init() {

    /* On supprime l'éventuelle scène précédente */
    clear();
    
    /* On créé la scène, avec les paramètres initiaux */
    Materiau<3> *m = new Materiau<3>(EAU);
    Vecteur<3> d = Vecteur<3>(9, 9, 5);
    f = new Fluide<3>(m, d, 0.05, m->getDensiteRepos(), m->getPression());
    //f->colorationMetaball();
    c1 = new Cascade<3> (f);
    s = new Skybox(c1);
    s->init();
}

void SceneCascade::draw()
{
    glPushMatrix();
    c1->draw();    
    glTranslatef(0, 0., -3.0);
    s->draw();
    glPopMatrix();
}

void SceneCascade::animate()
{
    c1->animate(arps);
}

void SceneCascade::interact() {
    cout << endl << "Quels paramètres voulez-vous modifier?" << endl;
    cout << " 1. La méthode de simulation" << endl;
    cout << " 2. Les seuils de l'ARPS" << endl;
    cout << " 3. L'affichage (fonctionne aussi avec la touche v)" << endl;
    cout << " 4. Redémarrer l'animation" << endl;
    cout << "autre. Annuler et revenir à la simulation" << endl;
    int numero;
    cin >> numero;
    switch (numero) {
    case 1:
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
    case 2:
        f->changerArps();
        break;
    case 3:
        f->changerAffichage();
        break;
    case 4:
        f->init();
        return;
        break;
    default:
        return;
        break;
    }

    int on;
    cout << "Voulez-vous effectuer une nouvelle modification?" << endl;
    cout << " 1 => Oui" << endl << " 0 => Non" << endl;
    cin >> on;
    if (on == 1) {
        interact();
        return;
    }
}

void SceneCascade::changerAffichage() {
    f->changerAffichageAuto();
}
