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
    Fluide<Dim> *f; /*!< Pointeur vers le fluide utilisé */
    double bassin_x; /*!< Dimensions de la cuve rectangulaire selon l'axe (Ox) */
    double bassin_y; /*!< Dimensions de la cuve rectangulaire selon l'axe (Oy) */
    double bassin_z; /*!< Dimensions de la cuve rectangulaire selon l'axe (Oz) */
    double obstacle_x; /*!< Dimensions de l'obstacle rectangulaire selon l'axe (Ox) */
    double obstacle_y; /*!< Dimensions de l'obstacle rectangulaire selon l'axe (Oy) */
    double obstacle_z; /*!< Dimensions de l'obstacle rectangulaire selon l'axe (Oz) */
    double pente_angle; /*!< Angle formé par la pente et l'horizontale */
    double pente_x; /*!< Longueur totale de la pente */
    double pente_y; /*!< Largeur de la pente */
    double pente_z; /*!< Hauteur des bords de la pente */

public :
    
    /**
     * \brief Constructeur
     *
     * Constructeur d'une cascade prenant en compte les dimensions par défaut de celles-ci
     * mais recevant au moins un pointeur vers un objet existant de type Fluide
     *
     * \param _f Pointeur vers un objet de type Fluide, déjà créé ailleurs
     */
    Cascade(Fluide<Dim> *_f);

    /**
     * \brief Constructeur
     *
     * Constructeur d'une cascade prenant recevant un pointeur vers un objet existant de type Fluide
     * et la liste des grandeurs représentant les dimensions du bassin
     *
     * \param _f Pointeur vers un objet de type Fluide, déjà créé ailleurs
     * \param _bassin_x Nouvelles dimensions selon l'axe (Ox) du bassin
     * \param _bassin_y Nouvelles dimensions selon l'axe (Oy) du bassin
     * \param _bassin_z Nouvelles dimensions selon l'axe (Oz) du bassin
     * \param _obstacle_x Nouvelles dimensions selon l'axe (Ox) de l'obstacle
     * \param _obstacle_y Nouvelles dimensions selon l'axe (Oy) de l'obstacle 
     * \param _obstacle_z Nouvelles dimensions selon l'axe (Oz) de l'obstacle
     * \param _pente_angle Nouvel angle formé par la pente par rapport au plan horizontal
     * \param _pente_x Nouvelle longueur de la pente
     * \param _pente_y Nouvelle largeur de la pente
     * \param _pente_z Nouvelle hauteur pour les bords de la pente
     */
    Cascade(Fluide<Dim> *_f, double _bassin_x, double _bassin_y, double _bassin_z,
	    double _obstacle_x, double _obstacle_y, double _obstacle_z, 
	    double _pente_angle, double _pente_x, double _pente_y, double _pente_z);

    /**
     * \brief Destructeur
     *
     * Destructeur d'un objet de type Cascade
     */
    ~Cascade();

    /**
     * \brief Représentation graphique
     * 
     * Représente l'objet de type Cascade initialisé à l'appel de l'objet, ceci
     * comprenant un bassin et les particules du fluide
     */
    void draw();

    /**
     * \brief Animation physique
     * 
     * Anime physiquement les particules de l'objet de type Cascade
     */
    void animate();

    /**
      * \return la position en x du bassin
      */
    const double & getBassinX() const;

    /**
      * \return la position en y du bassin
      */
    const double & getBassinY() const;

    /**
      * \return la position en z du bassin
      */
    const double & getBassinZ() const;
};

#include "cascade.tpp"

#endif
