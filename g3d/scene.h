#ifndef _SCENE_
#define _SCENE_

#include <GL/glut.h>
#include "../core/fluide.hpp"
#include "../core/materiau.hpp"

/**
 * \class Scene Classe contenant les objets représentés sur la scène
 */
class Scene {
 public :
    /**
     * \brief Constructeur
     *
     * Constructeur par défaut d'un objet de classe Scène
     */
    Scene () ;

    /**
     * \brief Représentation
     *
     * Représentation de la scène
     */
    void draw() ;

    /**
     * \brief Destructeur
     */
    ~Scene () ;

 private :
    Fluide<3> *f ; /*!< Pointeur sur un fluide */
	Materiau<3> *m ; /*!< Pointeur sur un matériau */
};
#endif
