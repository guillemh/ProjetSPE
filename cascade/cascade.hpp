#ifndef _CASCADE_HPP_
#define _CASCADE_HPP_

#include "../core/fluide.hpp"

/**
 * \class Cascade
 * \brief Classe utilisée pour le rendu final de l'animation
 *
 * Classe simulant le mouvement d'un fluide dans une cascade, laquelle se compose de trois éléments : <br/>
 * <ul>
 *   <li>le bassin, rectangulaire, positionné et centré le long de l'axe (Oy),</li>
 *   <li>un obstacle, rectangulaire et centré en l'origine du repère,</li>
 *   <li>une pente centrée par rapport à l'axe (Ox), en haut de laquelle les particules partent.</li>
 * </ul>
 */

template<unsigned int Dim>
class Cascade {

    /* ** Attributs ** */
private :
    Fluide<Dim> *f;       /* Pointeur vers le fluide utilisé */
    double bassin_x;      /* Dimensions de la cuve rectangulaire selon l'axe (Ox) */
    double bassin_y;      /* Dimensions de la cuve rectangulaire selon l'axe (Oy) */
    double bassin_z;      /* Dimensions de la cuve rectangulaire selon l'axe (Oz) */
    bool arps;            /* pour choisir entre l'arps ou pas pour l'animation */

public :
    
    /**
     * \brief Constructeur
     *
     * Constructeur d'une cascade avec le fluide correspondant
     * \param _f Pointeur vers un objet de classe Fluide
     */
    Cascade(Fluide<Dim> *_f);

    /**
     * \brief Constructeur
     *
     * Constructeur d'une cascade à partir du fluide et de
     * la liste des grandeurs représentant les dimensions du bassin
     * \param _f Pointeur vers un objet de classe Fluide
     * \param _bassin_x Dimension selon l'axe (Ox) du bassin
     * \param _bassin_y Dimension selon l'axe (Oy) du bassin
     * \param _bassin_z Dimension selon l'axe (Oz) du bassin
     */
    Cascade(Fluide<Dim> *_f, double _bassin_x, double _bassin_y, double _bassin_z);

    /**
     * \brief Destructeur
     *
     * Destructeur d'un objet de type Cascade
     */
    ~Cascade();

  

    /**
     * \brief Méthode de dessin
     * 
     * Dessine l'objet de type Cascade,
     * comprenant un bassin et les particules du fluide
     */
    void draw();

    /**
     * \brief Animation physique
     * 
     * Anime physiquement les particules de l'objet de type Cascade
     * @param arps Booléen valant True ssi on veut utiliser l'ARPS
     * pour la simulation
     */
    void animate(bool arps);

    /**
     * @brief Accesseur
     * \return La position en x du bassin
     */
    const double & getBassinX() const;

    /**
     * @brief Accesseur
     * \return La position en y du bassin
     */
    const double & getBassinY() const;

    /**
     * @brief Accesseur
     * \return La position en z du bassin
     */
    const double & getBassinZ() const;
};

#include "cascade.tpp"

#endif
