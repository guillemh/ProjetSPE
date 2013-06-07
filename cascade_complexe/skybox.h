#ifndef _SKYBOX_
#define _SKYBOX_

#include <GL/glut.h>
#include "../cascade/cascade.hpp"
#include <map>

/**
 * \class Skybox 
 * @brief Classe donnant les objets de la scène
 *
 * Elle est représentée par des plans entourant la scène,
 * et comprend également la cascade
 */
class Skybox {
    /* ** Attributs ** */
 public:
    /**
     * @enum TextureId
     * Identifiants pour les différentes textures utilisées
     */
    enum TextureId {
	TEX_SKY,
	TEX_HERBE
    };
 private:
    std::map<TextureId, GLuint> textures;  /*!< Map des textures */
    Cascade<3> *c;                         /*!< Pointeur vers la cascade utilisée */
    double box_x;                          /*!< Coordonnée en x de la skybox */
    double box_y;                          /*!< Coordonnée en y de la skybox */
    double box_z;                          /*!< Coordonnée en z de la skybox */

 public :

    /**
     * \brief Constructeur
     *
     * Constructeur par défaut
     * @param c Pointeur vers la cascade à mettre dans la scène
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
    void initSol();

    /**
     * \brief Chargement d'une texture
     * @param texId Identifiant pour la texture à charger
     * @param filename Nom du fichier contenant la texture
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
    void drawSol();
    
};

#endif
