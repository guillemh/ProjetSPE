#ifndef _METABALLS_
#ifndef _METABALLS_

#include <iostream>
#include "../core/particules.hpp"

/** 
 * \class Metaballs
 * @brief Classe discrétisant l'espace pour afficher un fluide avec des surfaces implicites
 * 
 * Dim : Dimension de l'espace
 */
class Metaballs {

    /* ** Attributs ** */
    
private:
    int n; /*!< Nombre de cubes selon l'axe (Ox) */
    int p; /*!< Nombre de cubes selon l'axe (Oy) */
    int q; /*!< Nombre de cubes selon l'axe (Oz) */
    bool*** points; /*!< Tableau de booléens, chaque booléen étant associé de façon unique à un point de l'espace :
		      un booléen indique si le sommet doit être marqué ou non, ce qui nous permet d'obtenir la configuration
		      correspondante du cube qui sera défini par la suite à l'aide de huit points */
    int configurations[256][12]; /*!< Look-up table des configurations possibles pour l'algorithme des Marching Cubes */


    /* ** Constructeurs ** */
    
public:
    /**
     * \brief Constructeur
     *
     * Alloue le tableau de points
     */
    Metaballs();

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
     */
    void coloration(const list<Particule <3>* > &particules);

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
     * \param pos Position du sommet 0 du cube, d'abscisse, d'ordonnée et de côte minimale
     * \param cote Dimension du côté du cube
     * \param config Configuration du cube
     */
    void drawCube(Vecteur<Dim> pos, double cote, int config);

    /**
     * \brief Représentation d'un triangle
     *
     * Représente un triangle à l'intérieur d'un cube
     * \param pos Position du sommet 0 du cube, d'abscisse, d'ordonnée et de côté minimale
     * \param cote Dimension du côté du cube
     * \param int a Numéro de la première arête à relier
     * \param int b Numéro de la deuxième arête à relier
     * \param int c Numéro de la troisième arête à relier
     */
    void drawTriangle(Vecteur<Dim> pos, double cote, int a, int b, int c);
};

#endif
