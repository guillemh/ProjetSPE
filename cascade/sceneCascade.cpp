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
    c = new Cascade<3> (f);
    s = new Skybox(c);
    init();
}


SceneCascade::~SceneCascade() {}

void SceneCascade::init() {
    s->init();
}

void SceneCascade::draw()
{
    glPushMatrix();
    c->draw();
    s->draw();
    glPopMatrix();
}

void SceneCascade::animate()
{
    c->animate();
}
