#ifndef _SCENE_CASCADE_
#define _SCENE_CASCADE_

#include <GL/glut.h>
#include "cascade.hpp"
#include "skybox.h"

/**
 * \class SceneCascade Classe contenant les objets représentés sur la scène et une cascade
 */
class SceneCascade {
/* ** Attributs ** */
 private :
    Cascade<3> *c;  /*!< Pointeur vers la cascade utilisée */
    Skybox *s; /*!< Pointeur vers la skybox utilisée */

 public :
    /**
     * \brief Constructeur
     *
     * Constructeur par défaut d'un objet de classe Scène
     */
    SceneCascade();

    /**
     * \brief Destructeur
     * 
     * Destructeur d'un objet de type Scene
     */
    ~SceneCascade();

    /**
     * \brief Initialisation de la scène
     */
    
    void init();

    /**
     * \brief Représentation
     *
     * Représentation de la scène
     */
    void draw();
    
    /**
     * \brief Animation
     *
     * Animation de la scène
     */
    void animate();

};
#endif
