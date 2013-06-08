#ifndef _METABALLS_
#define _METABALLS_

#include <list>
#include <iostream>
#include "particule.hpp"
#include "../core/vecteur.hpp"

using std::list;

/** 
 * \class Metaballs
 * @brief Classe discrétisant l'espace pour afficher un fluide avec des surfaces implicites
 * 
 */

class Metaballs {

    /* ** Attributs ** */
private:
    bool debutAnim;              /*!< Indique si on est au début de l'animation */
    int n;                       /*!< Nombre de cubes selon l'axe (Ox) */
    int p;                       /*!< Nombre de cubes selon l'axe (Oy) */
    int q;                       /*!< Nombre de cubes selon l'axe (Oz) */
    double*** points;            /*!< Tableau de booléens, chaque booléen étant associé à un point de l'espace :
		                              un booléen indique si le sommet doit être marqué ou non, pour avoir
		                              la configuration du cube qui sera défini à l'aide de huit points */
    Vecteur<3> origine;          /*!< Origine spatiale de l'espace rectangulaire considéré dans le maillage */
    double cote;                 /*!< Côté d'un cube */
    double rayon;                /*!< Rayon d'une particule */
    int configurations[128][12]; /*!< Look-up table de toutes les configurations possibles
                                      pour l'algorithme des Marching Cubes */

    /* ** Constructeurs ** */
public:
    /**
     * \brief Constructeur
     *
     * Alloue le tableau de points
     * \param _origine Origine spatiale de l'espace rectangulaire considéré dans le maillage
     * \param _cote Côté d'un cube du maillage
     * \param _rayon Rayon d'une particule
     * \param x Dimension du parallélépipède selon x
     * \param y Dimension du parallélépipède selon y
     * \param z Dimension du parallélépipède selon z
     */
    Metaballs(Vecteur<3> _origine, double _cote, double _rayon, double x = 1.0, double y = 1.0, double z = 1.0);

    /**
     * \brief Destructeur
     *
     * Détruit un objet de classe Metaballs
     */
    ~Metaballs();


    /* ** Methodes ** */
public:
    /**
     * \brief Coloration
     *
     * Calcule la valeur de la surface implicite définie par les particules du fluide pour tout point du maillage,
     * et attribue à chaque sommet sa couleur, ceci pour déterminer la configuration des cubes
     * @param particules Liste des particules considérées
     */
    void coloration(list<Particule<3> *> &particules);
    // void coloration();

    /**
     * \brief Coloration - fonction de debug
     *
     * Considère un maillage de l'espace de dimensions 1 x 1 x 1, et transforme les sommets de l'unique cube
     * de manière à obtenir la configuration d'identifiant passé en paramètre.
     * @param config Configuration
     */
    void coloration(int config);

    /**
     * \brief Représentation
     *
     * Représente la surface implicite ainsi obtenue à l'aide de l'algorithme des Marching Cubes
     */
    void draw();

    /**
     * \brief Représentation d'un cube
     *
     * Représente une configuration d'un Marching Cube, à la position et de taille voulue
     * \param pos Position du sommet 0 du cube, d'abscisse, d'ordonnée et de côte minimales
     * \param cote Dimension du côté du cube
     * \param config Configuration du cube
     */
    void drawCube(Vecteur<3> pos, double cote, int config);

    /**
     * \brief Représentation d'un triangle
     *
     * Représente un triangle à l'intérieur d'un cube
     * \param pos Position du sommet 0 du cube, d'abscisse, d'ordonnée et de côte minimales
     * \param cote Dimension du côté du cube
     * \param a Numéro de la première arête à relier
     * \param b Numéro de la deuxième arête à relier
     * \param c Numéro de la troisième arête à relier
     * \param coef Coefficient d'orientation de la normale, devant valoir 1 ou -1
     */
    void drawTriangle(Vecteur<3> pos, double cote, int a, int b, int c, int coef);

    /**
     * \brief Association d'un point
     *
     * Retourne un point au milieu de l'arête a d'un cube, connaissant la position de son
     * sommet 0 et de son côté.
     * \param pos Position du sommet 0 du cube, d'abscisse, d'ordonnée et de côte minimales
     * \param cote Dimension du côté du cube
     * \param a Numéro de l'arête considérée
     * \return Le point de l'espace ainsi déterminé
     */
    Vecteur<3> associerPoint(Vecteur<3> pos, double cote, int a);
};

#endif
