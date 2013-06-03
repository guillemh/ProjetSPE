#ifndef _SKYBOX_
#define _SKYBOX_

#include <GL/glut.h>
#include "../core/cascade.hpp"

/**
 * \class Skybox Classe respresentant la skybox associee a la scene
 */
class Skybox {
 public :
    /**
     * \brief Constructeur
     *
     * Constructeur par défaut d'un objet de classe Skybox
     */
    Skybox(const Cascade<3> *c);

    /**
     * \brief Destructeur
     */
    ~Skybox();

    /**
     * \brief Représentation
     *
     * Représentation de la skybox
     */
    void draw();
    void animate();

 private :
    Cascade<3> *c;
    double box_x;
    double box_y;
    double box_z;
};

#endif
