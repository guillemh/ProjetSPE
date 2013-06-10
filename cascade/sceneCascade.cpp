#include <iostream>
#include <GL/glut.h>

#include "sceneCascade.h"
#include "../core/fluide.hpp"
#include "../core/materiau.hpp"

using namespace std;


SceneCascade::SceneCascade()
{
    Materiau<3> *m = new Materiau<3>(EAU);
    Vecteur<3> d = Vecteur<3>(5, 5, 50);
    Fluide<3> *f = new Fluide<3>(m, d, 0.05, m->getDensiteRepos(), m->getPression());
    //f->colorationMetaball();
    c1 = new Cascade<3> (f);
    s = new Skybox(c1);
    init();
}


SceneCascade::~SceneCascade() {}

void SceneCascade::init() {
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
    c1->animate();}
