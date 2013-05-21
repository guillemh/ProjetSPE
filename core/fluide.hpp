#ifndef _FLUIDE_HPP_
#define _FLUIDE_HPP_

#include <vector>
using std::vector;
#include <iostream>
#include "materiau.hpp"
#include "vecteur.hpp"


/** \class Fluide : gestion de l'ensemble des particules constituant le fluide
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class Fluide {

    /* ** Attributs ** */
private:
    Materiau * mat;                      // Materiau du fluide (avec toutes les constantes)
    Vector<Particule<Dim> *> particules; // Ensemble des particules


    /* ** Constructeurs ** */
public:
    /**
      * Constructeur par defaut
      * \param m matériau du fluide
      */
    Fluide(Materiau * m);

    /**
      * Constructeur avec initialisation d'un parallèlépipède de particules
      * \param m matériau du fluide
      * \param nb tableau du nombre de particules sur chacune des dimensions
      * \param ecart écart entre les particules
      * \param rho masse volumique initiale des particules
      * \param p pression initiale des particules
      */
    Fluide(Materiau * m, double nb[Dim], double ecart, double rho, double p);
    
    /**
      * Destructeur
      */
    ~Fluide();


    /* ** Methodes ** */
public:
    /**
      * Ajoute une particule à l'ensemble des particules
      */
    void ajouteParticule(Particule<Dim> * part) const;
    
    /**
      * Fonction d'affichage du fluide
      */
    //void draw() const;
};


#include "fluide.tpp"

#endif

