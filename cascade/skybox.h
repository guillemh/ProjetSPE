#ifndef _SKYBOX_
#define _SKYBOX_

#include <GL/glut.h>
#include "cascade.hpp"
#include <map>

/**
 * \class Skybox Classe respresentant la skybox associee a la scene
 */
class Skybox {
    /* ** Attributs ** */
 public:
    enum TextureId {
	TEX_SKY,
	TEX_HERBE
    };
 private:
    std::map<TextureId, GLuint> textures; /*!< Map des textures */
    Cascade<3> *c; /*!< Pointeur vers la cascade utilisée */
    double box_x; /*!< Coordonnée en x de la skybox */
    double box_y; /*!< Coordonnée en y de la skybox */
    double box_z; /*!< Coordonnée en z de la skybox */

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
     * \brief Initialisation 
     *
     * Initialisation de la skybox
     */
    void init();

    /**
     * \brief Initialisation du ciel 
     *
     * Initialisation des faces latérales de la skybox
     */
    void initSky();

    /**
     * \brief Initialisation du sol
     *
     * Initialisation de la face inférieure de la skybox
     */
    void initHerbe();

    /**
     * \brief Chargement d'une texture
     */
    void loadTexture(TextureId texId, const char *filename);

    /**
     * \brief Représentation
     *
     * Représentation de la skybox
     */
    void draw();

    /**
     * \brief Représentation du ciel
     *
     * Représentation des faces latérales de la skybox
     */
    void drawSky();

    /**
     * \brief Représentation du sol 
     *
     * Représentation de la face inférieure de la skybox
     */
    void drawHerbe();
    
};

#endif
