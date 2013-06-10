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
    Scene ();

    /**
     * \brief Destructeur
     */
    ~Scene ();

    /**
     * \brief Représentation
     *
     * Représentation de la scène
     */
    void draw();

    /**
     * Initialisation de la scène; appelée par le constructeur,
     * et lors de la réinitialisation de la scène
     */
    void init();
    
    /**
     * Supprime les éléments; appelée par le destructeur,
     * et lors de la réinitialisation de la scène
     */
    void clear();
    
    void animate();

    /**
     * Permet une animation pas à pas
     */
    void animer() {anim = true;}

    /* ** Interaction utilisateur ** */
    void interact();

    void changerMateriau();
    
 private :
    Fluide<3> *f;   /*!< Pointeur sur un fluide */
    Materiau<3> *m; /*!< Pointeur sur un matériau */

    bool anim;  /* pour faire l'animation pas à pas */
};
#endif
