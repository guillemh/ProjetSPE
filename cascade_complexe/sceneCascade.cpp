#include <iostream>
#include <GL/glut.h>

#include "sceneCascade.h"
#include "../core/fluide.hpp"
#include "../core/materiau.hpp"

using namespace std;


SceneCascade::SceneCascade()
{
    Materiau<3> *m = new Materiau<3>(EAU);
    int d [3] = {5, 5, 5};
    Fluide<3> *f = new Fluide<3>(m, d, 0.1, m->getDensiteRepos(), m->getPression());
   c1 = new Cascade<3> (f);
   c2 = new Cascade<3> (f, c1->getBassinX(), c1->getBassinY(), c1->getBassinZ()+5, c1->getObstacleX(), c1->getObstacleY(), c1->getObstacleZ(), c1->getPenteAngle(), c1->getPenteX(), c1->getPenteY(), c1->getPenteZ());
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
    c2->draw();
    s->draw();
    glPopMatrix();
}

void SceneCascade::animate()
{
    c1->animate();
    c2->animate();
}
