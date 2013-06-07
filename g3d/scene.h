#ifndef _SCENE_
#define _SCENE_

#include <GL/glut.h>
#include "../core/fluide.hpp"
#include "../core/materiau.hpp"

/**
 * \class Scene
 * @brief Classe contenant les objets représentés sur la scène
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
     * \brief Destructeur
     */
    ~Scene () ;

    /**
     * \brief Représentation
     *
     * Représentation de la scène
     */
    void draw() ;
    
    void animate() ;

    void animer() {anim = true;}
    
 private :
    Fluide<3> *f ; /*!< Pointeur sur un fluide */
    Materiau<3> *m ; /*!< Pointeur sur un matériau */

    bool anim;  /* pour faire l'animation pas à pas */
};
#endif
