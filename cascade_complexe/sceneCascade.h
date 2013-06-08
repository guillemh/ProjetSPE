#ifndef _SCENE_CASCADE_
#define _SCENE_CASCADE_

#include <GL/glut.h>
#include "../cascade/cascade.hpp"
#include "skybox.h"


/**
 * \class SceneCascade 
 * @brief Classe contenant les objets représentés sur la scène 
 *
 * Les objets de la scène sont une cascade animée et une skybox
 */
class SceneCascade {
    /* ** Attributs ** */
 private :
  Cascade<3> *c;  /*!< Pointeur vers la cascade utilisée */
  Skybox *s;      /*!< Pointeur vers la skybox utilisée */
 public :
    /**
     * \brief Constructeur
     *
     * Constructeur par défaut
     */
    SceneCascade();

    /**
     * \brief Destructeur
     */
    ~SceneCascade();

    /**
     * @brief Initialisation
     *
     * Initialisations pour les objets de la scène
     */  
    
    void init();

    /**
     * \brief Représentation
     *
     * Représentation de la scène
     */
    void draw();

    void drawSphere(int scaley, int scalex, GLfloat r);
        
    /**
     * \brief Animation
     *
     * Animation de la scène
     */
    void animate();

};
#endif
