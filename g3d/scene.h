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

    /**
     * @brief Animation
     *
     * Appelle les fonctions d'animation des objets de la scène
     */
    void animate();

    /**
     * Permet une animation pas à pas, à l'appel de la touche 'Z',
     * lorsque les lignes concernées sont décommentées dans animate()
     */
    void animer() {anim = true;}


    /* ** Interaction utilisateur ** */

    /**
     * @brief Interaction utilisateur
     *
     * Lance l'interface d'interaction pour les paramètres du système
     */
    void interact();

    /**
     * @brief Interaction utilisateur
     *
     * Permet de changer de materiau pendant la simulation
     */
    void changerMateriau();

    /**
     * @brief Interaction utilisateur
     *
     * Permet de changer de méthode d'affichage pendant l'interaction
     */
    void changerAffichage();
    
 private :
    Fluide<3> *f;   /*!< Pointeur sur un fluide */
    Materiau<3> *m; /*!< Pointeur sur un matériau */

    bool anim;  /* pour faire l'animation pas à pas */
    bool arps;  /* pour changer entre l'arps ou pas */
};
#endif
