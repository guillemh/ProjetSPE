#ifndef _SCENE_
#define _SCENE_

#include <GL/glut.h>
#include "metaballs.hpp"
#include <vector>

using std::vector;

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
    Scene();

    /**
     * \brief Destructeur
     */
    ~Scene();

    /**
     * \brief Représentation
     *
     * Représentation de la scène
     */
    void draw();

 private :
    // Metaballs m;
    vector<Metaballs *> v;
};
#endif
