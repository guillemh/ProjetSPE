#ifndef _SCENE_CASCADE_
#define _SCENE_CASCADE_

#include <GL/glut.h>
#include "../core/cascade.hpp"

/**
 * \class SceneCascade Classe contenant les objets représentés sur la scène et une cascade
 */
class SceneCascade {
 public :
    /**
     * \brief Constructeur
     *
     * Constructeur par défaut d'un objet de classe Scène
     */
    SceneCascade () ;

    /**
     * \brief Destructeur
     */
    ~SceneCascade () ;

    /**
     * \brief Représentation
     *
     * Représentation de la scène
     */
    void draw() ;
    
    void animate() ;

 private :
    Cascade<3> *c ;
};
#endif
