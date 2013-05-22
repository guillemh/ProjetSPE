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
    Materiau<Dim> * mat;                      // Materiau du fluide (avec toutes les constantes)
    vector<Particule<Dim> *> particules; // Ensemble des particules


    /* ** Constructeurs ** */
public:
    /**
      * Constructeur par defaut
      * \param m matériau du fluide
      */
    Fluide(Materiau<Dim> * m);

    /**
      * Constructeur avec initialisation d'un parallèlépipède de particules
      * \param m matériau du fluide
      * \param nb tableau du nombre de particules sur chacune des dimensions
      * \param ecart écart entre les particules
      * \param rho masse volumique initiale des particules
      * \param p pression initiale des particules
      */
    Fluide(Materiau<Dim> * m, int nb[Dim], double ecart, double rho, double p);
    
    /**
      * Destructeur
      */
    ~Fluide();


    /* ** Methodes ** */
public:
    /**
      * Ajoute une particule à l'ensemble des particules
      * \param part la particule à ajouter
      */
    void ajouteParticule(Particule<Dim> * part);
    
    /**
      * Fonction d'affichage du fluide
      */
    //void draw() const;

    /**
      * Affichage des particules du fluide
      */
    void affiche();

};


#include "fluide.tpp"

#endif

