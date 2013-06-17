#ifndef _SCENE_CASCADE_
#define _SCENE_CASCADE_

#include <GL/glut.h>
#include "cascade.hpp"
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
    Cascade<3> *c1;  /* Pointeur vers la cascade utilisée */
    Cascade<3> *c2;  /* Pointeur vers la cascade utilisée */
    Skybox *s;       /* Pointeur vers la skybox utilisée */
    Fluide<3> *f;    /* Pointeur vers le fluide utilisé */

    bool arps;   /* permet de changer entre l'arps ou non */
    int nbBoucles;

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
     * Supprime les éléments; appelée par le destructeur,
     * et lors de la réinitialisation de la scène
     */
    void clear();
    
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
    
    /**
     * \brief Animation
     *
     * Animation de la scène
     */
    void animate();

    /**
     * @brief Interaction utilisateur
     *
     * Méthode permettant de changer interactivement entre l'ARPS
     * et le SPH traditionnel, ainsi que les seuils de l'ARPS
     */
    void interact();

    /**
     * @brief Interaction utilisateur
     *
     * Méthode permettant de changer interactivement le
     * mode d'affichage
     */
    void changerAffichage();
    
};
#endif
