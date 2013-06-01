#ifndef _FLUIDE_HPP_
#define _FLUIDE_HPP_

#include <vector>
using std::vector;
#include <iostream>
#include <map>
#include "materiau.hpp"
#include "particule.hpp"
#include "vecteur.hpp"
#include "premier.hpp"
using std::multimap;

/** 
 * \class Fluide
 * @brief Gestion de l'ensemble des particules constituant le fluide
 * 
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class Fluide {
    
    /* ** Attributs ** */
private:
    Materiau<Dim> * mat;                 // Materiau du fluide (avec toutes les constantes)
    vector<Particule<Dim> *> particules; // Ensemble des particules
    int nbrParticules;                   // Nombre de particules du fluide
    bool debutAnim;                      // Indique si on est au debut de l'animation
    Premier<Dim> table;                  // Table pour la dimension de la table de hachage
    multimap<int, Particule<Dim> > hash_voisins;

    /* Fonction de hashage */
    int fonction_hashage(Vecteur<Dim>);

    /* ** Constructeurs ** */
public:
    /**
      * Constructeur par defaut
      * \param m matériau du fluide
      */
    Fluide(Materiau<Dim> * m);

    /**
      * Constructeur avec initialisation d'un parallèlépipède de particules
      * \param m Matériau du fluide
      * \param nb Tableau du nombre de particules sur chacune des dimensions
      * \param ecart Écart entre les particules
      * \param rho Masse volumique initiale des particules
      * \param p Pression initiale des particules
      */
    Fluide(Materiau<Dim> * m, int nb[Dim], double ecart, double rho = 0, double p = 0);
    
    /**
      * Destructeur
      */
    ~Fluide();


    /* ** Methodes ** */
public:
    /**
      * Ajoute une particule à l'ensemble des particules
      * \param part La particule à ajouter
      */
    void ajouteParticule(Particule<Dim> * part);
    
    /**
      * Met à jour la densité et la pression de toutes les particules
      */
    void majDensitePression();
    
    /**
      * Met à jour la densité et la pression de toutes les particules
      */
    void majPositionVitesse();
    
    /**
      * Fonction d'affichage du fluide
      */
    void draw() const;

    /**
      * Affichage des particules du fluide
      */
    void affiche();

    friend void test_map();
};


#include "fluide.tpp"

#endif

